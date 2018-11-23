#ifndef RANDOM_SOLVER_H
#define RANDOM_SOLVER_H

#include "atsp_base/path.h"

namespace atsp
{
   typedef unsigned int uint;
   inline path random_solver(   const char * const fname,
                                uint numexecs,
                                uint numiters,
                                uint msize);
}

#endif // RANDOM_SOLVER_H
