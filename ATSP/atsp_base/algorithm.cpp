#include "algorithm.h"

using namespace atsp;


Algorithm::~Algorithm()
{

}

GreedyAlgorithm::GreedyAlgorithm(uint msksz):_msksz(msksz)
{

}

void GreedyAlgorithm::setMask(uint mask)
{
    _mask = mask;
}
