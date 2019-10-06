#ifndef ATSP_DECISION_H
#define ATSP_DECISION_H

#include <utility>
#include <vector>
#include <numeric>

#include "functors.h"

namespace algorithm{
namespace atsp_decision{

using node_t = std::pair<size_t,size_t>;
using solution_t = std::vector< node_t >;
using problem_data_t = std::vector< std::vector<size_t> >;

solution_t create_function_basic(const problem_data_t & data,
                                size_t sz,
                                const solution_t * const = nullptr)
{
    // create a random path

    std::vector<size_t> path(sz+1);
    std::iota(path.begin(),path.end()-1,0);

    // begin+1 / end-1 to make paths always starting and ending at city 0,
    // with no loss of generality

    std::random_shuffle(path.begin()+1,path.end()-1);

    // store it in the decision-node structure
    solution_t s(sz);
    for(size_t i = 0; i < sz; ++i)
    {
        auto city = path.at(i);
        auto next_city = path.at(i+1);
        s.at(city).second = next_city;
        s.at(next_city).first = city;
    }

    return s;
}


} // algorithm
} // atsp_decision
#endif // ATSP_H
