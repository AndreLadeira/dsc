#ifndef PATH_H
#define PATH_H

#include "data.h"
#include "base/random.h"

namespace atsp
{

class Path
{

public:

    explicit Path(uint sz);
    Path(const atsp::Path &, uint pos, uint length);
    Path(const Path &);
    ~Path();

    Path & operator=(const Path &);
    uint const * getDataPtr() const;
    uint getSize() const;

private:

    uint _path[512]; // big buffer to avoid memory allocation
    uint _size;

private:

    friend inline void randomize(Path &, base::rand_fcn_t);
    friend inline void move(Path & p, uint insert, uint start, uint sz);
    friend std::ostream & operator << (std::ostream &, const Path & p);

    friend class Algorithm;
};


inline uint getLength(const Data & data, const Path & p)
{
    const auto db = data.getDataPtr();
    const auto size = p.getSize();
    const uint * path = p.getDataPtr();

    uint length = 0;

    for (uint i = 0; i < size - 1; ++i)
      length += db[ path[i] ][ path[i+1] ];

    // closes the loop
    length += db[ path[ size-1]][ path[0]];

    return length;
}

inline uint getLength(const Data & data, const Path & p, uint start, uint size)
{
    uint  _len = 0;
    for (uint i = start; i < start+size-1; ++i)
       _len += data.getDataPtr()[ p.getDataPtr()[i] ][ p.getDataPtr()[i+1] ];

    return _len;
}

inline void randomize(Path & p, base::rand_fcn_t rand = base::fast_rand)
{
    uint size = p._size;
    uint * path = p._path;

    // linear shuffle
    for(uint i = 0; i < size; ++i)
    {
        uint a = static_cast<uint>(rand()) % size;
        uint b = static_cast<uint>(rand()) % size;

        uint tmp = path[a];
        path[a] = path[b] ;
        path[b] = tmp;
    }
}

inline void move(Path & p, uint insert, uint start, uint sz)
{
    uint tmp[128];
    uint * _path = p._path;

    uint insert_corrected = insert < start ? insert : insert + sz;

    // copies the mask to the buffer
    for (uint i = 0; i < sz; i++)
        tmp[i] = _path[ start + i ];

    if ( start > insert_corrected )
    {
        uint span = start - insert_corrected - 1;

        // moves the elements
        for (uint i = 0; i < span; i++ )
            _path[ start + sz - 1 - i  ] = _path[ start + sz - 1 - i - sz ];
    }
    else
    {
        uint span = insert_corrected - start - sz + 1;

        for (uint i = 0; i < span; i++ )
            _path[ start + i  ] = _path[ start + i + sz ];
    }

    // copy the mask back to the path
    for (uint i = 0; i < sz; i++)
        _path[ insert + 1 + i ] = tmp[i];
}

}// ns atsp
#endif // PATH_H
