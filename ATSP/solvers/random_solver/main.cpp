#include <iostream>
#include <iomanip>
#include "random_solver.h"
#include "atsp_base/atsp_data.h"
#include "tsplib_reader/tsplib_reader.h"
#include "atsp_base/path.h"

using namespace std;
using namespace atsp;
using atsp::data::data_proxy;
using atsp::data::tsplib_reader;

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

    }
    return 0;
}
