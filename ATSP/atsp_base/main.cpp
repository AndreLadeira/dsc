#include <iostream>
#include "tsplib_reader/tsplib_reader.h"
#include "path.h"

using namespace std;
using atsp::data::data_proxy;
using atsp::data::tsplib_reader;

#pragma GCC diagnostic ignored "-Wunused-parameter"

int main(int argc, char * argv[])
try
{
    data_proxy::instance().load( new tsplib_reader(argv[1]) );
    const auto & data = data_proxy::instance().data_ptr();

    atsp::data::dump( data, cout );
    atsp::path p(data.size);
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
