#include "data.h"

using namespace atsp::data;
using namespace std;

namespace
{

// the actual data

matrix_t    dataObj = nullptr;
uint        sizeObj = 0;
string      idObj;

void release()
{
    for( uint i = 0; i < sizeObj; ++i )
        delete[] dataObj[i];

    delete[] dataObj;
    dataObj = nullptr;
}

// The idea here is to have a global variable and
// rely on its destructor to release any memory
// alocated on dataObj.

struct Releaser
{
   ~Releaser()
   {
      if (dataObj)
      {
          release();
      }
   }

} releaser;

}
// the constant read-only references

const const_matrix_t &  atsp::data::data    = dataObj;
const uint &            atsp::data::size    = sizeObj;
const string &          atsp::data::id      = idObj;

// the data read-write access points, available only to loaders

const_matrix_ptr_t &    data_loader::m_data   = dataObj;
const uint &            data_loader::m_size   = sizeObj;
string &                data_loader::m_id     = idObj;

data_loader::data_loader(const char * const & fname): m_fname(fname){}
data_loader::~data_loader(){}

void data_loader::set_size(uint sz)
{
    if (dataObj) release();

    sizeObj = sz;

    dataObj = matrix_t( new row_t[sizeObj] );

    for( uint i = 0; i < sizeObj; ++i )
        dataObj[i] = row_t( new uint[sizeObj]);

    // m_data[0][0] = 100; // OK
    // m_data[0] = nullptr; // compile error as expected
}

void atsp::data::dump(std::ostream & os)
{
    os << "--- atsp data dump ---\n";
    os << "Problem name: " << id << endl;
    os << "Dimension:    " << size << endl;
    os << "Data (edge weights)\n\n";

    for(unsigned int i = 0; i < size; ++i)
    {
        for(unsigned int j = 0; j < size;++j)
            os<< data[i][j] << "  ";
        os << endl;
    }
    os<< "\n--- end of atsp data dump ---\n";
}

void atsp::data::load(const data_loader * loader)
{
    (*loader)();
}
