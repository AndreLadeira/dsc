#include <iostream>
#include <iomanip>
#include <ctime>
#include "base/random.h"
#include "data.h"
#include "TSPLibLoader/TSPLibLoader.h"
#include "path.h"
#include "algorithm.h"
#include <limits>
using namespace std;

#pragma GCC diagnostic ignored "-Wunused-parameter"

uint f(uint x)
{
    return x * x;
}

int main(int argc, char * argv[])
try
{
    atsp::Data data;
    data.load( atsp::TSPLibLoader(argv[1]) );

    std::cout<< data;

    uint runs    = static_cast<uint>(atoi( argv[2]) );
    uint iters   = static_cast<uint>(atoi( argv[3]) );
    uint msksz  = static_cast<uint>(atoi( argv[4]) );

    cout<<"\n\nATSP solution by random search\n";
    cout<<"\n\nData file: " << argv[1] << " (" << data.getSize() << " nodes)\n";
    cout<< runs << " executions, " << iters << " iterations per run.\n";
    cout<<"Mask size: " << msksz << "\n\n";
    cout<< "|0      50|      100|\n" << flush;

    base::fast_srand();

    const uint dataSize = data.getSize();
    const uint mskRange = dataSize - msksz;

    atsp::Path current(dataSize);
    atsp::Path best = current;

    uint min = std::numeric_limits<uint>::max();

    atsp::GreedyAlgorithm greedyAlgorithm(msksz);

    clock_t begin = clock();

    for (unsigned long long run = 0; run < runs; run++)
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
        if ( run % (runs / 20) == 0) cout<<"|" << flush;
    }

    cout<<"|" << endl;
    cout<< "Elapsed time: " << fixed << setprecision(2) <<
           (clock() - begin) / static_cast<double>(CLOCKS_PER_SEC) << endl;
    cout<< "Final result: " << min << endl;
    cout<< "Best path: " << best;

        return 0;
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
