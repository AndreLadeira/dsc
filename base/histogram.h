#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <string>

namespace base {

typedef unsigned int uint;

class HistBucket
{
    uint _min;
    uint _max;
    HistBucket * _next;
    uint _count;
    HistBucket( uint min, uint max, HistBucket * next = nullptr);
    void count( uint value);
    uint getMin() {return _min; }
    uint getMax() {return _max; }
    uint getCount() { return _count; }

    friend class Histogram;
};

HistBucket::HistBucket(uint min,uint max,HistBucket * next):
    _min(min),_max(max),_next(next),_count(0)
{
}
void HistBucket::count(uint value)
{
    if ( value < this->_max )
        this->_count++;
    else
        _next->count(value);
}

class Histogram
{
public:
    Histogram();
};

}
#endif // HISTOGRAM_H
