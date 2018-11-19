#include <iostream>
#include <ctime>
#include <iomanip>
#include <boost/timer/timer.hpp>

#include "random.h"

using namespace std;
using boost::timer::cpu_timer;

int main()
{
    base::fast_srand();
    cpu_timer timer;
    int hist[100]={0};

    for( uint i = 0; i < 1e09; i++)
    {
        int rnd = base::fast_rand() % 100;
        hist[rnd]++;
    }


    cout<< "Elapsed time: " << std::fixed << std::setprecision(2) << timer.elapsed().wall / 1.0e09 << endl;
}
