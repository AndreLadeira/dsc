#ifndef STDFUNCTORS_H
#define STDFUNCTORS_H

#include "functors.h"
#include <cmath>
#include <random>

namespace core{

template< typename solution_t,
          typename objective_t>
struct UpdateIfGreater : public Update<solution_t,objective_t>
{
    UpdateIfGreater():Update<solution_t,objective_t>(Compare<objective_t>::Greater){}
};
template< typename solution_t,
          typename objective_t>
struct UpdateIfsmaller : public Update<solution_t,objective_t>
{
    UpdateIfsmaller():Update<solution_t,objective_t>(Compare<objective_t>::less){}
};
template< typename solution_t,
          typename objective_t>
struct UpdateAlways : public Update<solution_t,objective_t>
{
    UpdateAlways():Update<solution_t,objective_t>(Compare<objective_t>::_true){}
};

}

#endif // STDFUNCTORS_H
