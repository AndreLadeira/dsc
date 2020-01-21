#include <algorithm>
#include <iomanip>
#include <ctime>
#include <cassert>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <cxxabi.h>

#include "functors.h"
#include "decorators.h"
#include "atsp.h"
#include "atsp_decision.h"
#include "execution_controller.h"
#include "betatsp_decorators.h"
#include "stdfunctors.h"
#include "greedy.h"
#include "simulated_annealing.h"

using namespace std;
using namespace problems::atsp;
using namespace atsp_decision;
using namespace core;

using algorithms::simmulated_annealing::CooldownCos;
using algorithms::simmulated_annealing::TemperatureFunction;
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

    core::ExecutionController exec;
    auto restarts = strtoul(argv[2],nullptr,0);

    // CREATE FUNCTION AND ACCESSORIES

    shared_ptr< core::Create< solution_t > > create_solution =
            make_shared< CreateRandom >(tspdata.size());

    auto create_counter = make_shared< core::CreateCallsCounter< solution_t >>(create_solution);
    create_solution = create_counter;

    algorithms::simmulated_annealing::CooldownFunction
            coolCos(10,1,restarts,std::bind(CooldownCos,std::placeholders::_1,5.0) );

    auto update_temp = make_shared< TemperatureFunction< solution_t > >(create_solution,coolCos);
    create_solution = update_temp;

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

    accept = make_shared< algorithms::simmulated_annealing::DeltaAcceptDecrease<> >(*update_temp);

//    if ( argv[3] == nullptr )
//        accept = make_shared< algorithms::greedy::DeltaAcceptBestDecrease<> >();
//    else
//        accept = make_shared< algorithms::greedy::DeltaAccept1stDecrease<> >();

    // TRANSFORM FUNCTION AND ACCESSORIES

    auto transform = make_shared<atsp_decision::Transform>();

    // UPDATE FUNCTION AND DECORATORS

    shared_ptr< core::Update<solution_t,int> > update =
            make_shared< core::UpdateAlways<solution_t,int> >();

    auto progress_monitor = make_shared< core::ObjectiveProgress<solution_t,int> >(update);
    update = progress_monitor;

    // Record intensification history between each create call
    auto neighCallsRecorder = make_shared<
        core::NeighborsCallsRecorder<solution_t,int,core::Compare<int>::less > > (update,*neighbors_calls_resettable);

    update = neighCallsRecorder;

    // add a stagnation counter. One stagnation means intensifying to the end and not improving.
    auto stagnation_counter = make_shared<
        core::StagnationCounter<solution_t,int,core::Compare<int>::less > > (update);

    update = stagnation_counter;

    auto objective_value = make_shared<
        core::ObjectiveValue<solution_t,int,core::Compare<int>::less > > (update);

    update = objective_value;

    // EXECUTION TIMER
    auto timer = make_shared<Timer>();

    exec.addStopTrigger( make_shared< core::Trigger<> >("Create function counter", create_counter,500));
    exec.addRestartTrigger( make_shared< core::Trigger<> >("Neighbor calls", neighbors_calls_resettable, 3));
//    exec.addStopTrigger( make_shared< core::Trigger<>>("Total explored transitions counter", neighbors_counter,20e06) );
//    exec.addStopTrigger( make_shared< core::Trigger<double>>("Progress monitor", progress_monitor,0.73) );
//    exec.addStopTrigger( make_shared< core::Trigger<>>("Cost function counter", cost_call_counter,100) );
//    exec.addStopTrigger( make_shared< core::Trigger<double> >("Timer", timer,0.5) );
//    exec.addStopTrigger( make_shared< core::Trigger<> >("Stagnated intensifications counter", stagnation_counter,100) );
      //exec.addStopTrigger( make_shared< core::Trigger<> >("Objective value", objective_value,6910,Compare<size_t>::less_or_equal) );

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
        int index = 0;
        while( index > -1 && !exec.restart())
        {
            auto transitions = (*neighbor)(current);
            auto deltas = (*deltacost)(current,transitions);
            index = (*accept)(deltas);

            if ( index > -1 )
            {
                (*transform)(current,transitions.at( static_cast<size_t>(index)) );
                current_cost = current_cost + deltas.at( static_cast<size_t>(index) );
            }
        }

        (*update)(best,best_cost,current,current_cost);
        current = (*create_solution)();
        current_cost = (*cost)(current);
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
    //std::cout<< neighCallsRecorder->getRecord() << endl;
    cout<< "Execution stop triggered by         : " << exec.getStoppingTrigger() << endl;
    cout<< "Execution time                      : " << fixed << std::setprecision(2) << timer->getValue() << "s\n";
    cout<< "Initial result                      : " << start_cost << endl;
    cout<< "Final result                        : " << best_cost << endl;
    cout<< "Improvement                         : " << progress_monitor->getValue() * 100.0 << "%\n";
    cout<< "Times create solution called        : " << create_counter->getValue() << endl;
    cout<< "Times neighbor called               : " << neighbor_calls_counter->getValue() << endl;
    cout.imbue( std::locale("en_US"));
    cout<< "Total Number of transitions listed  : " << neighbors_counter->getValue() << endl;
    cout.imbue( std::locale(""));
    cout<< "Times objective function was called : " << cost_call_counter->getValue() << endl;
    cout<< "Times delta function was called     : " << delta_call_counter->getValue() << endl;
    core::Statistics<> stats( neighCallsRecorder->getRecord() );
    cout<< "Intensification until local maxima  : " << stats.getMin() << "/" << stats.getMax()
        <<"/" << stats.getAverage() <<"/" << stats.getStdDev() << " (min/max/avg/stddev)\n";
    cout<< "Final stagnation count              : " << stagnation_counter->getValue() << endl;

#endif
    return 0;
}
