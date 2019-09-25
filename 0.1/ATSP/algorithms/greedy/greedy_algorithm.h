#ifndef GREEDYALGORITHM_H
#define GREEDYALGORITHM_H

#include "atsp/algorithm.h"
#include "atsp/data.h"

#ifdef __DEBUG__
#include <cassert>
#endif

namespace atsp{

class GreedyAlgorithm : public Algorithm
{
public:

    explicit GreedyAlgorithm(uint masksz);
    virtual inline uint run(Path&, const Data &);
    void setMask(uint mask);
private:

    uint _msksz;
    uint _mask;
};


inline uint GreedyAlgorithm::run(Path & path, const Data & data)
{
    //  gets a path without the mask using a specialized constructor.

    const Path pwm(path,_mask,_msksz);
    const uint pwm_length = getLength(data,pwm);

    // finds the length of path along the mask
    uint msklen = getLength(data,path,_mask, _msksz);

    // current length of the path
    uint length = getLength(data, path);

    // starts with the current length as the minimum
    uint minlen = length;

    // direct, read only, acess pointers (remove function call)
    const uint * _path  = path.getDataPtr();
    const uint * _pwm   = pwm.getDataPtr();

    // mask's 1st and last node
    const uint  m1st    = _path[ _mask ];
    const uint  mlast   = _path[ _mask + _msksz -1 ];
    const uint  pwm_sz  = pwm.getSize();
    uint        insert  = 0;

    const auto & db = data.getDataPtr();

    // try re-inserting at every possible position

    for (uint i = 0; i < pwm_sz - 1; ++i )
    {
        // length calculation in constant time
        const uint len =
                pwm_length -                    // sub path original length minus
                db[ _pwm[i] ][ _pwm[i+1] ] +    // the way being disconnected plus
                db[ _pwm[i] ][ m1st ] +         // going into the mask plus
                msklen +                        // going through the mask plus
                db[ mlast ][ _pwm[i+1] ];       // going from the mask back to the path

        if (len < minlen)
        {
            insert = i;
            minlen = len;
        }
    }

    // try the last postion (from the last to the first city)

    const uint len =
            pwm_length -                            // sub path original length minus
            db[ _pwm[ pwm_sz - 1 ] ][ _pwm[ 0 ] ] + // the way being disconnected plus
            db[ _pwm[ pwm_sz - 1 ] ][ m1st ] +      // going into the mask plus
            msklen +                                // going through the mask plus
            db[ mlast ][ _pwm[ 0 ] ];               // going from the mask back to the path

    if (len < minlen)
    {
        insert = pwm_sz - 1;
        minlen = len;
    }

    // if a better path is found
    if ( minlen < length )
    {
      // then updates the current best

      move(path,insert,_mask,_msksz);

#ifdef __DEBUG__
       assert( atsp::getLength(data, path) == minlen );
#endif
    }
    return minlen;
}

}

#endif // GREEDYALGORITHM_H
