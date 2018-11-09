#ifndef TSPLIB_READER_H
#define TSPLIB_READER_H

#include <string>
#include "../atsp_base/atsp_data.h"

namespace atsp
{
namespace data
{
class tsplib_reader : public data_loader
{
    void operator()( data_t & ) const;
public:
    tsplib_reader(const char * const & fname);
};
}
}
#endif // TSPLIB_READER_H
