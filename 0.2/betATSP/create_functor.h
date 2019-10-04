#ifndef CREATEFUNCTOR_H
#define CREATEFUNCTOR_H

#include "noncopyable.h"
#include <utility>

template< typename solution_t , typename problem_data_t >
class CreateFunctor : NonCopyable
{
public:

    using create_function_t =
        solution_t (*)(const problem_data_t &, size_t, const solution_t * const);

    explicit CreateFunctor(create_function_t f = nullptr):_fcn(f){}
    virtual ~CreateFunctor() = default;

    virtual solution_t operator()(
            const problem_data_t & data,
            size_t sz,
            const solution_t * const sol = nullptr)
    {
        return _fcn(data,sz,sol);
    }

protected:

    create_function_t _fcn;
};


#endif // CREATEFUNCTOR_H
