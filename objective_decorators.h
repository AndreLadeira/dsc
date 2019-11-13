#ifndef OBJECTIVE_DECORATORS_H
#define OBJECTIVE_DECORATORS_H

#include "objective_functor.h"
#include "core.h"

namespace core{
namespace objective{


template< typename S, typename D>
class CallCounter:
        public Objective<S,D>,
        public Decorator<Objective<S,D>>,
        public Counter<>{

public:

    CallCounter() = delete;
    CallCounter( typename Decorator<Objective<S,D>>::ptr_t ptr ):
       Decorator<Objective<S,D>>(ptr){}

    virtual size_t operator()(const S& s){
        increment(1);
        return Decorator<Objective<S,D>>::_ptr->operator()(s);
    }
};

}}

namespace core{
namespace deltaobjective{


template< typename S, typename T, typename D, typename R >
class CallCounter:
        public DeltaObjective<S,T,D,R>,
        public Decorator<DeltaObjective<S,T,D,R>>,
        public Counter<>{

public:

    CallCounter() = delete;
    CallCounter( typename Decorator<DeltaObjective<S,T,D,R>>::ptr_t ptr ):
       Decorator<DeltaObjective<S,T,D,R>>(ptr){}

    virtual void operator()(const S& s,
                            const std::vector<T>& trvec,
                            typename DeltaObjective<S,T,D,R>::result_vector_type& resvec ){
        increment(1);
        return Decorator<DeltaObjective<S,T,D,R>>::_ptr->operator()(s,trvec,resvec);
    }
};

}}

#endif // OBJECTIVE_DECORATORS_H
