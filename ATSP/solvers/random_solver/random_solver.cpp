#include "random_solver.h"
#include "base/random.h"
#include "tsplib_reader/tsplib_reader.h"
#include "atsp_base/atsp_data.h"
#include <ctime>
#include "base/random.h"

using atsp::path;
using atsp::data::data_proxy;
using atsp::data::tsplib_reader;


path atsp::random_solver(
        const char * const fname,
        uint numexecs,
        uint numiters,
        uint msize )
{
    // opens the data file

    data_proxy::instance().load( new tsplib_reader(fname) );
    const atsp::data::data_t & tspdata = data_proxy::instance().data_ptr();

    path best;
    path attempt;
    uint exec = 0;

    // set the random number generator
    base::fast_srand( static_cast<uint>(time(nullptr)));

    while ( exec < numexecs )
    {
        atsp::get_random_path(attempt,tspdata.size);

        for(uint iter = 0; iter < numiters; ++iter)
        {
            // get a randon position
            uint mstart = static_cast<uint>(base::fast_rand());

            // evaluate the weights of transformations
            // with the current position and mask size
            atsp::get_best_tr(attempt, mstart, msize, tspdata );

            if ( best > attempt)
                best = attempt;
        }
        exec++;
    }
    return best;
}
