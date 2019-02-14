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
    friend inline void reset(Path &);
    friend inline void move(Path & p, uint insert, uint start, uint sz);
    friend inline void operator << (std::ostream &, const Path & p);

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
inline void reset(Path & p)
{
    for (uint i = 0; i < p._size; ++i)
            p._path[i] = i;
}

// create a new path by moving part of the path to another position
//
// The block that is moved: path[start] to path[start + sz]
// The insertion point: insert.
//


inline void move(Path & p, uint insert, uint start, uint sz)
{
    uint tmp[512]; // fixed size "big" buffer, to avoid memory allocation
    uint * _path = p._path;

    // The insertion point was obtained in a sub-path that did not contain
    // the block being moved
    // Example:
    //
    // Original path: ABCDEF
    // Part of the path being reinserted: 'C'
    // sub-path: ABDEF
    // insert possible values: 1,2,3,4,5
    // 1 = after A, 2 = after B ... 5 = after F
    //
    // so, if insert is bigger than start (e.g., the block is to be inserted
    // after its original position, 'C' inserted after D,E of F) a correction is
    // necessary

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

inline void operator <<(std::ostream & os, const Path & p)
{
    for (uint i = 0; i < p._size - 1; i++)
        os << p._path[ i ] << "\n";

    os << p._path[ p._size - 1 ] << "\n";

//        for (uint i = 0; i < p._size - 1; i++)
//            os << p._path[ i ] << " \t";

//        os << p._path[ p._size - 1 ] << "\n";
}

}// ns atsp
#endif // PATH_H
