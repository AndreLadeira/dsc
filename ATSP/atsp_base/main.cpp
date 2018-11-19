#include <iostream>
#include <iomanip>
#include "tsplib_reader/tsplib_reader.h"
#include "path.h"
#include <boost/timer/timer.hpp>

using namespace std;
using atsp::data::data_proxy;
using atsp::data::tsplib_reader;
using boost::timer::cpu_timer;

#pragma GCC diagnostic ignored "-Wunused-parameter"

int main(int argc, char * argv[])
try
{
    base::fast_srand(); // start the randon number generator

    data_proxy::instance().load( new tsplib_reader(argv[1]) );
    const auto & db = data_proxy::instance().data_ptr();
    const auto & data = db.data;

    //atsp::data::dump( db, cout );
    atsp::path_ p(db.size);
    uint min = 999999;
    cpu_timer timer;
    for (int i =0; i < 2000000; i++)
    {
        p.randomize();
        //std::cout << p.length(data) << "\n";
        //std::cout << p.length_upto(data,16) << "\n";
        //std::cout << p.length_forward_on(data,5) << "\n";
        uint cmin = p.shorten(5,1,data);
        //std::cout << cmin << "\n";
        if (cmin < min) min = cmin;
    }
    std::cout << "minimum: " << min << "\n";
    cout<< "Elapsed time: " << fixed << setprecision(2) << timer.elapsed().wall / 1.0e09 << endl;
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
