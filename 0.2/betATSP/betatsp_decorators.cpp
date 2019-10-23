#include "betatsp_decorators.h"
using namespace problems::atsp::atsp_decision;

std::vector<t> BetATSP_Bet::operator()(const s& sol)
{
    const auto transfs = _ptr->operator()(sol);

    _house.getBets(sol,transfs);

    return transfs;
}

void BetATSP_Check::operator()(
        const s &sol,
        const std::vector<t> &trvec,
        DeltaObjective::result_vector_type &resvec)
{
   _ptr->operator()(sol,trvec,resvec);
   _house.processResults(resvec);
}
