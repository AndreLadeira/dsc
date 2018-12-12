
#include "path.h"
#include "data.h"

using namespace atsp;

#ifdef __DEBUG__
#include <cassert>
#include <iostream>
#endif

base::rand_fcn_t path::m_rnd_fcn = base::fast_rand;

// size constructor: constructs a new path given a size
// the path has initially the vertexes (cities) in order:
// 1,2,3...,N
path::path():m_sz(data::size)
{
    m_path = new uint[m_sz];
    for (uint i = 0; i <m_sz; ++i)
        m_path[i] = i;
}
path::path(uint sz):m_sz(sz)
{
    m_path = new uint[m_sz];
    for (uint i = 0; i <m_sz; ++i)
        m_path[i] = i;
}

// constructs a path from raw data: a pointer to a memory area
// and a size. This is used to speed some things up.
// Note to self: evaluate cons of changing to more robust c++

path::path(path_t ptr, uint sz)
{
    m_path = ptr;
    m_sz = sz;
    m_length_set = false;
}

// copy constructor: allocs memory and copies
// the path and its size

path::path(const path & rhs):m_sz(rhs.m_sz)
{
    m_path = new uint[m_sz];
    for (uint i = 0; i <m_sz; ++i)
        m_path[i] = rhs.m_path[i];
}



path &path::operator=(const path & rhs)
{
    for (uint i = 0; i <m_sz; ++i)
        m_path[i] = rhs.m_path[i];
    return *this;
}

path::~path()
{
    if (m_path) delete[] m_path;
}

void path::randomize()
{
    // linear shuffle
    for(uint i = 0; i < m_sz; ++i)
    {
        uint a = static_cast<uint>(m_rnd_fcn()) % m_sz;
        uint b = static_cast<uint>(m_rnd_fcn()) % m_sz;

        uint tmp = m_path[a];
        m_path[a] = m_path[b] ;
        m_path[b] = tmp;
    }
    m_length_set = false;
}

std::ostream & atsp::operator <<(std::ostream & os, const path & p)
{
    for (uint i = 0; i < p.m_sz -1; i++)
        os << p.m_path[i] << ", ";
    os << p.m_path[p.m_sz-1] << "\n";

    return os;
}

uint path::length()
{
   const auto & db = atsp::data::data;

   if ( !m_length_set )
   {
       m_length = 0;

       for (uint i = 0; i < m_sz - 1; ++i)
          m_length += db[ m_path[i] ][ m_path[i+1] ];
       // closes the loop
       m_length += db[m_path[m_sz-1]][m_path[0]];
       m_length_set = true;
   }
   return m_length;
}

uint path::shorten()
{

}

