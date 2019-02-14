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

    uint msksz = 2;
    uint mskRange = data.getSize() - msksz;

    atsp::Path current(data.getSize());

    atsp::BettingPhase1 betting1(20, data.getSize(), msksz );

    for(uint i = 0; i < 1000 * 1000 * 10; i++)
    {
        betting1.setMask( static_cast<uint>(base::fast_rand()) % mskRange );
        res += betting1.run(current,data);
    }

    cout<< "Elapsed time: " << fixed << setprecision(2) <<
           (clock() - begin) / static_cast<double>(CLOCKS_PER_SEC) << endl;
    cout<< "Final result: " << res << endl;


    return 0;
}
