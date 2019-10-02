#ifndef NEIGHBORHOOD_H
#define NEIGHBORHOOD_H

#include "noncopyable.h"
#include <memory>

template< typename solution_t >
class NeighborhoodFunctor : NonCopyable
{
public:

    using neighborhood_function_t = void(*)(solution_t &, size_t pos);

    explicit NeighborhoodFunctor(neighborhood_function_t f = nullptr):_fcn(f){}
    virtual ~NeighborhoodFunctor() = default;

    virtual void operator()(solution_t & s) const
    {
        return _fcn(s);
    }

protected:

    neighborhood_function_t _fcn;
};

template< typename solution_t >
class NeighborhoodFunctorDecorator : public NeighborhoodFunctor<solution_t>
{
public:

    using neighborhood_functor_ptr_t =
    std::shared_ptr<NeighborhoodFunctor<solution_t>>;


    NeighborhoodFunctorDecorator() = delete;
    NeighborhoodFunctorDecorator(neighborhood_functor_ptr_t F):_fptr(F){}

    virtual ~NeighborhoodFunctorDecorator() = default;
    virtual void operator()(solution_t & s, size_t pos) = 0;


protected:

    neighborhood_functor_ptr_t _fptr;
};

template< typename solution_t >
class CallCounter : public NeighborhoodFunctorDecorator<solution_t>
{
public:
    using NeighborhoodFunctorDecorator =
    typename NeighborhoodFunctorDecorator<solution_t>::create_functor_ptr_t;

    using base = NeighborhoodFunctorDecorator<solution_t>;

    CallCounter( NeighborhoodFunctorDecorator F ):base(F),_counter(0){}

    virtual solution_t operator()(const problem_data_t & data, size_t sz, const solution_t * const sol = nullptr){
        ++_counter;
        return base::_fctor->operator()(data,sz,sol);

    }

    unsigned int getCounter(){return _counter;}
    void resetCounter(){ _counter = 0;}

private:

    unsigned int _counter;
};

//template< typename solution_t, typename problem_data_t >
//class PrintSolution : public CreateFunctorDecorator<solution_t, problem_data_t>
//{
//public:
//    using create_functor_ptr_t =
//    typename CreateFunctorDecorator<solution_t,problem_data_t>::create_functor_ptr_t;

//    using base = CreateFunctorDecorator<solution_t,problem_data_t>;

//    PrintSolution( create_functor_ptr_t F ):base(F),_counter(0){}

//    virtual solution_t run(const problem_data_t & data, size_t sz,
//                           const solution_t * const sol = nullptr)
//    {
//        return base::_fctor->operator()(data,sz,sol);
//    }
//    unsigned int getCounter(){return _counter;}
//    void resetCounter(){ _counter = 0;}

//private:

//    unsigned int _counter;
//};



#endif // NEIGHBORHOOD_H
