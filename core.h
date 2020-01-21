#ifndef TYPES_H
#define TYPES_H

#include <memory>
#include <cmath>
#include <ctime>
#include <list>
#include <vector>
#include <numeric>
#include <iostream>

namespace core{

class NonCopyable
{
protected:
    NonCopyable() = default;
    ~NonCopyable() = default;
    NonCopyable( const NonCopyable& ) = delete;
    NonCopyable& operator=( const NonCopyable& ) = delete;
};

template<typename T>
struct Value
{
    Value():_v(T(0)){}
    Value(T v):_v(v){}
    Value(bool minimize):_v( minimize ? std::numeric_limits<T>::max() :
                                        std::numeric_limits<T>::min() ){}
    virtual ~Value() = default;
    virtual T getValue(void) const {return _v;}

protected:

    void setValue(T v){_v = v;}

    T _v;
};

template<typename T = size_t, bool resettable = false>
struct Counter : public Value<T>
{
    Counter() = default;
protected:
    void increment(T amount){ Value<T>::_v += amount;}
};

template<typename T = size_t>
struct Resettable : public Counter<T>
{
    Resettable() = default;
    void reset(){ Value<T>::_v = T(0);}
};

template<typename T = size_t, typename U = size_t>
struct Statistics;

template<typename T = size_t, typename U = size_t>
struct Record
{
    Record():_sz(0){}

    void add(T x, U y){
        _x.push_back(x);
        _y.push_back(y);
        _sz++;
    }

    void clear(){
        _x.clear();
        _y.clear();
        _sz = 0;
    }

    size_t size() const { return _sz; }
    std::vector<T> getX() const { return get<T>(_x); }
    std::vector<U> getY() const { return get<U>(_y); }

    template <T,U>
    friend std::ostream& operator<<(std::ostream& os, const Record<T,U>& r);
    friend struct Statistics<T,U>;

private:

    template<typename V> std::vector<V> get(const std::list<V>& list) const{
        return std::vector<V>(list.cbegin(), list.cend());
    }
    std::list<T> _x;
    std::list<U> _y;
    size_t _sz;
};

template<typename T, typename U>
struct Statistics
{
    Statistics(const Record<T,U>& r):_r(r){}

    double getAverage() const {
        if ( _r.size() ){
            U sum = std::accumulate(_r._y.cbegin(), _r._y.cend(), U(0) );
            return static_cast<double>(sum) / _r.size();
        }else return 0;
    }
    U getMin() const {
      return *std::min_element(_r._y.cbegin(), _r._y.cend());
    }
    U getMax() const {
      return *std::max_element(_r._y.cbegin(), _r._y.cend());
    }
    double getStdDev() const {
        if ( _r.size() ){
            double avg = getAverage();
            double accum = 0.0;
            for(const auto&x : _r._y)
                accum += (x - avg) * (x - avg);
            return std::sqrt( accum / _r.size() );
        }else return 0;
    }

private:

    const Record<T,U>&  _r;
};


template <typename tx, typename ty>
std::ostream& operator<<(std::ostream& os, const Record<tx,ty>& record){
    auto vx = record.getX();
    auto vy = record.getY();
    for(size_t i = 0; i < record.size(); ++i) os << vx.at(i) << "\t" << vy.at(i) << "\n";
    return os;
}

template< typename Tx = size_t, typename Ty = size_t >
struct Recorder
{
    Recorder():_started(true){}
    void start()   { _started = true; }
    void stop()    { _started = false; }
    void restart()  { _record.clear(); _started = true;}
    bool recording() const { return _started; }
    void record(Tx x, Ty y){ if ( recording() ) _record.add(x,y);}

    const Record<Tx,Ty>& getRecord() const {return _record; }

private:

  bool _started;
  Record<Tx,Ty> _record;

};

template<typename T>
struct Compare
{
    using compare_fcn_t = bool (*)(T,T);
    static bool less(const T a, const T b){return a<b;}
    static bool less_or_equal(const T a, const T b){return a<=b;}
    static bool greater(const T a, const T b){return a>b;}
    static bool greater_or_equal(const T a, const T b){return a>=b;}
    static bool equal_to(const T a, const T b){return a==b;}
    static bool _true(const T, const T){return true;}

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

template<typename T = size_t,
         typename Compare<T>::compare_fcn_t _compare_fcn = Compare<T>::less >
struct Progress : Value<double>
{
    Progress()
        :_compare(_compare_fcn),
          _v0(1),
         _vi( _compare(0,1) ? std::numeric_limits<T>::max(): std::numeric_limits<T>::min()){}

    void setInitialValue(T v0){ if ( v0 != 0) _v0 = v0; }
    void setProgress(T v){
        if( _compare(v,_vi) ){
            _vi = v;
            _v = std::abs( (static_cast<double>(_vi) - _v0)/_v0 );
        }
    }

protected:

    Compare<T> _compare;
    T _v0;
    T _vi;
};

template<typename T>
struct Decorator
{
    using ptr_t = std::shared_ptr<T>;
    Decorator(ptr_t& ptr):_ptr(ptr){}

protected:

    ptr_t _ptr;
};
template<typename id_t>
struct Identified
{
    explicit Identified(id_t id):_id(id){}
    id_t getId(){return _id;}
private:
    id_t _id;
};

}

#endif // TYPES_H
