#ifndef PATH_H
#define PATH_H

#include <forward_list>
#include "atsp_data.h"
#include "base/random.h"

namespace atsp
{

typedef unsigned int uint;
typedef std::forward_list<uint> path;

bool operator < (const path &, const path &);
bool operator > (const path &, const path &);

uint get_length(const path &, const data::data_t &);
void get_random( path &, const uint size, base::rand_fcn_t = base::fast_rand );
void get_best_tr(path & path, const uint mstart, const uint mlength, const atsp::data::data_t & );

}
#endif // PATH_H
