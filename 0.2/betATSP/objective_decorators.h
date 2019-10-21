#ifndef OBJECTIVE_DECORATORS_H
#define OBJECTIVE_DECORATORS_H

#include "objective_functor.h"
#include "core.h"

namespace algorithm {
namespace core{
namespace objective{


template< typename S, typename D, typename R = size_t>
class CallCounter:
        public Objective<S,D,R>,
        public Decorator<Objective<S,D,R>>,
        public Counter<int>{

public:

    CallCounter() = delete;
    CallCounter( typename Decorator<Objective<S,D,R>>::ptr_t ptr ):
       Decorator<Objective<S,D,R>>(ptr){}

    virtual R operator()(const S& s){
        increment(1);
        return Decorator<Objective<S,D,R>>::_ptr->operator()(s);
    }
};

}}}

#endif // OBJECTIVE_DECORATORS_H
