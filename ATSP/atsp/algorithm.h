#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "path.h"
#include "data.h"
#include "base/random.h"

namespace atsp{

class Algorithm
{
public:
    virtual ~Algorithm();
    virtual inline uint run(Path&, const Data &) const = 0;

protected:

    inline uint * getPathPtr(Path& p) const
    {
        return p._path;
    }

};

}

#endif // ALGORITHM_H
