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

    shared_ptr<createFunctor> create = make_shared<atsp_decision::BasicCreateFunctor>(10);
    create = make_shared<createCallCnt>(create);
    create = make_shared<printCreated>(create);

    atsp_decision::solution_t s = (*create)();

    return 0;
}
