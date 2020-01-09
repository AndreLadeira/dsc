#ifndef TYPES_H
#define TYPES_H

#include <memory>
#include <cmath>
#include <ctime>
#include <list>
#include <vector>

namespace core{


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

template<typename Tx = size_t, typename Ty = size_t>
struct Record
{
    using data_t = std::pair<Tx,Ty>;

    Record():_sz(0){}

    void add(Tx x, Ty y) { add( data_t(x,y) ); }
    void add(data_t r) { _data.push_back(r); _sz++;}
    void clear() { _data.clear(); _sz = 0; }
    size_t size() const { return _sz; }

    std::vector<Tx> getX() const {
        std::vector<Tx> v(_sz);
        for(const auto &p : _data) v.push_back(p.first);
        return std::vector<Tx>(v);
    }

    std::vector<Ty> getY() const {
        std::vector<Ty> v(_sz);
        for(const auto &p : _data) v.push_back(p.second);
        return std::vector<Ty>(v);
    }

    template <typename tx, typename ty>
    friend std::ostream& operator<<(std::ostream& os, const Record<tx,ty>& r);

private:

    std::list<data_t> _data;
    size_t _sz;
};

template <typename tx, typename ty>
std::ostream& operator<<(std::ostream& os, const Record<tx,ty>& record){
    for(const auto& p: record._data) os << p.first << "\t" << p.second << "\n";
    return os;
}

template< typename Tx = size_t, typename Ty = size_t >
struct Recorder
{
    Recorder() = default;
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

}

#endif // TYPES_H
