#ifndef FUNCTOR_H
#define FUNCTOR_H

#include "noncopyable.h"

template< typename function_t >
class Functor : public NonCopyable
{
public:

    Functor(function_t f):_fcn(f){}
    function_t operator()(void){ return _fcn; }

protected:

    function_t _fcn;
};




#endif // FUNCTOR_H
