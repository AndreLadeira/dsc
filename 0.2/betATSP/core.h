#ifndef TYPES_H
#define TYPES_H

#include <memory>

namespace core{

template<typename T>
struct Value
{
    Value():_v(T(0)){}
    T getValue(void) const {return _v;}

protected:

    T _v;
};

template<typename T = size_t>
struct Accumulator : public Value<T>
{
    Accumulator() = default;
protected:
    void increment(T amount){ Value<T>::_v += amount;}
};

template<typename T = size_t>
struct Counter : public Accumulator<T>
{
    Counter() = default;
protected:
    void reset(){ Value<T>::_v = T(0);}
};

template<typename T>
struct Decorator
{
    using ptr_t = std::shared_ptr<T>;
    Decorator(ptr_t& ptr):_ptr(ptr){}

protected:

    ptr_t _ptr;
};

}

#endif // TYPES_H
