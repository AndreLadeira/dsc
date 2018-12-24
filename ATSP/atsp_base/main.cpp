#include <iostream>
#include <iomanip>
#include <ctime>
#include "base.h"
#include "tsplib_reader/tsplib_reader.h"

using namespace std;
using namespace atsp;

#pragma GCC diagnostic ignored "-Wunused-parameter"

int main(int argc, char * argv[])
try
{
    atsp::data::load( new data::tsplib_reader(argv[1]) );

    atsp::data::dump( cout );
    atsp::Path p;

    //p.move(2,10,3);
    //p.move(12,4,2);
    //p.move(13,0,1);
    //p.move(0,14,2);

    uint runs    = static_cast<uint>(atoi( argv[2]) );
    uint iters   = static_cast<uint>(atoi( argv[3]) );
    uint msk_sz  = static_cast<uint>(atoi( argv[4]) );

    cout<<"\n\nATSP solution by random search\n";
    cout<<"\n\nData file: " << argv[1] << " (" << data::size << " nodes)\n";
    cout<< runs << " executions, " << iters << " iterations per run.\n";
    cout<<"Mask size: " << msk_sz << "\n\n";
    cout<< "|0      50|      100|\n" << flush;

    uint min = std::numeric_limits<uint>::max();
    atsp::Path best(p);

    //base::fast_srand();
    const uint msk_range = data::size - msk_sz;

    clock_t begin = clock();
    atsp::greedy_algorithm * greedy = new atsp::greedy_algorithm();
    greedy->_length = msk_sz;

    for(uint run = 0; run < runs; run++)
    {
        p.randomize();
        for(uint iter = 0; iter < iters; ++iter)
        {
            greedy->_pos = static_cast<uint>(base::fast_rand()) % msk_range;
            uint cmin = p.shorten( greedy );
            if ( cmin < min )
            {
                min = cmin;
                best = p;
            }
        }
        if ( run % (runs / 20) == 0) cout<<"|" << flush;
    }

    cout<<"|" << endl;
    cout<< "Elapsed time: " << fixed << setprecision(2) <<
           (clock() - begin) / static_cast<double>(CLOCKS_PER_SEC) << endl;
    cout<< "Final result: " << min << endl;
    //cout<< "Best path: " << best;
    delete greedy;
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
