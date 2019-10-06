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

    using neighborhood_functor_ptr_t =
    std::shared_ptr<NeighborhoodFunctor<solution_t,transformation_t>>;


    NeighborhoodFunctorDecorator() = delete;
    NeighborhoodFunctorDecorator(neighborhood_functor_ptr_t F):_fptr(F){}

    virtual ~NeighborhoodFunctorDecorator() = default;
    virtual std::vector<solution_t> operator()( const solution_t & s ) = 0;


protected:

    neighborhood_functor_ptr_t _fptr;
};

template< typename solution_t , typename transformation_t >
class CallCounter : public NeighborhoodFunctorDecorator<solution_t,transformation_t>
{
public:
    using neighborhood_functor_ptr_t =
    typename NeighborhoodFunctorDecorator<solution_t,transformation_t>::neighborhood_functor_ptr_t;

    using base = NeighborhoodFunctorDecorator<solution_t,transformation_t>;

    CallCounter( neighborhood_functor_ptr_t F ):base(F),_counter(0){}

    virtual solution_t operator()(solution_t & s, size_t pos){
        ++_counter;
        return base::_fctor->operator()(s,pos);
    }

    unsigned int getCounter(){return _counter;}
    void resetCounter(){ _counter = 0;}

private:

    unsigned int _counter;
};

}}

#endif // NEIGHBORHOOD_DECORATORS_H
