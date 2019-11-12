#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <ctime>

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

    auto create_counter = make_shared< core::create::CallCounter< solution_t >>(create_solution);
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

    auto neighbor_callcounter = make_shared< neighbor::CallCounter<solution_t,transformation_t > >(neighbor);
    neighbor = neighbor_callcounter;

    auto neighbor_counter = make_shared< neighbor::NeighborCounter<solution_t,transformation_t > >(neighbor);
    neighbor = neighbor_counter;

    //neighbor = make_shared< BetATSP_Bet >(neighbor,house);

    // OBJECTIVE FUNCTION AND ACCESSORIES

    shared_ptr< core::Objective<solution_t, problem_data_t> >
            cost = make_shared<atsp_decision::Objective>(tspdata);
    auto cost_counter = make_shared< objective::CallCounter<solution_t, problem_data_t> >(cost);
    cost = cost_counter;

    // DELTA OBJECTIVE FUNCTION AND ACCESSORIES

    shared_ptr< core::DeltaObjective<solution_t,transformation_t,problem_data_t> >
            deltacost = make_shared< atsp_decision::DeltaObjective >(tspdata);

//    deltacost = make_shared< BetATSP_Check >(deltacost,house);

    // ACCEPT FUNCTION AND ACCESSORIES

    auto accept = make_shared<atsp_decision::Accept>();

    // TRANSFORM FUNCTION AND ACCESSORIES

    auto transform = make_shared<atsp_decision::Transform>();


    core::ExecutionController exec;
    auto restarts = strtoul(argv[2],nullptr,0);
    exec.addStopTrigger( make_shared< core::Trigger<> >(create_counter,restarts));
    //exec.addStopTrigger( make_shared<core::Trigger<size_t>>(neighbor_counter,400000));


    auto solution = (*create_solution)();
    auto best = solution;
    auto best_cost = (*cost)(best);
    const auto start_cost = best_cost;

    clock_t begin = clock();

    while(!exec.stop())
    {
        auto neighbors = (*neighbor)(solution);

        //vector<int> deltas( neighbors.size() );

        auto deltas = (*deltacost)(solution,neighbors);

        auto accepted = (*accept)(deltas);

        if ( accepted.first )
        {
            (*transform)(solution,neighbors.at(accepted.second));
        }
        else
        {
            // saving only when a particular solution
            // fully explored, to reduce execution costs

            // 1st, check if this particular maximum/minumum
            // is a new absolute max/min

            auto newcost = (*cost)(solution);
            if ( newcost < best_cost )
            {
                best = solution;
                best_cost = newcost;
            }

            // then, restarts
            solution = (*create_solution)();
        }
    }

#ifdef __DEBUG__
    assert( best_cost == (*cost)(best));
#endif

    cout<< "Elapsed time: " << fixed << std::setprecision(2) <<
           (clock() - begin) / static_cast<double>(CLOCKS_PER_SEC) << endl;
    std::cout<< "Initial result: " << start_cost << endl;
    std::cout<< "Final result: " << best_cost << endl;
    std::cout<< "Improvement: " << ( start_cost - best_cost ) << "/" << 100.0 * ( start_cost - best_cost ) / start_cost << "%\n";
    std::cout<< "Times create solution called: " << create_counter->getValue() << endl;
    std::cout<< "Times neighbor called: " << neighbor_callcounter->getValue() << endl;
    cout.imbue( std::locale("en_US"));
    std::cout<< "Total Number of neighbors evaluated: " << neighbor_counter->getValue() << endl;
    std::cout<< "Times objective function was called: " << cost_counter->getValue() << endl;

    return 0;
}
