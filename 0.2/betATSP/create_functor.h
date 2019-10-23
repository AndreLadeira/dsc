#ifndef CREATEFUNCTOR_H
#define CREATEFUNCTOR_H

#include "noncopyable.h"
#include <utility>

namespace core{

template< typename solution_t>
class Create : public NonCopyable
{
public:

    explicit Create() = default;
    virtual ~Create() = default;

    virtual solution_t operator()(void) = 0;
};

}

#endif // CREATEFUNCTOR_H
