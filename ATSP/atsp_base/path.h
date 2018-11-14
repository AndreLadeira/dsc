#ifndef PATH_H
#define PATH_H

#include <forward_list>
#include "atsp_data.h"
#include "base/random.h"
#include <vector>

namespace atsp
{
typedef unsigned int uint;

class path_
{
public:
    // initializes the path with a random value
    path_(uint sz, bool random = true, base::rand_fcn_t rnd = base::fast_rand);
    path_(const path_ &);
    const uint & at(uint) const; // returns the value of the ith node on the path
    path_ subpath(const uint, const uint) const; // returns a subpath of the current path

    uint length(const data::data_t &, bool = false);
    uint length_upto(const data::data_t &, uint, bool = true);

public:

    path_ & operator = (const path_ &); // replaces the current conten of the path
    path_ &operator += (const path_ &); // add new data at path's end
    void randomize(base::rand_fcn_t = base::fast_rand);

private:
    typedef std::vector<uint> path_t;

    path_t              m_path;
    bool                m_length_set;
    bool                m_length_upto_set;


};

typedef std::forward_list<uint> path;

bool operator < (const path &, const path &);
bool operator > (const path &, const path &);

/*
 * Returns a value corresponding to the length (or weight)
 * of the given path, considering the given ATSP data
 *
 */

uint get_length(const path &, const data::data_t &);

/*
 * Returns a random path, given the path size.
 * The size correspond to the number of cities in the TS path.
 * The actual path length is size + 1, to account for the
 * to the fisrt city.
 */
void get_random( path &, const uint size, base::rand_fcn_t = base::fast_rand );

path get_subpath( const path &, const uint, const uint );
uint get_value( uint at );
path::const_iterator get_iterator(const path &,uint at);

void get_shortest(const path & path, const uint mstart, const uint mlength, const atsp::data::data_t & );

}
#endif // PATH_H
