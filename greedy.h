#ifndef GREEDY_H
#define GREEDY_H
#include "functors.h"

using namespace core;

namespace algorithms{
namespace greedy{

template< typename delta_t,
          typename Compare<delta_t>::compare_fcn_t compare >
class DeltaAcceptBestImprove : public core::DeltaAccept<delta_t, compare >
{
public:

    DeltaAcceptBestImprove() = default;
    virtual ~DeltaAcceptBestImprove() = default;

    virtual int operator()(const std::vector<delta_t>& delta_vec) const
    {
            int index = -1, i = 0;
            delta_t min_max = compare(0,1) ?
                            std::numeric_limits<delta_t>::max() :
                            std::numeric_limits<delta_t>::min();
            for(const auto& delta : delta_vec)
            {
                if ( compare(delta,0) && compare(delta,min_max) ) { min_max = delta; index = i;}
                i++;
            }
            return index;
    }
};

template< typename delta_t = int>
using DeltaAcceptBestIncrease = DeltaAcceptBestImprove<delta_t,Compare<delta_t>::greater>;

template< typename delta_t = int>
using DeltaAcceptBestDecrease = DeltaAcceptBestImprove<delta_t,Compare<delta_t>::less>;

template< typename delta_t,
          typename Compare<delta_t>::compare_fcn_t compare >
class DeltaAccept1stImprove : public core::DeltaAccept<delta_t, compare >
{
public:

    DeltaAccept1stImprove() = default;
    virtual ~DeltaAccept1stImprove() = default;

    virtual int operator()(const std::vector<delta_t>& delta_vec) const
    {
            int i = 0;
            for(const auto& delta : delta_vec)
            {
                if ( compare(delta,0) ) return i;
                i++;
            }
            return -1;
    }
};

template< typename delta_t = int>
using DeltaAccept1stIncrease = DeltaAcceptBestImprove<delta_t,Compare<delta_t>::greater>;

template< typename delta_t = int>
using DeltaAccept1stDecrease = DeltaAcceptBestImprove<delta_t,Compare<delta_t>::less>;

}
}

#endif // GREEDY_H
