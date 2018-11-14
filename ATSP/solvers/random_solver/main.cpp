#include <iostream>
#include <iomanip>
#include <boost/timer/timer.hpp>
#include "random_solver.h"

using namespace std;
using boost::timer::cpu_timer;
using namespace atsp;

/*
 * argv[0]: exe name
 * argv[1]: tsplib file name
 * argv[2]: # of attempts
 * argv[3]: # of iterations per attempt
 * argv[4]: mask (transformation) size
 *
 */

int main(int argc, char *argv[] )
{
    if ( argc < 4 )
    {
        cout << "Usage: random_solver <file> <numexecs> <numiters> <mask size>";
        exit(0);
    }
    else
    {
        cpu_timer timer;
        path path = random_solver(argv);
        cout<< "Elapsed time: " << fixed << setprecision(2) << timer.elapsed().wall / 1.0e09 << endl;
        cout<< "Final result: " << get_length(path) << endl;
    }
    return 0;
}
