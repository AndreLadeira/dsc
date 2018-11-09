#include <iostream>
#include "tsplib_reader.h"
#include <fstream>
using namespace std;
using atsp::data::data_proxy;
using atsp::data::tsplib_reader;

#pragma GCC diagnostic ignored "-Wunused-parameter"

int main(int argc, char * argv[])
try
{
    data_proxy::instance().load( new tsplib_reader(argv[1]) );
    atsp::data::dump( data_proxy::instance().data_ptr(), cout );
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
