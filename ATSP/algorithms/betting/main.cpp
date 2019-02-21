#include <iostream>
#include <iomanip>
#include <ctime>
#include <limits>
#include <cmath>

#include "base/random.h"
#include "atsp/data.h"
#include "TSPLibLoader/TSPLibLoader.h"
#include "atsp/path.h"
#include "betting_phase1.h"


using namespace std;

#pragma GCC diagnostic ignored "-Wunused-parameter"

int main(int argc, char * argv[])
{
    atsp::Data data;
    data.load( atsp::TSPLibLoader(argv[1]) );

    double res = 0;

    base::fast_srand();

    clock_t begin = clock();

    uint trsz = 3;
    uint trcount = 3;

    atsp::Path current(data.getSize());
    atsp::Path best = current;

    atsp::bet::Player players[30];

    for (uint i = 0; i < 30; ++i)
        players[i].reset(data.getSize(),1000.0);

    atsp::bet::BetAgorithm1 bet1(trsz, trcount, players, 30);

    uint runs  = 1e05; //100k
    uint iters = 500;

    uint all_min = std::numeric_limits<uint>::max();

    // phase 1

    for (uint run = 0; run < runs; run++)
    {
        atsp::randomize(current);

        for (uint iter = 0; iter < iters; iter++)
        {
            uint r = bet1.run(current, data);

            if ( r < all_min )
            {
                all_min = r;
                best = current;
            }

        }

    }

    cout<< "Elapsed time: " << fixed << setprecision(2) <<
           (clock() - begin) / static_cast<double>(CLOCKS_PER_SEC) << endl;
    cout<< "Final result: " << res << endl;


    return 0;
}
