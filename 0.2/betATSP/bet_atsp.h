#ifndef BET_ATSP_H
#define BET_ATSP_H

#include "neighborhood_functor.h"
#include "core.h"

using algorithm::core::Neighborhood;
using algorithm::core::Decorator;

namespace problems{
namespace atsp {
namespace atsp_decision{

template< typename S , typename T >
class BetATSP:
public Neighborhood<S,T>, public Decorator<Neighborhood<S,T>>
{
public:
    BetATSP(typename Decorator<Neighborhood<S,T>>::ptr_t ptr):
        Decorator<Neighborhood<S,T>>(ptr){}

    virtual std::vector<T> operator()( const S& s )
    {
        auto transfs = Decorator<Neighborhood<S,T>>::_ptr->operator()(s);

        for(const auto & t : transfs)
        {

        }
    }

};


}}}
#endif // BET_ATSP_H
