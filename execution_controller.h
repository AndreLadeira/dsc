#ifndef EXECUTION_CONTROLLER_H
#define EXECUTION_CONTROLLER_H

#include "core.h"
#include <vector>

namespace core{

struct __Trigger
{
    virtual ~__Trigger() = default;
    virtual operator bool() const = 0;
};

template <typename T = size_t>
struct Trigger : public __Trigger
{
    Trigger(const std::shared_ptr<const Value<T>> valueptr, T limit , Compare<T> c = Compare<T>::greater ):
        _valueptr(valueptr),_limit(limit), _compare(c){}

    virtual operator bool() const
    {
        return _compare(_valueptr->getValue(),_limit);
    }

private:

    std::shared_ptr<const Value<T>> _valueptr;
    const T _limit;
    Compare<T> _compare;
};

class ExecutionController
{
public:

    using trigger_ptr_t = std::shared_ptr<__Trigger>;

    bool restart();
    bool stop();
    void addRestartTrigger( trigger_ptr_t );
    void addStopTrigger( trigger_ptr_t );

    private:

    std::vector<trigger_ptr_t> stopTriggers;
    std::vector<trigger_ptr_t> restartTriggers;
};

}
#endif // EXECUTION_CONTROLLER_H
