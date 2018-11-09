#include <regex>
#include "atsp_data.h"

using namespace atsp::data;
using namespace std;

void atsp::data::alloc(data_t & atsp_data)
{
    data_matrix_t & data = atsp_data.data;
    uint sz = atsp_data.size;

    data = data_matrix_t( new row_t[sz] );

    for( uint i = 0; i < sz; ++i )
        data[i] = row_t( new value_t[sz]);
}

void atsp::data::dump(const data_t & db, std::ostream & os)
{
    const data_matrix_t & data = db.data;
    const uint & sz = db.size;

    os << "--- atsp data dump ---\n";
    os << "Problem name: " << db.id << endl;
    os << "Dimension:    " << db.size << endl;
    os << "Data (edge weights)\n";
    os << "\nFirst 10x10 elements\n\n";

    for(unsigned int i = 0; i < 10;++i)
    {
        for(unsigned int j = 0; j < 10;++j)
            os<< data[i][j] << " ";
        os << endl;
    }

    os << "\nLast 10x10 elements\n\n";

    for(unsigned long i = sz - 10; i < sz; ++i )
    {
        for(unsigned long j = sz - 10; j < sz; ++j )
            os << data[i][j] << " ";

        os << endl;
    }

    os<< "\n--- end of atsp data dump ---\n";
}

data_loader::data_loader(const char * const & fname): m_fname(fname){}
data_loader::~data_loader(){}

data_t data_proxy::m_data;

data_proxy &data_proxy::instance()
{
  static data_proxy obj;
  return obj;
}
const data_t &data_proxy::data_ptr()
{
    return m_data;
}
void data_proxy::load(const data_loader * loader)
{
    (*loader)(m_data);
}
