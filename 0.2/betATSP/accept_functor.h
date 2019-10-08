#ifndef ACCEPT_FUNCTOR_H
#define ACCEPT_FUNCTOR_H

#include "noncopyable.h"
#include <utility>
#include <memory>
#include <vector>

namespace algorithm {
namespace core {

template< typename delta_t = int >
class AcceptFunctor : public NonCopyable
{
public:
    using delta_type = delta_t;
    using delta_vector = std::vector<delta_t>;
    using result_t = std::pair<bool,size_t>;

    AcceptFunctor() = default;
    virtual ~AcceptFunctor() = default;

    virtual result_t operator()(const delta_vector&) const = 0;

};

}}



#endif // ACCEPT_FUNCTOR_H
