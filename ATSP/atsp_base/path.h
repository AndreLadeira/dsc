#ifndef PATH_H
#define PATH_H

#include "atsp_data.h"
#include "base/random.h"
#include <cstdlib>

namespace atsp
{
class path
{

    typedef uint * path_t;

public:

    path(uint sz, base::rand_fcn_t rnd_fcn = base::fast_rand);
    path(path_t ptr, uint sz, base::rand_fcn_t rnd_fcn = base::fast_rand);
    path(const path &, base::rand_fcn_t rnd_fcn = base::fast_rand);
    path& operator=(const path &);
    ~path();

    // path length functions
    uint length(const data::data_matrix_t &);
    uint shorten(const uint mask_start, const uint mask_length, const data::data_matrix_t &);
    void randomize();

private:

    friend std::ostream & operator << (std::ostream &, const path & p);

    path_t  m_path;
    bool    m_length_set;
    uint    m_length;
    uint    m_sz; // size (#of vertices) on the path

    const base::rand_fcn_t m_rnd_fcn;
};

}
#endif // PATH_H
