#include "tsplib_reader.h"
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;
using namespace atsp::data;

void tsplib_reader::operator()() const
{
   if (!m_fname) throw runtime_error( string("tsplib_reader(): file name not set.") );

   ifstream file(m_fname);

   if ( !file.is_open() )
       throw runtime_error( string("tsplib_reader(): file not found: ") + string(m_fname) );

   string line;
   getline(file,line); // problem name

   smatch m;
   regex e("^\\s*NAME\\s*:\\s*(\\w+)");
   if ( !regex_search (line,m,e) )
       throw runtime_error( string("tsplib_reader(): problem name not found in atsp file: ") + m_fname );

   data_loader::m_id = m[1];

   getline(file,line); // type
   getline(file,line); // comment
   getline(file,line); // matrix size

   e = "^\\s*DIMENSION\\s*:\\s*(\\d+)";
   if ( !regex_search (line,m,e) )
       throw std::runtime_error( string("tsplib_reader(): problem sz not found atsp file: ") + m_fname);

   this->set_size( static_cast<uint>(stoul(m[1])) );

   getline(file,line); // weight type
   getline(file,line); // weight format
   getline(file,line); // weight section

   try
   {
       for( uint i = 0; i< this->m_size; ++i )
           for( uint j = 0; j< this->m_size; ++j )
               file >> m_data[i][j];

   }
   catch(...)
   {
       throw runtime_error( string("tsplib_reader(): error reading edge data from file: ") + m_fname);
   }
}

tsplib_reader::tsplib_reader(const char * const & fname):data_loader(fname){}
