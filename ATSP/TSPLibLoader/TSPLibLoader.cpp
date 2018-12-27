#include "TSPLibLoader.h"
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;
using namespace atsp;

TSPLibLoader::TSPLibLoader(const char * const &fname):_fname(fname){}

void TSPLibLoader::load(Data & data) const
{
   if (!_fname) throw runtime_error( string("TSPLibLoader(): file name not set.") );

   ifstream file(_fname);

   if ( !file.is_open() )
       throw runtime_error( string("TSPLibLoader(): file not found: ") + string(_fname) );

   string line;
   getline(file,line); // problem name

   smatch m;
   regex e("^\\s*NAME\\s*:\\s*(\\w+)");
   if ( !regex_search (line,m,e) )
       throw runtime_error( string("TSPLibLoader(): problem name not found in atsp file: ") + _fname );

   const string id(m[1]);

   getline(file,line); // type
   getline(file,line); // comment
   getline(file,line); // matrix size

   e = "^\\s*DIMENSION\\s*:\\s*(\\d+)";
   if ( !regex_search (line,m,e) )
       throw std::runtime_error( string("TSPLibLoader(): problem sz not found atsp file: ") + _fname);

   const uint size = static_cast<uint>(stoul(m[1]));

   set(data, id, size );

   getline(file,line); // weight type
   getline(file,line); // weight format
   getline(file,line); // weight section

   uint ** dataptr = DataLoader::getDataPtr(data);

   try
   {
       for( uint i = 0; i < size; ++i )
           for( uint j = 0; j < size; ++j )
               file >> dataptr[i][j];

   }
   catch(...)
   {
       throw runtime_error( string("TSPLibLoader(): error reading edge data from file: ") + _fname);
   }
}

