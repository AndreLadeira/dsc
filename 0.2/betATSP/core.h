#ifndef TYPES_H
#define TYPES_H
/*
template< typename result_t, typename solution_t, typename problem_data_t >
using objective_function_t = result_t (*)(solution_t, problem_data_t);

template< typename solution_t >
using neighborhood_function_t = void (*)(const solution_t &, solution_t &);

template< typename solution_t, typename problem_data_t >
using create_solution_function_t = solution_t (*)(const problem_data_t &);

template<typename solution_t>
using accept_solution_function_t = bool (*)(const solution_t &, const solution_t &);

template< typename function_t >
class Functor
{
public:
    Functor(function_t f):_fcn(f){}
    inline function_t operator()(void){ return _fcn; }
protected:
    function_t _fcn;
};

template< typename function_t >
class FunctorWithCallCounter : public Functor< function_t >
{
public:
    FunctorWithCallCounter(function_t f):_calls(0), Functor<function_t>(f){}
    unsigned int getTimesCalled(){ return _calls;}
    void resetCounter(){ _calls = 0; }

    inline function_t operator()(void){ ++_calls; return Functor<function_t>::_fcn; }

private:
    unsigned int _calls;
};

template < typename objective_function_t >
class ObjectiveFunctor : public FunctorWithCallCounter<objective_function_t>
{
public:
    ObjectiveFunctor(objective_function_t);
};

template < typename neighborhood_function_t >
class NeighborhoodFunctor : public FunctorWithCallCounter<neighborhood_function_t>
{
public:
    NeighborhoodFunctor(neighborhood_function_t);
};

template < typename create_solution_function_t >
class CreateSolutionFunctor : public FunctorWithCallCounter<create_solution_function_t>
{
public:
    CreateSolutionFunctor(create_solution_function_t);
};

template < typename accept_solution_function_t >
class AcceptSolutionFunctor : public FunctorWithCallCounter<accept_solution_function_t>
{
public:
    AcceptSolutionFunctor(accept_solution_function_t);
};

class NonCopyable
{
protected:
    NonCopyable() = default;
    ~NonCopyable() = default ;
    NonCopyable( const NonCopyable& ) = delete;
    NonCopyable& operator=( const NonCopyable& ) = delete;
};

template< typename create_solution_function_t,
          typename neighborhood_function_t,
          typename objective_function_t,
          typename accept_solution_function_t >
class Algorithm : public NonCopyable
{
protected:
    using create_solution_functor_t = CreateSolutionFunctor<create_solution_function_t>;
    using neighborhood_functor_t    = NeighborhoodFunctor<neighborhood_function_t>;
    using objective_functor_t       = ObjectiveFunctor<objective_function_t>;
    using accept_solution_functor_t = AcceptSolutionFunctor<accept_solution_function_t>;

public:
    void setCreateSolutionFunctor( create_solution_functor_t f){ _create_solution_functor = f;}
    void setNeighborhoodFunctor( neighborhood_functor_t f){ _neighborhood_functor = f;}
    void setObjectiveFunctor( objective_functor_t f ) { _objective_functor = f; }
    void setAcceptSolutionFunctor( accept_solution_functor_t f ) { _accept_solution_functor = f; }

    virtual void run(unsigned int) = 0;
    void setData(objective_function_t);
    void setInitialSolution( decltype (create_solution_function_t()));

protected:

    create_solution_functor_t    _create_solution_functor;
    neighborhood_functor_t       _neighborhood_functor;
    objective_functor_t          _objective_functor;
    accept_solution_functor_t    _accept_solution_functor;
};

*/
#endif // TYPES_H
