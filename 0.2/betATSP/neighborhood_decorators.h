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
    NeighborhoodFunctorDecorator(functor_ptr_t F):_fctor(F){}

    virtual ~NeighborhoodFunctorDecorator() = default;
    virtual std::vector<transformation_t> operator()( const solution_t & s ) = 0;

protected:

    functor_ptr_t _fctor;
};

template< typename solution_t , typename transformation_t >
class NeighborhoodFunctorCallCounter :
        public NeighborhoodFunctorDecorator<solution_t,transformation_t>
{
public:

    using base = NeighborhoodFunctorDecorator<solution_t,transformation_t>;
    using functor_ptr_t = typename base::functor_ptr_t;

    NeighborhoodFunctorCallCounter( functor_ptr_t F ):base(F),_counter(0){}

    virtual std::vector<transformation_t> operator()( const solution_t & s ){
        ++_counter;
        return base::_fctor->operator()(s);
    }

    unsigned int getCounter(){return _counter;}
    void resetCounter(){ _counter = 0;}

private:

    unsigned int _counter;
};

}}

#endif // NEIGHBORHOOD_DECORATORS_H
