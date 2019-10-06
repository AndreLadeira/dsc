#ifndef NEIGHBORHOOD_H
#define NEIGHBORHOOD_H

#include "noncopyable.h"
#include <utility>
#include <vector>

namespace algorithm {
namespace core {

template< typename solution_t , typename transformation_t >
class NeighborhoodFunctor : NonCopyable
{
public:

    using neighborhood_function_t =
    std::vector<transformation_t> (*)(const solution_t &);

    explicit NeighborhoodFunctor(neighborhood_function_t f = nullptr):_fcn(f){}
    virtual ~NeighborhoodFunctor() = default;

    virtual std::vector<transformation_t> operator()(const solution_t &) = 0;

protected:

    neighborhood_function_t _fcn;
};

}}// namespace


#endif // NEIGHBORHOOD_H
