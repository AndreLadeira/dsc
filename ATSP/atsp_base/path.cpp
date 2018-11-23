
#include "path.h"
using namespace atsp;

#ifdef __DEBUG__
#include <cassert>
#include <iostream>
#endif

path::path(uint sz, base::rand_fcn_t rnd_fcn):m_sz(sz),m_rnd_fcn(rnd_fcn)
{
    m_path = new uint[m_sz];
    for (uint i = 0; i <m_sz; ++i)
        m_path[i] = i;
}
path::path(path_t ptr, uint sz, base::rand_fcn_t rnd_fcn):m_rnd_fcn(rnd_fcn)
{
    m_path = ptr;
    m_sz = sz;
    m_length_set = false;
}

path::path(const path & rhs, base::rand_fcn_t rnd_fcn):m_sz(rhs.m_sz),m_rnd_fcn(rnd_fcn)
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
    delete[]m_path;
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

uint path::length(const data::data_matrix_t & db)
{
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
uint path::shorten(const uint msk_start, const uint msk_size, const data::data_matrix_t & db)
{
    // gets a path without the mask.
    const path_t path_ptr = path_t(new uint[ m_sz - msk_size ] );

    // copies the original path up to the mask start
    std::memcpy(path_ptr, m_path, (msk_start)*sizeof(uint) );

    // copies the original path from after the mask end to the end
    std::memcpy(path_ptr + msk_start,
                m_path + msk_start + msk_size,
                ( m_sz - msk_start - msk_size )*sizeof(uint) );

    // construct a path object with the raw path_t data
    path path_wm(path_ptr, m_sz - msk_size);

    // store its size
    const uint path_wm_length = path_wm.length(db);

    // find the length of path along the mask
    uint msklen = 0; // optimization attempt
    for (uint i = 0; i < msk_size - 1; i++)
        msklen += db[ m_path[ i + msk_start ] ][ m_path[ i + msk_start + 1] ];

    // starts with the current length as the minimum
    uint minlen = this->length(db);

    // try # 1: single loop, no memory allocation
    // mask's 1st and last node

    const uint  m1st         = m_path[ msk_start ];
    const uint  mlast        = m_path[ msk_start + msk_size -1 ];
    const uint  path_wm_sz   = path_wm.m_sz;
    uint        pos          = 0;

    for (uint i = 0; i < path_wm_sz - 1; ++i )
    {

        const uint len =
                path_wm_length - // sub path original length
                db[ path_ptr[i] ][ path_ptr[i+1] ] + // minus the way being disconnected
                db[ path_ptr[i] ][ m1st ] + // plus going into the mask
                msklen + // plus going through the mask
                db[ mlast ][ path_ptr[i+1] ]; // plus going from the mask back to the path

        if (len < minlen)
        {
            pos = i;
            minlen = len;
        }
    }

    // try the last postion

    const uint len =
            path_wm_length - // sub path original length
            db[ path_ptr[ path_wm_sz - 1 ] ][ path_ptr[ 0 ] ] + // minus the way being disconnected
            db[ path_ptr[ path_wm_sz - 1 ] ][ m1st ] + // plus going into the mask
            msklen + // plus going through the mask
            db[ mlast ][ path_ptr[ 0 ] ]; // plus going from the mask back to the path

    if (len < minlen)
    {
        pos = path_wm_sz - 1;
        minlen = len;
    }

    if ( minlen < m_length )
    {
       path_t new_path_ptr = new uint[ m_sz ];

       // copies the original path up to the insertion point
       std::memcpy(new_path_ptr, path_ptr, ( pos + 1 )*sizeof(uint) );

       // copies the mask
       std::memcpy(new_path_ptr + pos + 1,
                   m_path + msk_start,
                   ( msk_size )*sizeof(uint) );

       // copies the rest of the path
       std::memcpy(new_path_ptr + pos + msk_size + 1,
                   path_ptr + pos + 1,
                   ( path_wm_sz - pos - 1 )*sizeof(uint) );

       delete [] m_path;
       m_path = new_path_ptr;
       m_length_set = false;

#ifdef __DEBUG__
       assert( length(db) == minlen );
#endif
    }
    return length(db);
}

