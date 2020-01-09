#ifndef STDFUNCTORS_H
#define STDFUNCTORS_H

#include "functors.h"

namespace core{

template< typename delta_t = int,
          typename Compare<delta_t>::compare_fcn_t compare = Compare<delta_t>::less >
class DeltaAcceptBestImprove : public core::DeltaAccept<delta_t, compare >
{
public:

    DeltaAcceptBestImprove() = default;
    virtual ~DeltaAcceptBestImprove() = default;

    using Base = core::DeltaAccept<delta_t, compare>;

    virtual int operator()(const typename Base::delta_vector_t& delta_vec) const
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

template< typename delta_t = int,
          typename Compare<delta_t>::compare_fcn_t compare = Compare<delta_t>::less >
class DeltaAccept1stImprove : public core::DeltaAccept<delta_t, compare >
{
public:

    DeltaAccept1stImprove() = default;
    virtual ~DeltaAccept1stImprove() = default;

    using Base = core::DeltaAccept<delta_t, compare>;

    virtual int operator()(const typename Base::delta_vector_t& delta_vec) const
    {
            int i = 0;
            delta_t min_max = compare(0,1) ?
                            std::numeric_limits<delta_t>::max() :
                            std::numeric_limits<delta_t>::min();
            for(const auto& delta : delta_vec)
            {
                if ( compare(delta,0) && compare(delta,min_max) ) return i;
                i++;
            }
            return -1;
    }
};

}

#endif // STDFUNCTORS_H
