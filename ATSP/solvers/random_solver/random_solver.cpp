#include "random_solver.h"
#include "base/random.h"
#include "tsplib_reader/tsplib_reader.h"

using atsp::path;

path atsp::random_solver(char * const argv[])
{
    // extracts data from command arguments
    uint exec = 0;
    uint numexecs = 0;
    uint numiters = 0;
    uint msize = 0;
    uint mstart = 0;

    // opens the data file

    tsplib_reader tspdata("");
    path best;
    path attempt;

    while ( exec < numexecs )
    {
        atsp::assign_random(attempt,tspdata.size());

        for(uint iter = 0; iter < numiters; ++iter)
        {
            // get a randon position
            uint mask_start = 0;

            // evaluate the weights of transformations
            // with the current position and mask size

           attempt.getShortest(mstart,msize,tspdata);

            if ( best > attempt)
                best = attempt;
        }
        exec++;
    }
    return best;
}
