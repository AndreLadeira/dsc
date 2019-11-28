#ifndef TYPES_H
#define TYPES_H

#include <memory>
#include <cmath>
#include <ctime>

namespace core{

struct Ostreamable
{
    virtual void output(std::ostream& to) = 0;
    virtual~Ostreamable() = default;
};

template<typename T>
struct Value
{
    Value():_v(T(0)){}
    Value(T v):_v(v){}
    virtual ~Value() = default;
    virtual T getValue(void) const {return _v;}

protected:

    T _v;
};
template<typename T>
struct OstreamableValue :
        public Value<T>,
        public Ostreamable
{
  public:
    virtual void output(std::ostream &to) override
    {
        to << Value<T>::_v;
    }
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
struct Compare
{
    using compare_fcn_t = bool (*)(T,T);
    static bool less(const T a, const T b){return a<b;}
    static bool greater(const T a, const T b){return a>b;}
    static bool equal_to(const T a, const T b){return a==b;}

    Compare(compare_fcn_t c = less):_compare(c){}
    bool operator()(const T a, const T b) const { return _compare(a,b); }

private:

    compare_fcn_t _compare;

};

struct Timer : public Value<double>
{
    void start()
    {
        begin = clock();
    }
    virtual double getValue(void) const
    {
        return (clock() - begin) / static_cast<double>(CLOCKS_PER_SEC);
    }

private:
    clock_t begin;
};

template<typename T = size_t>
struct Progress : Value<double>
{
    Progress(T v, Compare<T> c = Compare<T>::less ):_v0(v),_vi(v),_compare(c){}
    void setProgress(T v){
        if( _compare(v,_vi) ){
            _vi = v;
            _v = std::abs( (static_cast<double>(_vi) - _v0)/_v0 );
        }
    }

protected:

    const T _v0;
    T _vi;
    Compare<T> _compare;

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
