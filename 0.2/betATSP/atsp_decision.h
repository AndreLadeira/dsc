#ifndef ATSP_DECISION_H
#define ATSP_DECISION_H

#include <utility>
#include <vector>
#include <numeric>
#include <ostream>

#include "functors.h"

namespace algorithm{
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

using solution_t = std::vector< node_t >;
using transformation_t = std::pair<size_t,size_t>;
using problem_data_t = std::vector< std::vector<size_t> >;

using namespace core;

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


} // algorithm
} // atsp_decision
#endif // ATSP_H
