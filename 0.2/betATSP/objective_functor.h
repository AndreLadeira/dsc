#ifndef OBJECTIVE_FUNCTOR_H
#define OBJECTIVE_FUNCTOR_H

#include "noncopyable.h"
#include <utility>
#include <memory>
#include <vector>

namespace algorithm {
namespace core {


template< typename solution_t, typename data_t, typename result_t = size_t>
class ObjectiveFunctor : public NonCopyable
{
public:
    ObjectiveFunctor() = default;
    explicit ObjectiveFunctor(const data_t & d):_data(d){}
    virtual ~ObjectiveFunctor() = default;

    virtual result_t operator()(const solution_t&) = 0;

protected:

    const data_t _data;
};


template< typename solution_t, typename transformation_t, typename data_t, typename result_t = int>
class DeltaObjectiveFunctor : public NonCopyable
{
public:

    using result_type = result_t;
    using result_vector_type = std::vector<result_t>;

    DeltaObjectiveFunctor() = default;
    explicit DeltaObjectiveFunctor( const data_t & d ):_data(d){}
    virtual ~DeltaObjectiveFunctor() = default;

    virtual void operator()(const solution_t&,
                            const std::vector<transformation_t>&,
                            result_vector_type&) = 0;
protected:

    const data_t _data;
};

template< typename solution_t, typename transformation_t>
class TransformFunctor : public NonCopyable
{
public:


    TransformFunctor() = default;
    virtual ~TransformFunctor() = default;
    virtual void operator()(solution_t&, const transformation_t&) = 0;

};

}}

#endif // OBJECTIVE_FUNCTOR_H
