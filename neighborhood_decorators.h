#ifndef NEIGHBORHOOD_DECORATORS_H
#define NEIGHBORHOOD_DECORATORS_H

#include "neighborhood_functor.h"
#include "core.h"

namespace core{
namespace neighbor{

template< typename S , typename T >
class CallCounter :
public Neighborhood<S,T>, public Decorator<Neighborhood<S,T>>, public Counter<size_t>
{
public:

    CallCounter(typename Decorator<Neighborhood<S,T>>::ptr_t ptr):
        Decorator<Neighborhood<S,T>>(ptr){}

    virtual ~CallCounter() = default;
    virtual std::vector<T> operator()( const S& s ){
        Counter::increment(1);
        return Decorator<Neighborhood<S,T>>::_ptr->operator()(s);
    }
};

template< typename S , typename T >
class NeighborCounter :
public Neighborhood<S,T>, public Decorator<Neighborhood<S,T>>, public Counter<size_t>
{
public:

    NeighborCounter(typename Decorator<Neighborhood<S,T>>::ptr_t ptr):
        Decorator<Neighborhood<S,T>>(ptr){}

    virtual ~NeighborCounter() = default;
    virtual std::vector<T> operator()( const S& s ){
        auto n = Decorator<Neighborhood<S,T>>::_ptr->operator()(s);
        Counter::increment(n.size());
        return n;
    }
};

}}

#endif // NEIGHBORHOOD_DECORATORS_H
