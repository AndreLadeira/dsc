#include <vector>
#include "path.h"
using namespace atsp;
using std::runtime_error;
using std::vector;


//==========================================================
path_::path_(uint sz, bool random, base::rand_fcn_t rnd):
    m_length_set(false),
    m_length_upto_set(false),
    m_length_forward_on_set(false)
{
    m_path.reserve(sz);
    for (uint i = 0; i<sz;++i)
        m_path.push_back(i);
    if (random) randomize(rnd);
}

path_::path_(const path_ &rhs)
{
   *this=rhs;
}

const uint & path_::at(uint pos) const
{
    if (pos >m_path.size())
        throw std::runtime_error("path::at: invalid position.");
    return m_path.at(pos);
}

path_ path_::subpath(const uint start, const uint length) const
{
    if (!length)
        throw std::runtime_error("path::subpath: length must be greater than zero.");
    if ( start + length - 1 > m_path.size() )
        throw std::runtime_error("path::subpath: invalid start/length.");

    path_ newp(length, false);
    auto begin = m_path.begin()+start;
    auto end   = m_path.begin()+start+length;

    newp.m_path = path_::path_t(begin,end);
    return  newp;
}
path_ &path_::operator =(const path_ & rhs)
{
    m_path.resize(rhs.m_path.size());
    m_path = rhs.m_path;

    m_length_set = false;
    m_length_upto_set = false;
    m_length_forward_on_set = false;
    return *this;
}
path_ &path_::operator +=(const path_ & rhs)
{
    m_path.insert(m_path.end(), rhs.m_path.begin(),rhs.m_path.end());
    m_length_set = false;
    m_length_upto_set = false;
    m_length_forward_on_set = false;
    return *this;
}
void path_::randomize(base::rand_fcn_t rnd)
{
    //linear shuffle
    auto sz = m_path.size();

    for(uint i = 0; i < sz; ++i)
    {
        uint a = static_cast<uint>(rnd()) % sz;
        uint b = static_cast<uint>(rnd()) % sz;

        uint tmp = m_path.at(a);
        m_path.at(a) = m_path.at(b) ;
        m_path.at(b) = tmp;
    }
    m_length_set = false;
    m_length_upto_set = false;
    m_length_forward_on_set = false;

}

uint path_::length(const data::data_matrix_t & db, bool force)
{
   if ( !m_length_set || force )
   {
       auto i = m_path.cbegin();
       auto j = ++m_path.cbegin();
       m_length = 0;

       while ( j != m_path.end()  )
       {
          m_length += db[*i][*j];
          i++;
          j++;
       }
       // closes the loop
       m_length += db[*i][*m_path.cbegin()];
       m_length_set = true;
   }
   return m_length;

}
uint path_::length_upto(const data::data_matrix_t & db, uint pos, bool force)
{
     if ( !m_length_upto_set || force )
     {
         m_length_upto.clear();
         m_length_upto.reserve( m_path.size() );

         auto i = m_path.cbegin();
         auto j = ++m_path.cbegin();

         m_length_upto.push_back(0);
         uint counter = 0;
         while ( j != m_path.end()  )
         {
             uint cost = db[*i++][*j++];
             m_length_upto.push_back( m_length_upto.at(counter++) + cost );
         }
         m_length_upto_set = true;
     }
     return m_length_upto.at(pos);
}
uint path_::length_forward_on(const data::data_matrix_t & db, uint pos, bool force)
{
    if ( !m_length_forward_on_set || force )
    {
        m_length_fwd.clear();
        m_length_fwd.reserve(m_path.size());
        m_length_fwd.push_back(0);

        uint length = this->length(db);
        uint pos = 1;
        while ( pos < m_path.size()  )
        {
            m_length_fwd.push_back( length - m_length_upto.at(pos++) );
        }
        m_length_forward_on_set = true;
    }
    return m_length_fwd.at(pos);
}

uint path_::shorten(const uint mstart, const uint mlength, const data::data_matrix_t & db)
{
    const uint this_pathsz = static_cast<uint>(this->m_path.size());

    path_ msk = this->subpath(mstart,mlength);
    const uint & msk_cost = msk.length_upto(db,mlength-1); // test mask size 1..ok!

    path_ x = this->subpath(0,mstart);
    x += this->subpath(mstart + mlength, this_pathsz - mstart - mlength);
    uint xlen = this_pathsz - mlength;

    const uint & ms = msk.at(0); // mask's 1st city
    const uint & me = msk.at(mlength-1); // mask's last city

    auto i = x.m_path.cbegin();
    auto j = ++x.m_path.cbegin();

    uint pos = 0;
    uint min_cost = this->length(db);
    uint mc_pos = 0;

    //uint trcost = x.length(db);

    //if ( trcost > min_cost ) return min_cost;

    while (j!= x.m_path.cend())
    {
       uint l1_cost = db[*i][ms];
       uint l2_cost = db[me][*j];

       uint cost = x.length_upto(db, pos) + l1_cost +
               msk_cost + l2_cost + x.length_forward_on(db, pos + 1);

       if ( cost < min_cost )
       {
           min_cost = cost;
           mc_pos = pos;
       }
       i++;
       j++;
       pos++;
    }

    // do the loop
    uint l1_cost = db[x.at(xlen-1)][ms];
    uint l2_cost = db[me][x.at(0)];

    uint cost = x.length_upto(db, xlen-1) + l1_cost +
            msk_cost + l2_cost;
    if ( cost < min_cost )
    {
        min_cost = cost;
        mc_pos = xlen-1;
    }

    if ( min_cost < this->length(db) )
    {
        path_ p = x.subpath(0,mc_pos+1);
        p += msk;
        if (mc_pos < xlen-1)
            p += x.subpath(mc_pos + mlength, this_pathsz - mc_pos - mlength -1);

        (*this) = p;
    }
    return  this->length(db);
}

