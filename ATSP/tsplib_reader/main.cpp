#include <iostream>
#include "tsplib_reader.h"

using namespace std;

#pragma GCC diagnostic ignored "-Wunused-parameter"

int main(int argc, char * argv[])
try
{
   tsplib_reader data(argv[1]);
   data.print();
   return 0;
}
catch( std::exception & e)
{
    std::cout<< e.what() << endl;
}
catch(...)
{
    std::cout<<"Unknown exception caught in main()\n";
}
