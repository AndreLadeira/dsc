#ifndef ATSP_DECISION_H
#define ATSP_DECISION_H

#include <utility>
#include <vector>
#include <numeric>
#include <ostream>

#include "functors.h"
#include "stdfunctors.h"

namespace problems{
namespace atsp {
namespace atsp_decision{

struct node_t
{
    node_t():prev(0),next(0){}
    node_t(size_t p, size_t n):prev(p),next(n){}
    size_t prev;
    size_t next;

    friend std::ostream& operator<<(std::ostream&, const node_t&);
};
std::ostream& operator<<(std::ostream&, const node_t&);

using path_t = std::vector<size_t>;
using solution_t = std::vector< node_t >;
using transformation_t = std::pair<size_t,size_t>;
using problem_data_t = std::vector< std::vector<size_t> >;

// solution to-from path conversions
void to_path(const solution_t&, path_t&);
void from_path(const path_t&, solution_t&);

class CreateRandom : public core::Create<solution_t>
{
public:
    CreateRandom(size_t sz):_size(sz){}
    virtual solution_t operator()(void);
private:
    size_t _size;
};

class Neighborhood : public core::Neighborhood<solution_t,transformation_t>
{
public:
    Neighborhood() = default;
    using trvec_t = std::vector<transformation_t>;
    virtual trvec_t operator()(const solution_t & s);
};

class Objective : public core::Objective<solution_t,problem_data_t>
{
public:

    explicit Objective(const problem_data_t& data):
        core::Objective<solution_t,problem_data_t>(data){}

    virtual int operator()(const solution_t&);

};

class DeltaObjective :
public core::DeltaObjective<solution_t,transformation_t, problem_data_t>
{
public:

    explicit DeltaObjective( const problem_data_t & data ):
        core::DeltaObjective<solution_t,transformation_t, problem_data_t>(data){}

    virtual std::vector<int> operator()(
            const solution_t &,const std::vector<transformation_t>&);
};

class Transform : public core::Transform<solution_t, transformation_t>
{
public:

    Transform() = default;
    virtual ~Transform() = default;
    virtual void operator()(solution_t&, const transformation_t&);
};


} // problems
} // atsp
} // atsp_decision
#endif // ATSP_H
