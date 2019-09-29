#ifndef TYPES_H
#define TYPES_H

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
private:
    function_t _fcn;
};

template< typename function_t >
class FunctorWithCallCounter : public Functor< function_t >
{
public:
    FunctorWithCallCounter(function_t f):_calls(0), Functor<function_t>(f){}
    unsigned int getCalls(){ return _calls;}
    void resetCallCaounter(){ _calls = 0; }

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
public:
    void setCreateSolutionFunctor(
            CreateSolutionFunctor<create_solution_function_t> f){ _create_solution_functor = f;}
    void setNeighborhoodFunctor(
            NeighborhoodFunctor<neighborhood_function_t> f){ _neighborhood_functor = f;}
    void setObjectiveFunctor(
            ObjectiveFunctor<objective_function_t> f ) { _objective_functor = f; }
    void setAcceptSolutionFunctor(
            AcceptSolutionFunctor<accept_solution_function_t> f ) { _accept_solution_functor = f; }

    virtual void run() = 0;

private:

    CreateSolutionFunctor<create_solution_function_t> _create_solution_functor;
    NeighborhoodFunctor<neighborhood_function_t> _neighborhood_functor;
    ObjectiveFunctor<objective_function_t> _objective_functor;
    AcceptSolutionFunctor<accept_solution_function_t> _accept_solution_functor;
};


#endif // TYPES_H
