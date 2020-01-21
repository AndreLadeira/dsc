#ifndef FUNCTORS_H
#define FUNCTORS_H

#include "core.h"

namespace core{

template< typename solution_t >
class Create : public NonCopyable
{
public:

    explicit Create() = default;
    virtual ~Create() = default;

    virtual solution_t operator()(void) = 0;
};


template< typename solution_t , typename transition_t >
class Neighborhood : public NonCopyable
{
public:

    virtual ~Neighborhood() = default;
    virtual std::vector<transition_t> operator()(const solution_t &) = 0;
};


template< typename solution_t, typename data_t, typename objective_t = int >
class Objective : public NonCopyable
{
public:

    Objective():_data(nullptr){}
    explicit Objective(const data_t& d):_data(&d){}
    virtual ~Objective() = default;

    virtual objective_t operator()(const solution_t&) = 0;

protected:

    const data_t * const _data;
};


template< typename solution_t, typename transition_t, typename data_t, typename delta_t = int>
class DeltaObjective : public NonCopyable
{
public:

    DeltaObjective():_data(nullptr){}
    explicit DeltaObjective( const data_t & d ):_data(&d){}
    virtual ~DeltaObjective() = default;

    virtual std::vector<delta_t> operator()(
            const solution_t&, const std::vector<transition_t>&) = 0;
protected:

    const data_t * const _data;
};

template< typename delta_t = int,
          typename Compare<delta_t>::compare_fcn_t = core::Compare<delta_t>::less >
class DeltaAccept : public NonCopyable
{
public:

    DeltaAccept() = default;
    virtual ~DeltaAccept() = default;

    virtual int operator()(const std::vector<delta_t>&) const = 0;

};

template< typename solution_t,
          typename objective_t>
class Update : public NonCopyable
{
public:

    Update(typename Compare<objective_t>::compare_fcn_t c = Compare<objective_t>::_true ):_compare(c){}
    virtual ~Update() = default;
    virtual bool operator()(solution_t& bestSoFar, objective_t& bsfCost,
                            const solution_t& candidate, const objective_t candidateCost ){
        if ( _compare(candidateCost, bsfCost) ){
            bsfCost = candidateCost;
            bestSoFar = candidate;
            return true;
        }
        return false;
    }
private:

    typename Compare<objective_t>::compare_fcn_t _compare;
};

template< typename solution_t, typename transition_t>
class Transform : public NonCopyable
{
public:

    Transform() = default;
    virtual ~Transform() = default;
    virtual void operator()(solution_t&, const transition_t&) = 0;
};


}

#endif // FUNCTORS_H
