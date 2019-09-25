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
using atsp::bet::Player;

#pragma GCC diagnostic ignored "-Wunused-parameter"

int main(int argc, char * argv[])
try
{
    atsp::Data data;
    data.load( atsp::TSPLibLoader(argv[1]) );

    base::fast_srand();

    clock_t begin = clock();

    const uint trsz = 3;
    const uint numPicks = 3;
    const uint numPlayers = 30;

    atsp::Path current(data.getSize());
    atsp::Path best = current;

    Player players[numPlayers];
    Player::setGameParameters(data.getSize(),1.0,1000.0);

    for (uint i = 0; i < numPlayers; ++i)
        players[i].reset();

    atsp::bet::BetAlgorithm1 bet1(trsz, numPicks, players, numPlayers);

    uint runs  = 1; //100k
    uint iters = 5000;

    uint all_min = atsp::getLength(data,best);

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
        // Phase 2

    }

    cout<< "Elapsed time: " << fixed << setprecision(2) <<
           (clock() - begin) / static_cast<double>(CLOCKS_PER_SEC) << endl;
    cout<< "Final result: " << all_min << endl;


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
