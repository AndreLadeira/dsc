#ifndef GREEDYALGORITHM_H
#define GREEDYALGORITHM_H

#include "atsp/algorithm.h"
#include "atsp/data.h"

namespace atsp{

class GreedyAlgorithm : public Algorithm
{
public:

    explicit GreedyAlgorithm(uint masksz);
    virtual inline uint run(Path&, const Data &) const;
    void setMask(uint mask);
private:

    uint _msksz;
    uint _mask;
};


inline uint GreedyAlgorithm::run(Path & path, const Data & data) const
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

    // mask's 1st and last node
    const uint * _path  = path.getDataPtr();
    const uint * _pwm   = pwm.getDataPtr();

    const uint  m1st    = _path[ _mask ];
    const uint  mlast   = _path[ _mask + _msksz -1 ];
    const uint  pwm_sz  = pwm.getSize();
    uint        insert  = 0;

    const auto & db = data.getDataPtr();

    for (uint i = 0; i < pwm_sz - 1; ++i )
    {
        const uint len =
                pwm_length -                    // sub path original length
                db[ _pwm[i] ][ _pwm[i+1] ] +    // minus the way being disconnected
                db[ _pwm[i] ][ m1st ] +         // plus going into the mask
                msklen +                        // plus going through the mask
                db[ mlast ][ _pwm[i+1] ];       // plus going from the mask back to the path

        if (len < minlen)
        {
            insert = i;
            minlen = len;
        }
    }

    // try the last _postion

    const uint len =
            pwm_length -                            // sub path original length
            db[ _pwm[ pwm_sz - 1 ] ][ _pwm[ 0 ] ] + // minus the way being disconnected
            db[ _pwm[ pwm_sz - 1 ] ][ m1st ] +      // plus going into the mask
            msklen +                                // plus going through the mask
            db[ mlast ][ _pwm[ 0 ] ];               // plus going from the mask back to the path

    if (len < minlen)
    {
        insert = pwm_sz - 1;
        minlen = len;
    }

    if ( minlen < length )
    {
      move(path,insert,_mask,_msksz);

#ifdef __DEBUG__
       assert( p.length() == minlen );
#endif
    }
    return minlen;
}

}

#endif // GREEDYALGORITHM_H
