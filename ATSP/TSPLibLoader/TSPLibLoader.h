#ifndef TSPLIB_READER_H
#define TSPLIB_READER_H

#include <string>
#include "../atsp_base/data.h"

namespace atsp
{

class TSPLibLoader : public DataLoader
{
public:
    TSPLibLoader(const char * const & fname);
private:
    virtual void load(Data &) const;
    const char * const & _fname;

};

}
#endif // TSPLIB_READER_H
