#ifndef NEIGHBORHOOD_H
#define NEIGHBORHOOD_H

#include "noncopyable.h"
#include <utility>
#include <vector>

namespace algorithm {
namespace core {

template< typename solution_t , typename transformation_t >
class NeighborhoodFunctor : public NonCopyable
{
public:

    explicit NeighborhoodFunctor() = default;
    virtual ~NeighborhoodFunctor() = default;

    virtual std::vector<transformation_t> operator()(const solution_t &) = 0;

};

}}// namespace


#endif // NEIGHBORHOOD_H
