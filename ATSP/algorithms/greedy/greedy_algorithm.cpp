#include "greedy_algorithm.h"

using namespace atsp;

GreedyAlgorithm::GreedyAlgorithm(uint msksz):_msksz(msksz)
{

}

void GreedyAlgorithm::setMask(uint mask)
{
    _mask = mask;
}
