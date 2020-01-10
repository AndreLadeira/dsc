#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <cassert>

#include "functors.h"
#include "decorators.h"
#include "atsp.h"
#include "atsp_decision.h"
#include "execution_controller.h"
#include "betatsp_decorators.h"
#include "stdfunctors.h"

using namespace std;
using namespace problems::atsp;
using namespace atsp_decision;
using namespace core;

int main(int, char * argv[])
{
    problem_data_t tspdata;
    std::ifstream datafile(argv[1]);
    if (datafile.is_open())
        problems::atsp::loadTSPLIB(datafile,tspdata);
    else
    {
        std::cout<<"Data file not found.\n";
        return 0;
    }
    datafile.close();

    // CREATE FUNCTION AND ACCESSORIES

    shared_ptr< core::Create< solution_t > > create_solution =
            make_shared< CreateRandom >(tspdata.size());

    auto create_counter = make_shared< core::CreateCallsCounter< solution_t >>(create_solution);
    create_solution = create_counter;


    // NEIGHBOR FUNCTION AND ACCESSORIES

    shared_ptr< core::Neighborhood<solution_t,transformation_t> >
            neighbor = make_shared< atsp_decision::Neighborhood >();

    auto neighbor_calls_counter = make_shared< core::NeighborCallsCounter<solution_t,transformation_t > >(neighbor);
    neighbor = neighbor_calls_counter;

    auto neighbors_counter = make_shared< core::NeighborsExploredCounter< solution_t, transformation_t > >(neighbor);
    neighbor = neighbors_counter;

    auto neighbors_calls_resettable = make_shared< core::NeighborCallsResettable<solution_t,transformation_t > >(neighbor);
    neighbor = neighbors_calls_resettable;

    // OBJECTIVE FUNCTION AND ACCESSORIES

    shared_ptr< core::Objective<solution_t, problem_data_t> > cost =
            make_shared<atsp_decision::Objective>(tspdata);

    auto cost_call_counter = make_shared< core::ObjectiveCallsCounter<solution_t, problem_data_t> >(cost);
    cost = cost_call_counter;

    // DELTA OBJECTIVE FUNCTION AND ACCESSORIES

    shared_ptr< core::DeltaObjective<solution_t,transformation_t,problem_data_t> >
            deltacost = make_shared< atsp_decision::DeltaObjective >(tspdata);

    auto delta_call_counter = make_shared<
            core::DeltaObjectiveCallsCounter< solution_t, transformation_t, problem_data_t > >(deltacost);

    deltacost = delta_call_counter;

    // ACCEPT FUNCTION AND ACCESSORIES

    shared_ptr< core::DeltaAccept<> > accept;

    if ( argv[3] == nullptr )
        accept = make_shared< core::DeltaAcceptBestDecrease<> >();
    else
        accept = make_shared< core::DeltaAccept1stDecrease<> >();

    // TRANSFORM FUNCTION AND ACCESSORIES

    auto transform = make_shared<atsp_decision::Transform>();

    core::ExecutionController exec;
    auto restarts = strtoul(argv[2],nullptr,0);

    // UPDATE FUNCTION AND DECORATORS

    shared_ptr< core::Update<solution_t,int,core::Compare<int>::less> > update;
    update = make_shared< core::UpdateIfsmaller<solution_t,int> >();

    auto progress_monitor = make_shared< core::ObjectiveProgress<solution_t,int,core::Compare<int>::less> >(update);
    update = progress_monitor;

    // Record intensification history between each create call
    auto neighCallsRecorder = make_shared<
        core::NeighborsCallsRecorder<solution_t,int,core::Compare<int>::less > > (update,*neighbors_calls_resettable);

    update = neighCallsRecorder;

    // add a stagnation counter. One stagnation count means intensifying to the end and not improving.
    auto stagnation_counter = make_shared<
        core::StagnationCounter<solution_t,int,core::Compare<int>::less > > (update);

    update = stagnation_counter;



    // EXECUTION TIMER
    auto timer = make_shared<Timer>();

    //exec.addStopTrigger( make_shared< core::Trigger<> >(create_counter,restarts) );
    //exec.addStopTrigger( make_shared< core::Trigger<>>(neighbors_counter,800e03) );
    //exec.addStopTrigger( make_shared< core::Trigger<double>>(progress_monitor,0.65) );
//    exec.addStopTrigger( make_shared< core::Trigger<>>(cost_call_counter,30) );
    //exec.addStopTrigger( make_shared< core::Trigger<double> >(timer,1.0) );
    exec.addStopTrigger( make_shared< core::Trigger<> >(stagnation_counter,300) );

    timer->start();

    auto current = (*create_solution)();
    auto best = current;
    auto best_cost = (*cost)(best);
    auto current_cost = best_cost;
#ifndef __RESULTGEN__
    auto start_cost = current_cost;
#endif

    while(!exec.stop())
    {
        auto transitions = (*neighbor)(current);
        auto deltas = (*deltacost)(current,transitions);
        auto index = (*accept)(deltas);

        if ( index > -1 )
        {
            (*transform)(current,transitions.at( static_cast<size_t>(index)) );
            current_cost = current_cost + deltas.at( static_cast<size_t>(index) );
        }
        else
        {
           (*update)(best,best_cost,current,current_cost);
           current = (*create_solution)();
           current_cost = (*cost)(current);
        }
    }

#ifdef __DEBUG__
    assert( best_cost == (*cost)(best));
#endif

#ifdef __RESULTGEN__

    std::cout<< std::setprecision(3) << best_cost << "\t" << progress_monitor->getValue() << "\t"
             << cost_call_counter->getValue() << "\t" << neighbors_counter->getValue() << "\t"
             << timer->getValue() << endl;
    //std::cout<< neighCallsRecorder->getRecord() << endl;
#else
    cout<< "Elapsed time: " << fixed << std::setprecision(2) << timer->getValue() << endl;
    std::cout<< "Initial result: " << start_cost << endl;
    std::cout<< "Final result: " << best_cost << endl;
    std::cout<< "Improvement: " << progress_monitor->getValue() * 100.0 << "%\n";
    std::cout<< "Times create solution called: " << create_counter->getValue() << endl;
    std::cout<< "Times neighbor called: " << neighbor_calls_counter->getValue() << endl;
    cout.imbue( std::locale("en_US"));
    std::cout<< "Total Number of transitions listed: " << neighbors_counter->getValue() << endl;
    cout.imbue( std::locale(""));
    std::cout<< "Times objective function was called: " << cost_call_counter->getValue() << endl;
    std::cout<< "Times delta function was called: " << delta_call_counter->getValue() << endl;
    core::Statistics<> stats( neighCallsRecorder->getRecord() );
    std::cout<< "Intensification until local maxima (min/max/avg/stddev):" << stats.getMin()
             << "/" << stats.getMax() <<"/" << stats.getAverage() <<"/" << stats.getStdDev() << endl;
    std::cout<< "Final stagnation count:" << stagnation_counter->getValue() << endl;
    //std::cout<< neighCallsRecorder->getRecord() << endl;
#endif
    return 0;
}
