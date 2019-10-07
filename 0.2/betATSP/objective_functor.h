#ifndef OBJECTIVE_FUNCTOR_H
#define OBJECTIVE_FUNCTOR_H

#include "noncopyable.h"
#include <utility>
#include <memory>
#include <vector>

namespace algorithm {
namespace core {

template< typename solution_t,typename data_t, typename result_t = size_t>
using objective_function_t = result_t (*) (const solution_t&, const data_t&);

template< typename solution_t, typename transformation_t, typename data_t, typename result_t>
class DeltaObjectiveFunctor;

template< typename solution_t, typename data_t, typename result_t = size_t>
class ObjectiveFunctor : public NonCopyable
{
public:

    explicit ObjectiveFunctor(const data_t & d):_data(d){}
    virtual ~ObjectiveFunctor() = default;

    virtual size_t operator()(const solution_t&) const = 0;

protected:

    template< solution_t, typename transformation_t, data_t, result_t>
    friend class DeltaObjectiveFunctor;

    const data_t & _data;
};


template< typename solution_t, typename transformation_t, typename data_t, typename result_t = size_t>
class DeltaObjectiveFunctor : public NonCopyable
{
public:

    using objective_functor_t = const std::shared_ptr< const ObjectiveFunctor<solution_t,data_t,result_t> >;

    explicit DeltaObjectiveFunctor( objective_functor_t & d):_data(d){}
    virtual ~DeltaObjectiveFunctor() = default;

    virtual void operator()(const solution_t&,
                            const std::vector<transformation_t>&,
                            std::vector<result_t>&) const = 0;
protected:

    objective_functor_t & _data;
};


}}

#endif // OBJECTIVE_FUNCTOR_H
