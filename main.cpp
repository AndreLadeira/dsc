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

using namespace std;
using namespace problems::atsp;
using namespace atsp_decision;
using namespace core;

int main(int, char * argv[])
{
    problem_data_t tspdata;
    problems::atsp::loadTSPLIB(std::ifstream(argv[1]),tspdata);

    // CREATE FUNCTION AND ACCESSORIES

    shared_ptr< core::Create< solution_t > > create_solution =
            make_shared< CreateRandom >(tspdata.size());

    auto create_counter = make_shared< core::CreateCallsAccumulator< solution_t >>(create_solution);
    create_solution = create_counter;
    //create_solution = make_shared< create::PrintSolution<solution_t>>(create_counter);

    // BET stuff
//    Gambler::setProblemSize(tspdata.size());
//    auto trsz = (tspdata.size() - 2)*(tspdata.size() - 2);
//    std::vector<Gambler> gamblers(20);
//    House house(gamblers,1000.0,1.0, trsz);

    // NEIGHBOR FUNCTION AND ACCESSORIES

    shared_ptr< core::Neighborhood<solution_t,transformation_t> >
            neighbor = make_shared< atsp_decision::Neighborhood >();

    auto neighbor_totalcalls = make_shared< core::NeighborCallAccumulator<solution_t,transformation_t > >(neighbor);
    neighbor = neighbor_totalcalls;

    auto neighbor_counter = make_shared< core::NeighborAccumulator<solution_t,transformation_t > >(neighbor);
    neighbor = neighbor_counter;

    auto neighbor_callcounter = make_shared< core::NeighborAccumulator<solution_t,transformation_t > >(neighbor);
    neighbor = neighbor_callcounter;

    //neighbor = make_shared< BetATSP_Bet >(neighbor,house);

    // OBJECTIVE FUNCTION AND ACCESSORIES

    shared_ptr< core::Objective<solution_t, problem_data_t> > cost =
            make_shared<atsp_decision::Objective>(tspdata);

    auto cost_call_counter = make_shared< core::ObjectiveCallAccumulator<solution_t, problem_data_t> >(cost);
    cost = cost_call_counter;

    auto solution = (*create_solution)();
    auto best = solution;
    auto best_cost = (*cost)(best);
    const auto start_cost = best_cost;

    auto progress_monitor = make_shared< core::ObjectiveProgress<solution_t, problem_data_t> >(cost, start_cost);
    cost = progress_monitor;

    // DELTA OBJECTIVE FUNCTION AND ACCESSORIES

    shared_ptr< core::DeltaObjective<solution_t,transformation_t,problem_data_t> >
            deltacost = make_shared< atsp_decision::DeltaObjective >(tspdata);
    auto delta_call_counter = make_shared<
            core::DeltaObjectiveCallAccumulator< solution_t, transformation_t, problem_data_t > >(deltacost);
    deltacost = delta_call_counter;

//    deltacost = make_shared< BetATSP_Check >(deltacost,house);

    // ACCEPT FUNCTION AND ACCESSORIES
    shared_ptr< core::DeltaAccept<> > accept;

    if ( argv[3] == nullptr )
        accept = make_shared<atsp_decision::DeltaAccept>();
    else
        accept = make_shared<atsp_decision::DeltaAccept1stImprove>();

    // TRANSFORM FUNCTION AND ACCESSORIES

    auto transform = make_shared<atsp_decision::Transform>();

    core::ExecutionController exec;
    auto restarts = strtoul(argv[2],nullptr,0);

    exec.addStopTrigger( make_shared< core::Trigger<> >(create_counter,restarts) );
    //exec.addStopTrigger( make_shared< core::Trigger<>>(neighbor_counter,30e06) );
    //exec.addStopTrigger( make_shared< core::Trigger<double>>(progress_monitor,0.73) );
    //exec.addStopTrigger( make_shared< core::Trigger<>>(cost_call_counter,100000) );

    clock_t begin = clock();

    while(!exec.stop())
    {
        auto transitions = (*neighbor)(solution);
        auto deltas = (*deltacost)(solution,transitions);
        auto acceptDelta = (*accept)(deltas);

        if ( acceptDelta.accepted )
        {
            (*transform)(solution,transitions.at(acceptDelta.index));

            auto newcost = (*cost)(solution);
            if ( newcost < best_cost )
            {
                best = solution;
                best_cost = newcost;
            }
        }
        else
        {
           solution = (*create_solution)();
        }
    }

#ifdef __DEBUG__
    assert( best_cost == (*cost)(best));
#endif


//    cout<< "Elapsed time: " << fixed << std::setprecision(2) <<
//           (clock() - begin) / static_cast<double>(CLOCKS_PER_SEC) << endl;
//    std::cout<< "Initial result: " << start_cost << endl;
//    std::cout<< "Final result: " << best_cost << endl;
//    std::cout<< "Improvement: " << ( start_cost - best_cost ) << " / " << 100.0 * ( start_cost - best_cost ) / start_cost << "%\n";
//    std::cout<< "Improvement: " << progress_monitor->getValue() * 100.0 << "%\n";
//    std::cout<< "Times create solution called: " << create_counter->getValue() << endl;
//    std::cout<< "Times neighbor called: " << neighbor_totalcalls->getValue() << endl;
//    cout.imbue( std::locale("en_US"));
//    std::cout<< "Total Number of transitions listed: " << neighbor_counter->getValue() << endl;
//    cout.imbue( std::locale(""));
//    std::cout<< "Times objective function was called: " << cost_call_counter->getValue() << endl;
//    std::cout<< "Times delta function was called: " << delta_call_counter->getValue() << endl;

    std::cout<< best_cost << "\t" << progress_monitor->getValue() << "\t" <<
                cost_call_counter->getValue() << "\t" << neighbor_counter->getValue() << "\t" <<
                (clock() - begin) / static_cast<double>(CLOCKS_PER_SEC) << endl;

    return 0;
}
