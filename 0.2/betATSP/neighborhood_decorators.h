#ifndef NEIGHBORHOOD_DECORATORS_H
#define NEIGHBORHOOD_DECORATORS_H

#include "neighborhood_functor.h"
#include <memory>

namespace algorithm{
namespace core{


template< typename solution_t , typename transformation_t >
class NeighborhoodFunctorDecorator : public NeighborhoodFunctor<solution_t,transformation_t>
{
public:

    using functor_ptr_t =
    std::shared_ptr<NeighborhoodFunctor<solution_t,transformation_t>>;

    NeighborhoodFunctorDecorator() = delete;
    NeighborhoodFunctorDecorator(functor_ptr_t F):_fptr(F){}

    virtual ~NeighborhoodFunctorDecorator() = default;
    virtual std::vector<solution_t> operator()( const solution_t & s ) = 0;

protected:

    functor_ptr_t _fptr;
};

template< typename S , typename T >
class NeighborhoodFunctorCallCounter : public NeighborhoodFunctorDecorator<S,T>
{
public:

    using base = NeighborhoodFunctorDecorator<S,T>;
    using functor_ptr_t = typename base::neighborhood_functor_ptr_t;

    NeighborhoodFunctorCallCounter( functor_ptr_t F ):base(F),_counter(0){}

    virtual std::vector<S> operator()( const S & s ){
        ++_counter;
        return base::_fptr->operator()(s);
    }

    unsigned int getCounter(){return _counter;}
    void resetCounter(){ _counter = 0;}

private:

    unsigned int _counter;
};

}}

#endif // NEIGHBORHOOD_DECORATORS_H
