#ifndef OBJECTIVE_H
#define OBJECTIVE_H

#include "noncopyable.h"
#include <utility>
#include <memory>
#include <vector>

namespace core {

template< typename solution_t, typename data_t, typename result_t = size_t>
class Objective : public NonCopyable
{
public:

    using result_type = result_t;

    Objective() = default;
    explicit Objective(const data_t & d):_data(d){}
    virtual ~Objective() = default;

    virtual result_t operator()(const solution_t&) = 0;

protected:

    const data_t _data;
};


template< typename solution_t, typename transformation_t, typename data_t, typename result_t = int>
class DeltaObjective : public NonCopyable
{
public:

    using result_type = result_t;
    using result_vector_type = std::vector<result_t>;

    DeltaObjective() = default;
    explicit DeltaObjective( const data_t & d ):_data(d){}
    virtual ~DeltaObjective() = default;

    virtual void operator()(const solution_t&,
                            const std::vector<transformation_t>&,
                            result_vector_type&) = 0;
protected:

    const data_t _data;
};

template< typename solution_t, typename transformation_t>
class Transform : public NonCopyable
{
public:

    Transform() = default;
    virtual ~Transform() = default;
    virtual void operator()(solution_t&, const transformation_t&) = 0;
};

}

#endif // OBJECTIVE__H
