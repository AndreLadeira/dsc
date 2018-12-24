#ifndef TSPLIB_READER_H
#define TSPLIB_READER_H

#include <string>
#include "../atsp_base/data.h"

namespace atsp
{
namespace data
{
class tsplib_reader : public data_loader
{
    void operator()() const;
public:
    tsplib_reader(const char * const & fname);
};
}
}
#endif // TSPLIB_READER_H
