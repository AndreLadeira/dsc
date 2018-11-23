#ifndef TESTE_H
#define TESTE_H

typedef unsigned int uint;

inline int fast_rand(void)
{
    static int g_seed = 0;

    g_seed = (214013*g_seed+2531011);
        return (g_seed>>16)&0x7FFF;
}
template <typename T> void randomize( T & p)
{
    for (uint k = 0; k < 2000000; ++k)
    for(uint j = 0; j <10;j++)
    for(uint i = 0; i < 17; ++i)
    {
        uint a = static_cast<uint>(fast_rand()) % p.m_sz;
        uint b = static_cast<uint>(fast_rand()) % p.m_sz;

        uint tmp = p.m_path[a];
        p.m_path[a] = p.m_path[b] ;
        p.m_path[b] = tmp;
    }
}

struct A
{
    A(uint sz):m_sz(sz)
    {
        m_path = new uint[m_sz];
    }
    uint at(uint);
    ~A()
    {
        delete[] m_path;
    }
    uint * m_path;
    uint m_sz;
};

struct B
{
    B(uint sz);
    ~B();
    uint * m_path;
    uint m_sz;
};

#endif // TESTE_H
