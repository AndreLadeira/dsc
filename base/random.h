#ifndef RANDOM_H
#define RANDOM_H

namespace base
{
    extern unsigned int g_seed;
    inline void fast_srand(unsigned int seed)
    {
        g_seed = seed;
    }
    inline int fast_rand(void)
    {
        g_seed = (214013*g_seed+2531011);
            return (g_seed>>16)&0x7FFF;
    }
}

#endif // RANDOM_H
