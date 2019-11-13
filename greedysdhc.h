#ifndef GREEDYSDHC_H
#define GREEDYSDHC_H
/*
#include "types.h"

template< typename create_solution_function_t,
          typename neighborhood_function_t,
          typename objective_function_t,
          typename accept_solution_function_t >
class GreedySDHC : public Algorithm<
        create_solution_function_t,
        neighborhood_function_t,
        objective_function_t,
        accept_solution_function_t>
{
    using Base = Algorithm<
    create_solution_function_t,
    neighborhood_function_t,
    objective_function_t,
    accept_solution_function_t >;
public:

    GreedySDHC() = default;

    virtual void run(unsigned int iters)
    {
        auto best_solution = Base::_create_solution_functor()();

        while (iters)
        {
            auto candidate_solution = Base::_neighborhood_functor()();
            auto candidate_result = Base::_objective_functor()(candidate);

            if ( accept_solution_function_t(candidate_solution, best_solution, iter ) )
                best_solution = candidate_solution;

            --iters;

        }
    }

};


//template<typename SolutionT, typename ProblemDataT, typename ResultT = int>
//void greedySDHC(
//        objectiveFunctionT<SolutionT,ProblemDataT, ResultT> objectiveFunction,
//        exploreNeighborhoodFunctionT<SolutionT>,
//        SolutionT & solution,
//        const ProblemDataT & problemData,
//        unsigned int iters
//        )
//{
//    ResultT best = objectiveFunction(solution, problemData);
     
//    while( iters )
//    {
//        SolutionT candidate = exploreNeigborhood(solution);
//        ResultT value = objectiveFunction(candidate, problemData);
        
//        if ( value < best ){
//            best = value;
//            solution = candidate;
//        }
        
//        iters--;
//    }
    
//}
*/
#endif // GREEDYSDHC_H
