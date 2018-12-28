#include <iostream>
#include <iomanip>
#include <ctime>
#include <limits>
#include <cmath>

#include "base/random.h"
#include "atsp/data.h"
#include "TSPLibLoader/TSPLibLoader.h"
#include "atsp/path.h"
#include "betting_algorithm.h"

using namespace std;

#pragma GCC diagnostic ignored "-Wunused-parameter"

int main(int argc, char * argv[])
{
    atsp::Data data;
    data.load( atsp::TSPLibLoader(argv[1]) );

    std::cout<< data;
    return 0;
}
