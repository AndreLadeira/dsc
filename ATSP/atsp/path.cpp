#include "path.h"
#include <sstream>

atsp::Path::Path(uint sz):_size(sz)//:_path(nullptr),_size(0)
{
    reset(*this);
}

atsp::Path::~Path()
{
//    if (_path)
    //        delete [] _path;
}

atsp::Path &atsp::Path::operator=(const atsp::Path & rhs)
{
    _size = rhs._size;
    for (uint i = 0; i < _size; i++)
        _path[i] = rhs._path[i];

    return *this;
}

const uint *atsp::Path::getDataPtr() const
{
    return _path;
}

uint atsp::Path::getSize() const
{
    return this->_size;
}

atsp::Path::Path(const atsp::Path & p, uint pos, uint length):_size(p._size-length)//,_path(nullptr)
{
    // if (_size)
    //_path = new int[_size]

    // copies the original path up to the mask start

    std::memcpy(_path, p._path, (pos)*sizeof(uint) );

    // copies the original path from after the mask end to the end

    std::memcpy(_path + pos,
                p._path + pos + length,
                ( p._size - pos - length )*sizeof(uint) );

}

atsp::Path::Path(const atsp::Path & rhs):_size(rhs._size)
{
    for (uint i = 0; i < _size; i++)
        _path[i] = rhs._path[i];
}
