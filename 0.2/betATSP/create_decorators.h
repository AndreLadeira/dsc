#ifndef CREATE_DECORATORS_H
#define CREATE_DECORATORS_H

#include "create_functor.h"
#include <memory>
#include <iostream>

namespace algorithm{
namespace core{


template< typename solution_t , typename problem_data_t >
class CreateFunctorDecorator : public CreateFunctor<solution_t,problem_data_t>
{
public:

    using create_functor_ptr_t =
    std::shared_ptr<CreateFunctor<solution_t,problem_data_t>>;


    CreateFunctorDecorator() = delete;
    CreateFunctorDecorator(create_functor_ptr_t F):_fctor(F){}

    virtual ~CreateFunctorDecorator() = default;
    virtual solution_t operator()(const problem_data_t & data,
                           size_t sz, const solution_t * const sol = nullptr) = 0;


protected:

    create_functor_ptr_t _fctor;
};

template< typename solution_t, typename problem_data_t >
class CallCounter : public CreateFunctorDecorator<solution_t, problem_data_t>
{
public:
    using create_functor_ptr_t =
    typename CreateFunctorDecorator<solution_t,problem_data_t>::create_functor_ptr_t;

    using base = CreateFunctorDecorator<solution_t,problem_data_t>;

    CallCounter( create_functor_ptr_t F ):base(F),_counter(0){}

    virtual solution_t operator()(const problem_data_t & data, size_t sz, const solution_t * const sol = nullptr){
        ++_counter;
        return base::_fctor->operator()(data,sz,sol);

    }

    unsigned int getCounter(){return _counter;}
    void resetCounter(){ _counter = 0;}

private:

    unsigned int _counter;
};

using std::ostream;
using std::cout;

template< typename solution_t, typename problem_data_t >
class PrintSolution : public CreateFunctorDecorator<solution_t, problem_data_t>
{
public:
    using create_functor_ptr_t =
    typename CreateFunctorDecorator<solution_t,problem_data_t>::create_functor_ptr_t;

    using base = CreateFunctorDecorator<solution_t,problem_data_t>;

    PrintSolution( create_functor_ptr_t F, ostream & os = cout):
        base(F),_counter(0),_os(os){}

    virtual solution_t operator()(const problem_data_t & data, size_t sz,
                           const solution_t * const sol = nullptr)
    {
        // get the newly created solution
        solution_t s = base::_fctor->operator()(data,sz,sol);
        //print it
        for (auto const& i: s) _os << i << " ";
        _os << "\n";
        return s;
    }
    unsigned int getCounter(){return _counter;}
    void resetCounter(){ _counter = 0;}

private:

    unsigned int _counter;
    ostream & _os;
};
}}

#endif // CREATE_DECORATORS_H
