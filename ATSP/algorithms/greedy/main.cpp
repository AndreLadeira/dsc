#include <iostream>
#include <iomanip>
#include <ctime>
#include "base/random.h"
#include "atsp/data.h"
#include "TSPLibLoader/TSPLibLoader.h"
#include "atsp/path.h"
#include "greedy_algorithm.h"
#include <limits>
#include <cmath>

using namespace std;

#pragma GCC diagnostic ignored "-Wunused-parameter"

int main(int argc, char * argv[])
try
{
    atsp::Data data;
    data.load( atsp::TSPLibLoader(argv[1]) );

    //std::cout<< data;

    uint runs    = static_cast<uint>(atoi( argv[2]) );
    uint iters   = static_cast<uint>(atoi( argv[3]) );
    uint msksz  = static_cast<uint>(atoi( argv[4]) );

    cout<<"\n\nATSP solution by random search\n";
    cout<<"\n\nData file: " << argv[1] << " (" << data.getSize() << " nodes)\n";
    cout<< runs << " executions, " << iters << " iterations per run.\n";
    cout<<"Mask size: " << msksz << "\n\n";
    cout<< "|0      50|      100|\n|" << flush;

    base::fast_srand();

    const uint dataSize = data.getSize();
    const uint mskRange = dataSize - msksz;

    atsp::Path current(dataSize);
    atsp::Path best = current;

    uint min = std::numeric_limits<uint>::max();

    atsp::GreedyAlgorithm greedyAlgorithm(msksz);

    clock_t begin = clock();

    float progress = 0.0f;
    uint  mult = 1;

    for (uint run = 0; run < runs; run++)
    {
        atsp::randomize(current);

        for (uint iter = 0; iter < iters; iter++)
        {
            greedyAlgorithm.setMask(static_cast<uint>(base::fast_rand()) % mskRange);

            uint r = greedyAlgorithm.run(current, data);

            if ( r < min )
            {
                min = r;
                best = current;
            }
        }
        progress = 100.0f * run / runs;
        if ( progress > mult * 5)
        {
            mult++;
            cout<<"|" << flush;
        }
    }

    cout<<"|" << endl;
    cout<< "Elapsed time: " << fixed << setprecision(2) <<
           (clock() - begin) / static_cast<double>(CLOCKS_PER_SEC) << endl;
    cout<< "Final result: " << min << endl;
    cout<< "Best path: " << best;

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
