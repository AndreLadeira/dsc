#include <iostream>
#include "TSPLibLoader.h"
#include <fstream>

using namespace std;

#pragma GCC diagnostic ignored "-Wunused-parameter"

int main(int argc, char * argv[])
try
{
    atsp::Data data;

    data.load( atsp::TSPLibLoader(argv[1]) );
    cout << data;
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
