#ifndef PATH_H
#define PATH_H

#include <forward_list>

namespace atsp
{

typedef unsigned int uint;
typedef std::forward_list<uint> path;

bool operator < (const path &, const path &);
bool operator > (const path &, const path &);

uint get_length(const path &);
void assign_random( path &, uint size);
//void shorten(path & path, uint start, uint length, const atsp_data & data);

}
#endif // PATH_H
