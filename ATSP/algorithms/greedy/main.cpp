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
#include <fstream>
#include <sstream>

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

    cout<<"\n\nATSP solution by an random-restart, first-choice stochastic greedy algorithm.\n";
    cout<<"\n\nData file: " << argv[1] << " (" << data.getSize() << " nodes)\n";
    cout<< runs << " executions, " << iters << " iterations per run.\n";
    cout<<"Mask size: " << msksz << "\n\n";
    //cout<< "|0      50|      100|\n|" << flush;

    base::fast_srand();
    //std::srand( static_cast<unsigned int>(time(nullptr)));

    const uint dataSize = data.getSize();
    const uint mskRange = dataSize - msksz;

    atsp::Path current(dataSize);
    atsp::Path best = current;

    uint min = std::numeric_limits<uint>::max();

    atsp::GreedyAlgorithm greedyAlgorithm(msksz);

    clock_t begin = clock();

//    float progress = 0.0f;
//    uint  mult = 1;

    unsigned long long total = 0;

    //std::stringstream fname;
    //fname << time(nullptr) << ".txt";

    //std::ofstream outfile(fname.str());


    for (uint run = 0; run < runs; run++)
    {
        atsp::randomize(current);//, std::rand);
        //atsp::reset(current);
        //std::cout<< atsp::getLength(data,current) << "\n";

       //std::cout<< current;

        //std::cout<< "\n";

        //uint local_min = std::numeric_limits<uint>::max();;
        uint r = 0;

        for (uint iter = 0; iter < iters; iter++)
        {
            greedyAlgorithm.setMask(static_cast<uint>(base::fast_rand()) % mskRange);

            r = greedyAlgorithm.run(current, data);

            if ( r < min )
            {
                min = r;
                best = current;
            }
//            if (r < local_min)
//            {
//                local_min = r;
//            }


        }
        //std::cout<< atsp::getLength(data,current) << "\n";
        //std::cout<< current;
        //std::cout<< "\n";

//        progress = 100.0f * run / runs;
//        if ( progress > mult * 5)
//        {
//            mult++;
//            cout<<"|" << flush;
//        }
          total += r;
        //outfile << min << "\n";
    }

    //cout<<"|" << endl;
    cout<< "Elapsed time: " << fixed << setprecision(2) <<
           (clock() - begin) / static_cast<double>(CLOCKS_PER_SEC) << endl;
    cout<< "Final result: " << min << endl;
    cout<< "Average: " << static_cast<uint>( std::ceil( 1.0 * total / runs )) << "\n";
    //cout<< "Best path: \n";
    //std::cout<< best;

    //outfile.close();

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
