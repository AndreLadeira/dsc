#ifndef RANDOM_H
#define RANDOM_H
#include <ctime>

namespace base
{
    extern unsigned int g_seed;
    extern const unsigned int rand_max;

    typedef int(*rand_fcn_t)(void);
    typedef void(*srand_fcn_t)(unsigned int);

    inline void fast_srand(unsigned int seed)
    {
        g_seed = seed;
    }

    inline void fast_srand(void)
    {
        g_seed = static_cast<unsigned int>(time(nullptr));
    }

    inline int fast_rand(void)
    {
        g_seed = (214013*g_seed+2531011);
        return (g_seed>>16)&rand_max;
    }
}

#endif // RANDOM_H
