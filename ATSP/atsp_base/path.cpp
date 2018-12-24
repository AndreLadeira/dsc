
#include "path.h"
#include "data.h"
#include "algorithm.h"

using namespace atsp;

#ifdef __DEBUG__
#include <cassert>
#include <iostream>
#endif

base::rand_fcn_t Path::_rnd_fcn = base::fast_rand;

// size constructor: constructs a new path given a size
// the path has initially the vertexes (cities) in order:
// 1,2,3...,N

Path::Path():_size(data::size)
{
    set();
}
Path::Path(uint sz):_size(sz)
{
    set();

}

// constructs a path from raw data: a pointer to a memory area
// and a size. This is used to speed some things up.
// Note to self: evaluate cons of changing to more robust c++

Path::Path(const Path & rhs):_size(rhs._size)
{
    _path = new uint[_size];
    for (uint i = 0; i <_size; ++i)
        _path[i] = rhs._path[i];

    _length_set = false;
}

Path::Path(const Path & p, uint pos, uint length):_size(p._size-length)
{
    _path = new uint[_size];

    // copies the original path up to the mask start

    std::memcpy(_path, p._path, (pos)*sizeof(uint) );

    // copies the original path from after the mask end to the end

    std::memcpy(_path + pos,
                p._path + pos + length,
                ( p._size - pos - length )*sizeof(uint) );

    _length_set = false;
}

Path & Path::operator=(const Path & rhs)
{
    for (uint i = 0; i <_size; ++i)
        _path[i] = rhs._path[i];
    return *this;
}

const uint &Path::operator[](uint at) const
{
    return _path[at];
}

void Path::set()
{
    _path = new uint[_size];
    for (uint i = 0; i <_size; ++i)
        _path[i] = i;

    _length_set = false;
}

Path::~Path()
{
    if (_path) delete[] _path;
}

void Path::randomize()
{
    // linear shuffle
    for(uint i = 0; i < _size; ++i)
    {
        uint a = static_cast<uint>(_rnd_fcn()) % _size;
        uint b = static_cast<uint>(_rnd_fcn()) % _size;

        uint tmp = _path[a];
        _path[a] = _path[b] ;
        _path[b] = tmp;
    }
    _length_set = false;
}

void Path::move(uint ins, uint msk_init, uint msk_count)
{
    // attempt #1: no memory allocation. O( n * count )

    if ( msk_init > ins )
    {
        for ( uint i = 0; i < msk_count; ++i)
        {
            uint temp = _path[ msk_init + i];
            for ( uint j = 0; j < msk_init - ins - 1; ++j)
                _path[ msk_init + i - j ] = _path[ msk_init + i - j -1 ];
            _path[ ins + i + 1 ] = temp;
        }
    }
    else
    {
          for ( uint i = 0; i < msk_count; ++i)
          {
              uint temp = _path[ msk_init + msk_count - i - 1];

              for ( uint j = 0; j < ins - msk_init + 1; ++j)
                  _path[ msk_init + msk_count - i + j  - 1 ] = _path[ msk_init + msk_count - i + j ];

              _path[ ins + msk_count - i ] = temp;
          }

    }

    _length_set = false;
}

void Path::setRandonFcn(base::rand_fcn_t fcn)
{
   _rnd_fcn = fcn;
}

std::ostream & atsp::operator <<(std::ostream & os, const Path & p)
{
    for (uint i = 0; i < p._size -1; i++)
        os << p._path[i] << ", ";
    os << p._path[p._size-1] << "\n";

    return os;
}

uint Path::length() const
{
   const auto & db = atsp::data::data;

   if ( !_length_set )
   {
       _length = 0;

       for (uint i = 0; i < _size - 1; ++i)
          _length += db[ _path[i] ][ _path[i+1] ];
       // closes the loop
       _length += db[_path[_size-1]][_path[0]];
       _length_set = true;
   }
   return _length;
}

uint Path::length(uint start, uint size)
{
    const auto & db = atsp::data::data;

    uint  _len = 0;

    for (uint i = start; i < start+size-1; ++i)
       _len += db[ _path[i] ][ _path[i+1] ];

    return _len;
}

uint Path::size() const
{
    return _size;
}

uint Path::shorten(atsp::algorithm * shorten_algorithm)
{
    return (*shorten_algorithm)(*this);
}
