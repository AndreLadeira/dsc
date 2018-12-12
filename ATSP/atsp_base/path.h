#ifndef PATH_H
#define PATH_H

#include "base/random.h"
#include <ostream>

namespace atsp
{

class path
{
    typedef unsigned int uint;
    typedef uint * path_t;

public:

    path();
    explicit path(uint sz);

    path(path_t ptr, uint sz);
    path(const path &);
    path& operator=(const path &);

    ~path();

    // path length functions

    uint length();
    uint shorten();
    void randomize();

    static void set_random_fcn(base::rand_fcn_t);

private:

    friend std::ostream & operator << (std::ostream &, const path & p);

    path_t  m_path;
    bool    m_length_set;
    uint    m_length;
    uint    m_sz; // size (#of vertices) on the path

    static base::rand_fcn_t m_rnd_fcn;
};

}
#endif // PATH_H
