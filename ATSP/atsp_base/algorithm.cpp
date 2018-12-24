#include "algorithm.h"
#include "path.h"
#include "data.h"
#include <cassert>

using namespace atsp::data;

atsp::algorithm::~algorithm(){}

//uint atsp::greedy_algorithm::_pos = 0;
//uint atsp::greedy_algorithm::length = 2;

atsp::greedy_algorithm::greedy_algorithm():_pos(0),_length(0)
{
}

uint atsp::greedy_algorithm::operator()(atsp::Path & p) const
{
   //  gets a path without the mask using a specialized constructor.
    const Path pwm(p,_pos,_length);
    const uint pwm_length = pwm.length();

//    // finds the length of path along the mask
    uint msklen = p.length(_pos,_length);

//    // starts with the current length as the minimum
    uint minlen = p.length();

//    // try # 1: single loop, no memory allocation
//    // mask's 1st and last node

    const uint  m1st    = p[ _pos ];
    const uint  mlast   = p[ _pos + _length -1 ];
    const uint  pwm_sz  = pwm.size();
    uint        insert  = 0;

    const auto & db = atsp::data::data;

    for (uint i = 0; i < pwm_sz - 1; ++i )
    {
        // if (i == _pos) continue;
        const uint len =
                pwm_length - // sub path original length
                db[ pwm[i] ][ pwm[i+1] ] + // minus the way being disconnected
                db[ pwm[i] ][ m1st ] + // plus going into the mask
                msklen + // plus going through the mask
                db[ mlast ][ pwm[i+1] ]; // plus going from the mask back to the path

        if (len < minlen)
        {
            insert = i;
            minlen = len;
        }
    }

//    // try the last _postion

//    const uint len =
//            pwm_length - // sub path original length
//            db[ pwm[ pwm_sz - 1 ] ][ pwm[ 0 ] ] + // minus the way being disconnected
//            db[ pwm[ pwm_sz - 1 ] ][ m1st ] + // plus going into the mask
//            msklen + // plus going through the mask
//            db[ mlast ][ pwm[ 0 ] ]; // plus going from the mask back to the path

//    if (len < minlen)
//    {
//        insert = pwm_sz - 1;
//        minlen = len;
//    }

//    if ( minlen < p.length() )
//    {
//      p.move(insert,_pos,_length);

//#ifdef __DEBUG__
//       assert( p.length() == minlen );
//#endif
//    }

 //   return minlen;
}
