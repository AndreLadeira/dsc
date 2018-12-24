#ifndef PATH_H
#define PATH_H

#include "base/random.h"
#include "algorithm.h"
#include <ostream>


namespace atsp
{

class Path
{

public:

    Path();
    explicit Path(uint sz);
    Path(const Path &);
    Path(const Path &, uint pos, uint len); // cut construction
    ~Path();

    uint length() const;
    uint length(uint start, uint length);
    uint size() const;
    void randomize();
    void move(uint insertion, uint pos, uint length);
    uint shorten(atsp::algorithm *);

    static void setRandonFcn(base::rand_fcn_t);

    Path & operator=(const Path &);
    const uint & operator[](uint)const;

private:

    friend std::ostream & operator << (std::ostream &, const Path & p);

    uint *  _path;

    mutable bool    _length_set; // lazy evaluation
    mutable uint    _length;

    uint    _size; // size (#of vertices) on the path

    static base::rand_fcn_t _rnd_fcn;

    void set();
};


}
#endif // PATH_H
