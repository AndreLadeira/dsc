#ifndef OBJECTIVE_DECORATORS_H
#define OBJECTIVE_DECORATORS_H

#include "objective_functor.h"
#include <memory>

namespace algorithm {
namespace core{

template< typename solution_t , typename data_t, typename result_t = size_t>
class ObjectiveFunctorDecorator : public ObjectiveFunctor<solution_t,data_t, result_t>
{
public:

    using functor_ptr_t =
    std::shared_ptr< ObjectiveFunctor<solution_t,data_t, result_t> >;

    ObjectiveFunctorDecorator(functor_ptr_t F):_fctor(F){}

    virtual ~ObjectiveFunctorDecorator() = default;
    virtual result_t operator()(const solution_t&) = 0;

protected:

    functor_ptr_t _fctor;
};

template< typename solution_t , typename data_t, typename result_t = size_t>
class ObjectiveFunctorCallCounter :
        public ObjectiveFunctorDecorator<solution_t,data_t, result_t>
{
public:

    using base = ObjectiveFunctorDecorator<solution_t, data_t, result_t>;
    using functor_ptr_t = typename base::functor_ptr_t;

    ObjectiveFunctorCallCounter() = delete;
    ObjectiveFunctorCallCounter( functor_ptr_t F ):base(F),_counter(0){}

    virtual result_t operator()(const solution_t& s){
        ++_counter;
        return base::_fctor->operator()(s);
    }

    unsigned int getCounter(){return _counter;}
    void resetCounter(){ _counter = 0;}

private:

    unsigned int _counter;
};

}}

#endif // OBJECTIVE_DECORATORS_H
