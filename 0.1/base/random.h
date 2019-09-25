#ifndef RANDOM_H
#define RANDOM_H
#include <ctime>
#include <cstdlib>

namespace base
{
    extern unsigned int g_seed;
    extern const unsigned int rand_max;

    typedef int(*rand_fcn_t)(void);
    typedef void(*srand_fcn_t)(unsigned int);

    inline void fast_srand(unsigned int seed)
    {
        g_seed = seed;
        //std::srand(seed);
    }

    inline void fast_srand(void)
    {
        g_seed = static_cast<unsigned int>(time(nullptr));
        //std::srand(static_cast<unsigned int>(time(nullptr)));

    }

    inline int fast_rand(void)
    {
        g_seed = (214013*g_seed+2531011);
        return ((g_seed>>16)&rand_max);
        //return std::rand();
    }
    inline double fast_rand01(void)
    {
        g_seed = (214013*g_seed+2531011);
        return static_cast<double>((g_seed>>16)&rand_max) / rand_max;
        //return static_cast<double>( 1.0 * std::rand() / RAND_MAX );
        //return 1.00 * ((g_seed>>16)&rand_max) / rand_max;
    }
}

#endif // RANDOM_H
