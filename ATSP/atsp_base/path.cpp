#include <vector>
#include "path.h"
using namespace atsp;
using std::runtime_error;
using std::vector;

uint atsp::get_length(const path & p, const data::data_t & tspdata)
{
    auto i = p.cbegin();
    auto j = ++p.cbegin();
    uint len = 0;

    const atsp::data::data_matrix_t & db = tspdata.data;

    while ( j != p.end()  )
    {
       len += db[*i][*j];
       i++;
       j++;
    }
    return len;
}

void atsp::get_random(path & p, const uint sz, base::rand_fcn_t rnd)
{
    p.clear();

    path::iterator * it = new path::iterator[sz];

    for(uint i = 0; i <sz; ++i)
    {
        p.insert_after(p.before_begin(),i);
        it[i] = p.begin();
    }
    //linear shuffle
    for(uint i = 0; i <sz; ++i)
    {
        uint a = static_cast<uint>(rnd()) % sz;
        uint b = static_cast<uint>(rnd()) % sz;

        uint tmp = *it[a];
        *it[a] = *it[b];
        *it[b] = tmp;
    }
    // closes the loop
    p.insert_after(it[0],*it[sz-1]);
    delete [] it;
}

void get_shortest(path &p, const uint mstart, const uint mlength, const data::data_t & db)
{
//    // sanity check
//    if ( (mstart + mlength) > db.size )
//        throw runtime_error("path::get_shortest: inconsistent mask data (size, length).");

//    // find the nodes at the mask endpoints  (begin, end)
//    uint ms             = get_value(mstart);
//    uint me             = get_value(mstart+mlength-1);
//    uint mask_cost      = get_length( get_subpath(p,mstart,mlength), db );
//    auto mask_begin_it  = get_iterator(p,mstart-1);
//    auto mask_end_it    = get_iterator(p,mstart + mlength);

//    path X(p.cbegin(),mask_begin_it);
//    X.insert_after(X.end(),mask_end_it,p.cend());

//    uint Xcost              = get_length(X,db);
//    vector<uint> cost_upto;

//    // pointers to list items
//    uint counter = 0;
//    for( const auto & n:X  )
//    {
//        if ( counter == 0)
//        {
//            cost_upto.push_back(0);
//        }
//        else
//        {
//            uint cost = db.data[counter-1][counter];
//            cost_upto.push_back( cost_upto.at(counter) + cost );
//        }
//        counter++;
//    }
//    // get the index of the best transformation
//    uint best_length = std::numeric_limits<uint>::max();
//    uint index = 0;

//    for(uint i = 0; i < counter; i++)
//    {
//        uint cost_link1 = db.data[i][ms];
//        uint cost_link2 = db.data[me][i+1];

//        uint cost_forward_on = Xcost - cost_upto.at(i);

//        uint length = cost_upto.at(i) + cost_link1 + mask_cost + cost_link2 + cost_forward_on;

//        if ( length < best_length )
//        {
//            best_length = length;
//            index = i;
//        }
//    }
//    // save the best (shortest) path
//    if ( best_length < get_length(p,db) )
//    {
//        path res(p.cbegin(),get_iterator(p,index));
//        res.insert_after(res.end(), mask_begin_it++,mask_end_it);
//        res.insert_after(res.end(), get_iterator(p,index+1),p.cend());

//        path & q = const_cast<path &>(p);
//        q.assign(res.begin(),res.end());
//    }
//    // returns

}
//==========================================================
path_::path_(uint sz, bool random, base::rand_fcn_t rnd):
    m_length_set(false),m_length_upto_set(false)
{
    m_path.reserve(sz);
    if (random) randomize(rnd);
}

path_::path_(const path_ &rhs)
{
   *this=rhs;
}

const uint &path_::at(uint pos) const
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

    return *this;
}
path_ &path_::operator +=(const path_ & rhs)
{
    m_path.insert(m_path.end(), rhs.m_path.begin(),rhs.m_path.end());
    return *this;
}
void path_::randomize(base::rand_fcn_t rnd)
{
    //linear shuffle
    auto sz = m_path.size();

    for(auto i = 0u; i < sz; ++i)
    {
        uint a = static_cast<uint>(rnd()) % sz;
        uint b = static_cast<uint>(rnd()) % sz;

        uint tmp = m_path.at(a);
        m_path.at(a) = m_path.at(b) ;
        m_path.at(b) = tmp;
    }
}
uint path_::length(const data::data_t & tspdata, bool force)
{
   static uint length = 0;
   if ( !m_length_set || force )
   {
       auto i = m_path.cbegin();
       auto j = ++m_path.cbegin();
       length = 0;

       const atsp::data::data_matrix_t & db = tspdata.data;

       while ( j != m_path.end()  )
       {
          length += db[*i][*j];
          i++;
          j++;
       }
       // closes the loop
       length += db[*(j-1)][*m_path.cbegin()];
   }
   return length;

}
uint path_::length_upto(const data::data_t & tspdata, uint pos, bool force)
{
    static std::vector<uint> length_upto;
     if ( !m_length_set || force )
     {
         length_upto.clear();
         length_upto.reserve( m_path.size() + 1 );

         auto i = m_path.cbegin();
         auto j = ++m_path.cbegin();

         const auto & db = tspdata.data;
         length_upto.push_back(0);
         uint counter = 0;
         while ( j != m_path.end()  )
         {
             uint cost = db[*i][*j];
             length_upto.push_back( length_upto.at(counter++) + cost );
         }
     }
     return length_upto.at(pos);
}

