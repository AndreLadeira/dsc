#include "data.h"

using namespace atsp;
using namespace std;

Data::Data():_data(nullptr),_size(0){}
Data::~Data()
{
    release();
}

//uint const * Data::operator[](uint i) const
//{
//#ifdef __DEBUG__
//    if ( i >= _size )
//        throw runtime_error("Data::operator[]: index out of range.");
//    if ( !_data )
//        throw runtime_error("Data::operator[]: data not set.");
//#endif

//    return this->_data[i];
//}

uint Data::getSize() const
{
    return _size;
}

void Data::load(const DataLoader & loader)
{
    loader.load(*this);
}

void Data::malloc(uint size)
{
    if (_data) release();

    _size = size;

    _data = new uint * [_size];
    for(uint i = 0; i < _size; i++)
        _data[i] = new uint[_size]();
}

void Data::release()
{
    if (_data)
    {
        for(uint i = 0; i < 10; i++)
            delete[] _data[i];
        delete[] _data;
        _size = 0;
        _data = nullptr;
    }

}

DataLoader::~DataLoader()
{
}

void DataLoader::set(Data &d, string id, uint sz) const
{
    d.malloc(sz);
    d._id = id;
}

uint **DataLoader::getDataPtr(Data &d) const
{
    return d._data;
}

ostream & atsp::operator <<(ostream & os, const Data & d)
{
    os << "--- atsp data dump ---\n";
    os << "Problem name: " << d._id << endl;
    os << "Dimension:    " << d._size << endl;
    os << "Data (edge weights)\n\n";

    for(unsigned int i = 0; i < d._size; ++i)
    {
        for(unsigned int j = 0; j <d._size;++j)
            os<< d._data[i][j] << "\t";
        os << endl;
    }
    os<< "\n--- end of atsp data dump ---\n\n";
    return os;
}
