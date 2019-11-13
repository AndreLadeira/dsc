#ifndef BETATSP_DECORATORS_H
#define BETATSP_DECORATORS_H

#include "core.h"
#include "atsp_decision.h"
#include "betatsp_core.h"

namespace problems{
namespace atsp {
namespace atsp_decision{

using s = solution_t;
using t = transformation_t;
using d = problem_data_t;


class BetATSP_Bet:
public core::Neighborhood<s,t>,
public core::Decorator<core::Neighborhood<s,t>>
{
public:

    BetATSP_Bet(typename Decorator<Neighborhood<s,t>>::ptr_t ptr,House& house):
        Decorator<Neighborhood<s,t>>(ptr),_house(house){}

    virtual std::vector<t> operator()( const s& s );

private:

    House& _house;
};

//class BetATSP_Check:
//public core::DeltaObjective<s,t,d,int>,
//public core::Decorator<core::DeltaObjective<s,t,d,int>>
//{
//public:
//    BetATSP_Check(typename Decorator<DeltaObjective<s,t,d>>::ptr_t ptr, House& house):
//        Decorator<DeltaObjective<s,t,d>>(ptr),_house(house){}

//    virtual void operator()( const s& solution,
//                             const std::vector<t>& trvec,
//                             typename DeltaObjective<s,t,d,int>::result_vector_type& resvec);
//private:

//    House& _house;

//};

}}}

#endif // BETATSP_DECORATORS_H
