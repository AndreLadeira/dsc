#ifndef CREATEFUNCTOR_H
#define CREATEFUNCTOR_H

#include "noncopyable.h"
#include <utility>

namespace algorithm{
namespace core{

template< typename solution_t>
class CreateFunctor : public NonCopyable
{
public:

    explicit CreateFunctor() = default;
    virtual ~CreateFunctor() = default;

    virtual solution_t operator()(void) = 0;
};

}}

#endif // CREATEFUNCTOR_H
