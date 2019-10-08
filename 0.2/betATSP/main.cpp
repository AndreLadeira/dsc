#include <iostream>
#include <vector>
#include <algorithm>

#include "functors.h"
#include "decorators.h"
#include "atsp.h"
#include "atsp_decision.h"

using namespace std;
using namespace algorithm;
using namespace problems::atsp;

int main(void)
{
    const std::vector<size_t> p = {0,12,16,11,1,9,2,13,8,3,10,5,6,14,15,7,4,0};
    atsp_decision::solution_t s(p.size()-1);
    atsp_decision::from_path(p,s);
    std::vector<size_t> q;
    atsp_decision::to_path(s,q);

    assert(p == q);

    using createFunctor = core::CreateFunctor<atsp_decision::solution_t>;
    using createCallCnt = core::CreateFunctorCallCounter<atsp_decision::solution_t>;
    using printCreated = core::PrintSolution<atsp_decision::solution_t>;

    atsp_decision::problem_data_t tspdata;
    problems::atsp::loadTSPLIB(std::ifstream("../tsplib/br17.atsp"),tspdata);

    shared_ptr<createFunctor> create = make_shared<atsp_decision::BasicCreateFunctor>(tspdata.size());
    create = make_shared<printCreated>(create);
    create = make_shared<createCallCnt>(create);

    s = (*create)();
    std::cout<< "Times create called: " <<
                dynamic_cast<createCallCnt*>(create.get())->getCounter() << endl;

    using neighborFunctor =
    core::NeighborhoodFunctor< atsp_decision::solution_t, atsp_decision::transformation_t >;
    using neighborCallCnt =
    core::NeighborhoodFunctorCallCounter< atsp_decision::solution_t, atsp_decision::transformation_t >;

    shared_ptr<neighborFunctor>  neighbor = make_shared< atsp_decision::NeighborhoodFunctor >();
    neighbor = make_shared< neighborCallCnt >(neighbor);

    auto neighbors = (*neighbor)(s);
    std::cout<< "Times neighbor called: " <<
                dynamic_cast<neighborCallCnt*>(neighbor.get())->getCounter() << endl;
    std::cout<< "Number of neighbors: " << neighbors.size() << endl;

    using objFunctor =
    core::ObjectiveFunctor< atsp_decision::solution_t, atsp_decision::problem_data_t>;
    using objCallCounter = core::ObjectiveFunctorCallCounter< atsp_decision::solution_t, atsp_decision::problem_data_t>;

    shared_ptr<objFunctor> cost = make_shared<atsp_decision::ObjectiveFunctor>(tspdata);
    cost = make_shared<objCallCounter>(cost);

    std::cout<< "Solution cost: " << (*cost)(s) << endl;

    using deltaObjFunctor =
    core::DeltaObjectiveFunctor< atsp_decision::solution_t, atsp_decision::transformation_t, atsp_decision::problem_data_t>;

    shared_ptr<deltaObjFunctor> deltacost = make_shared<atsp_decision::DeltaObjectiveFunctor>(tspdata);
    atsp_decision::DeltaObjectiveFunctor::result_vector_type deltas( neighbors.size() );

    (*deltacost)(s,neighbors,deltas);

    shared_ptr<atsp_decision::AcceptFunctor> accept = make_shared<atsp_decision::AcceptFunctor>();

    atsp_decision::AcceptFunctor::result_t accepted = (*accept)(deltas);

    std::cout<< "Improvement possible: " << std::boolalpha << accepted.first << endl;

    auto bestimprove = deltas.at(accepted.second);

    if ( accepted.first )
    {
        std::cout<< "Best solution cost improvement: " << bestimprove
                 << " at index " << accepted.second << endl;

        std::cout<< "Expected modified solution cost is: " << signed((*cost)(s)) + bestimprove << endl;

        auto transform = make_shared<atsp_decision::TransformFunctor>();
        (*transform)(s,neighbors.at(accepted.second));

        std::cout<< "Obtained solution cost is: " << (*cost)(s) << endl;

    }


    std::cout<< "Times objective function was called: " <<
                dynamic_cast<objCallCounter*>(cost.get())->getCounter() << endl;

    //std::sort(deltas.begin(),deltas.end());
    //assert( deltas.at(0) == bestimprove );

    return 0;
}
