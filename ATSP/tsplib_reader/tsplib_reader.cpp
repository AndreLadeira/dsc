#include "tsplib_reader.h"
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;
using namespace atsp::data;

void tsplib_reader::operator()( data_t & data ) const
{
    ifstream file(m_fname);

   if ( !file.is_open() )
       throw runtime_error( string("tsplib_reader(): file not found: ") + string(m_fname) );

   string line;
   getline(file,line); // problem name

   smatch m;
   regex e("^\\s*NAME\\s*:\\s*(\\w+)");
   if ( !regex_search (line,m,e) )
       throw runtime_error( string("tsplib_reader(): problem name not found in atsp file: ") + m_fname );

   data.id = m[1];

   getline(file,line); // type
   getline(file,line); // comment
   getline(file,line); // matrix size

   e = "^\\s*DIMENSION\\s*:\\s*(\\d+)";
   if ( !regex_search (line,m,e) )
       throw std::runtime_error( string("tsplib_reader(): problem sz not found atsp file: ") + m_fname);

   data.size = static_cast<unsigned int>(stoul(m[1]));
   alloc(data);

   getline(file,line); // weight type
   getline(file,line); // weight format
   getline(file,line); // weight section

   try
   {
       for( uint i = 0; i< data.size; ++i )
           for( uint j = 0; j< data.size; ++j )
           {
               file >> data.data[i][j];
           }

   }
   catch(...)
   {
       throw runtime_error( string("tsplib_reader(): error reading edge data from file: ") + m_fname);
   }
}

tsplib_reader::tsplib_reader(const char * const &fname):data_loader(fname){}
