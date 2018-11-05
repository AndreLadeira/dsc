#include "tsplib_reader.h"
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

tsplib_reader::tsplib_reader(const char *fname):m_data(nullptr)
{
    ifstream file(fname);

    if ( !file.is_open() )
        throw runtime_error( string("tsplib_reader(): file not found: ") + string(fname) );

    string line;
    getline(file,line); // problem name

    smatch m;
    regex e("^\\s*NAME\\s*:\\s*(\\w+)");
    if ( !regex_search (line,m,e) )
        throw runtime_error( string("tsplib_reader(): problem name not found in atsp file: ") + fname );

    this->m_name = m[1];

    getline(file,line); // type
    getline(file,line); // comment
    getline(file,line); // matrix size

    e = "^\\s*DIMENSION\\s*:\\s*(\\d+)";
    if ( !regex_search (line,m,e) )
        throw std::runtime_error( string("tsplib_reader(): problem sz not found atsp file: ") + fname);

    this->m_sz = static_cast<unsigned int>(stoul(m[1]));
    this->m_data = new unsigned int*[this->m_sz];

    for(unsigned int i = 0; i<this->m_sz; ++i)
        this->m_data[i] = new unsigned int[this->m_sz];

    getline(file,line); // weight type
    getline(file,line); // weight format
    getline(file,line); // weight section

    m_max = 0;
    m_min = 999999999;

    try
    {
        for(unsigned int i=0;i<this->m_sz;++i)
            for(unsigned int j=0;j<this->m_sz;++j)
            {
                file >> this->m_data[i][j];
                if(i != j)
                {
                    if (m_data[i][j] > m_max) m_max = m_data[i][j];
                    if (m_data[i][j] < m_min) m_min = m_data[i][j];
                }

            }

    }
    catch(...)
    {
        throw runtime_error( string("tsplib_reader(): error reading edge data from atsp file: ") + fname);
    }

}

tsplib_reader::~tsplib_reader()
{
    for(unsigned int i=0;i<this->m_sz;++i)
    {
        if ( this->m_data[i] ) delete[] this->m_data[i];
        this->m_data[i] = nullptr;
    }
    if ( this->m_data ) delete[] this->m_data;
    this->m_data = nullptr;
}

unsigned int tsplib_reader::size() const
{
    return this->m_sz;
}

const unsigned int *tsplib_reader::operator[](const unsigned int i) const
{
    return this->m_data[i];
}

void tsplib_reader::print() const
{
    cout << "ATSP data file dump from atspdata reader\n";
        cout << "Problem name: " << this->m_name << endl;
        cout << "Dimension: " << this->m_sz << endl;
        cout << "Data (edge weights):\n";
        cout << "\nFirst 10x10 elements\n\n";

        for(unsigned int i = 0; i < 10;++i)
        {
            for(unsigned int j = 0; j < 10;++j)
                cout<< m_data[i][j] << " ";
            cout << endl;
        }

        cout << "\nLast 10x10 elements\n\n";

        for(unsigned long i = m_sz - 10; i < m_sz; ++i )
        {
            for(unsigned long j = m_sz - 10; j < m_sz; ++j )
                cout << m_data[i][j] << " ";

            cout << endl;
        }

        cout<< "\nEnd of atsplib file dump.\n";
}

unsigned int tsplib_reader::min() const
{
    return this->m_min;
}

unsigned int tsplib_reader::max() const
{
    return this->m_max;
}
