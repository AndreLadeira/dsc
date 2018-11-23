#include "teste.h"


B::B(uint sz):m_sz(sz)
{
    m_path = new uint[m_sz];
}

B::~B()
{
    delete [] m_path;
}

uint A::at(uint pos)
{
    return m_path[pos];
}
