#ifndef CREATE_DECORATORS_H
#define CREATE_DECORATORS_H

#include "create_functor.h"
#include <memory>
#include <iostream>

namespace algorithm{
namespace core{


template< typename solution_t >
class CreateFunctorDecorator : public CreateFunctor<solution_t>
{
public:

    using functor_ptr_t = std::shared_ptr<CreateFunctor<solution_t> >;


    CreateFunctorDecorator() = delete;
    CreateFunctorDecorator(functor_ptr_t F):_fctor(F){}

    virtual ~CreateFunctorDecorator() = default;
    virtual solution_t operator()(void) = 0;


protected:

    functor_ptr_t _fctor;
};

template< typename solution_t >
class CreateFunctorCallCounter : public CreateFunctorDecorator<solution_t>
{
public:
    using base = CreateFunctorDecorator<solution_t>;
    using functor_ptr_t = typename base::functor_ptr_t;

    CreateFunctorCallCounter( functor_ptr_t F ):base(F),_counter(0){}

    virtual solution_t operator()(void){
        ++_counter;
        return base::_fctor->operator()();

    }

    unsigned int getCounter(){return _counter;}
    void resetCounter(){ _counter = 0;}

private:

    unsigned int _counter;
};

using std::ostream;
using std::cout;

template< typename solution_t >
class PrintSolution : public CreateFunctorDecorator<solution_t>
{
public:

    using base = CreateFunctorDecorator<solution_t>;
    using functor_ptr_t = typename base::functor_ptr_t;

    PrintSolution( functor_ptr_t F, ostream & os = cout):
        base(F),_os(os){}

    virtual solution_t operator()(void)
    {
        // get the newly created solution
        solution_t s = base::_fctor->operator()();
        //print it
        for (auto const& i: s) _os << i << "\t";
        _os << "\n";
        return s;
    }

private:

    ostream & _os;
};

}}

#endif // CREATE_DECORATORS_H
