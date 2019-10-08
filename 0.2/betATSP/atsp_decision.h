#ifndef ATSP_DECISION_H
#define ATSP_DECISION_H

#include <utility>
#include <vector>
#include <numeric>
#include <ostream>

#include "functors.h"

namespace problems{
namespace atsp {
namespace atsp_decision{

struct node_t
{
    node_t():_node(){}
    node_t(size_t prev, size_t next):_node(prev,next){}
    size_t& prev = _node.first;
    size_t& next = _node.second;

    friend std::ostream& operator<<(std::ostream&, const node_t&);

private:

    std::pair<size_t,size_t> _node;
};

using path_t = std::vector<size_t>;
using solution_t = std::vector< node_t >;
using transformation_t = std::pair<size_t,size_t>;
using problem_data_t = std::vector< std::vector<size_t> >;

// solution to-from path conversions
void to_path(const solution_t&, path_t&);
void from_path(const path_t&, solution_t&);

using namespace algorithm;

class BasicCreateFunctor : public core::CreateFunctor<solution_t>
{
public:
    BasicCreateFunctor(size_t sz):_size(sz){}

    virtual solution_t operator()(void);

private:

    size_t _size;

};

class NeighborhoodFunctor : public core::NeighborhoodFunctor<solution_t,transformation_t>
{
public:
    NeighborhoodFunctor() = default;
    using trvec_t = std::vector<transformation_t>;

    virtual trvec_t operator()(const solution_t & s);

};

class ObjectiveFunctor : public core::ObjectiveFunctor<solution_t,problem_data_t,size_t>
{
public:
    using base = core::ObjectiveFunctor<solution_t,problem_data_t>;

    explicit ObjectiveFunctor(const problem_data_t& d):base(d){}
    virtual size_t operator()(const solution_t&);

};


class DeltaObjectiveFunctor :
public core::DeltaObjectiveFunctor<solution_t,transformation_t, problem_data_t>
{
public:

    using base = core::DeltaObjectiveFunctor<solution_t,transformation_t, problem_data_t>;
    using trvec_t = std::vector<transformation_t>;
    using resvec_t = std::vector<base::result_type>;

    explicit DeltaObjectiveFunctor( const problem_data_t & d ):base(d){}

    virtual void operator()(const solution_t &,
                            const trvec_t&,
                            resvec_t&);

};

class AcceptFunctor :
public core::AcceptFunctor<>
{
public:
    AcceptFunctor() = default;
    virtual ~AcceptFunctor() = default;

    virtual result_t operator()(const AcceptFunctor::delta_vector& ) const;

};

class TransformFunctor : public core::TransformFunctor<solution_t, transformation_t>
{
public:

    TransformFunctor() = default;
    virtual ~TransformFunctor() = default;
    virtual void operator()(solution_t&, const transformation_t&);
};

} // problems
} // atsp
} // atsp_decision
#endif // ATSP_H
