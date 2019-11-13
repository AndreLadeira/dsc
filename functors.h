#ifndef FUNCTORS_H
#define FUNCTORS_H

#include "noncopyable.h"
#include <iosfwd>

namespace core{

template< typename solution_t >
class Create : public NonCopyable
{
public:

    explicit Create() = default;
    virtual ~Create() = default;

    virtual solution_t operator()(void) = 0;
};


template< typename solution_t , typename transformation_t >
class Neighborhood : public NonCopyable
{
public:

    virtual ~Neighborhood() = default;
    virtual std::vector<transformation_t> operator()(const solution_t &) = 0;
};


template< typename solution_t, typename data_t, typename result_t = size_t >
class Objective : public NonCopyable
{
public:

    Objective():_data(nullptr){}
    explicit Objective(const data_t& d):_data(&d){}
    virtual ~Objective() = default;

    virtual result_t operator()(const solution_t&) = 0;

protected:

    const data_t * const _data;
};


template< typename solution_t, typename transformation_t, typename data_t, typename delta_t = int>
class DeltaObjective : public NonCopyable
{
public:

    DeltaObjective():_data(nullptr){}
    explicit DeltaObjective( const data_t & d ):_data(&d){}
    virtual ~DeltaObjective() = default;

    virtual std::vector<delta_t> operator()(
            const solution_t&, const std::vector<transformation_t>&) = 0;
protected:

    const data_t * const _data;
};

template< typename _delta_t = int >
class DeltaAccept : public NonCopyable
{
public:

    struct Result
    {
       bool accepted = false;
       size_t index = 0;
    };

    using delta_vector_t = std::vector<_delta_t>;
    using delta_t = _delta_t;

    DeltaAccept() = default;
    virtual ~DeltaAccept() = default;

    virtual Result operator()(const delta_vector_t&) const = 0;

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

#endif // FUNCTORS_H
