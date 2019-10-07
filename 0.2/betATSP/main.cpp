#include <iostream>
#include <vector>

#include "functors.h"
#include "decorators.h"
#include "atsp_decision.h"

using namespace std;
using namespace algorithm;
using namespace core;

int main(void)
{
    using createFunctor = core::CreateFunctor<atsp_decision::solution_t>;
    using createCallCnt = core::CreateFunctorCallCounter<atsp_decision::solution_t>;
    using printCreated = core::PrintSolution<atsp_decision::solution_t>;

    shared_ptr<createFunctor> create = make_shared<atsp_decision::BasicCreateFunctor>(4);
    create = make_shared<printCreated>(create);
    create = make_shared<createCallCnt>(create);

    atsp_decision::solution_t s = (*create)();
    std::cout<< "Times create called: " <<
                dynamic_cast<createCallCnt*>(create.get())->getCounter() << endl;

    using neighborFunctor =
    core::NeighborhoodFunctor< atsp_decision::solution_t, atsp_decision::transformation_t >;
    using neighborCallCnt =
    core::NeighborhoodFunctorCallCounter< atsp_decision::solution_t, atsp_decision::transformation_t >;

    shared_ptr<neighborFunctor>  neighbor = make_shared< atsp_decision::NeighborhoodFunctor >();
    neighbor = make_shared< neighborCallCnt >(neighbor);

    auto tr = (*neighbor)(s);
    std::cout<< "Times neighbor called: " <<
                dynamic_cast<neighborCallCnt*>(neighbor.get())->getCounter() << endl;
    std::cout<< "Number of neighbors: " << tr.size() << endl;

    return 0;
}
