#include "path.h"
using namespace atsp;

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
    delete [] it;
}

void get_best_tr(path &path, const uint mstart, const uint mlength, const data::data_t &)
{

}
