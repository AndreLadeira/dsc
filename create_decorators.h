#ifndef CREATE_DECORATORS_H
#define CREATE_DECORATORS_H

#include "create_functor.h"
#include "core.h"
#include <iostream>

namespace core{
namespace create{

template< typename T >
class CallCounter : public Create<T>, public Decorator<Create<T>>, public Counter<size_t>
{
public:

    CallCounter( typename Decorator<Create<T>>::ptr_t ptr ):
        Decorator<Create<T>>(ptr){}

    virtual T operator()(void){
        Counter::increment(1);
        return Decorator<Create<T>>::_ptr->operator()();
    }

};

template< typename T >
class PrintSolution : public Create<T>, public Decorator<Create<T>>
{
public:

    PrintSolution( typename Decorator<Create<T>>::ptr_t ptr, std::ostream & os = std::cout):
        Decorator<Create<T>>(ptr),_os(os){}

    virtual T operator()(void)
    {
        // get the newly created solution
        T s = Decorator<Create<T>>::_ptr->operator()();

        //print it
        for (auto const& i: s) _os << i << "\t";
        _os << "\n";

        // pass it along
        return s;
    }

private:

    std::ostream & _os;
};

}}

#endif // CREATE_DECORATORS_H
