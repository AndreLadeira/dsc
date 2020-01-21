#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H

#include "functors.h"
#include <random>
#include <functional>

using namespace core;

namespace algorithms
{
namespace simmulated_annealing {

template< typename delta_t,
          typename Compare<delta_t>::compare_fcn_t compare >
class DeltaAccept : public core::DeltaAccept<delta_t, compare >
{
public:

    DeltaAccept( const core::Value<double>& t):_tk(t){}
    virtual ~DeltaAccept() = default;

    virtual int operator()(const std::vector<delta_t>& delta_vec) const {
        static std::default_random_engine e( static_cast<unsigned int>( clock() ) );
        static auto rand_max = e.max();

        int i = 0;
        for(const auto& delta : delta_vec)
        {
            if ( compare(delta,0) )
            {
                return i;
            }
            else{
                auto p = std::exp( -static_cast<double>(delta) / _tk.getValue() );
                auto q = double(e()) / rand_max;
                if ( q < p )
                {
                    return i;
                }
            }
            i++;
        }
        return -1;
    }
private:
    const core::Value<double>& _tk;
};

template< typename delta_t = int>
using DeltaAcceptIncrease = DeltaAccept<delta_t,Compare<delta_t>::greater>;

template< typename delta_t = int>
using DeltaAcceptDecrease = DeltaAccept<delta_t,Compare<delta_t>::less>;

struct CooldownFunction
{
    CooldownFunction(double t0, double tf, size_t iters, std::function<double (double)> f ):
        _t0(t0),_tf(tf),_iters(iters),_f(f){}
    double operator()(size_t iter) const
    {
        auto u = (_t0-_tf) * _f( double(iter)/_iters);
        auto v = _tf + u;
        return v;
    }
private:
    const double _t0;
    const double _tf;
    const size_t _iters;
    const std::function<double (double)> _f;
};


double CooldownSin(double x, double power)
{
    return 1.0 - std::pow( std::sin( double(M_PI)/2.0 * x ), power);
}
double CooldownCos(double x, double power)
{
    return std::pow( std::cos( double(M_PI)/2.0 * x ), power);
}
double CooldownPoly(double x, double power)
{
    return std::pow( 1.0 - x, power);
}
double CooldownTanh(double x, double n)
{
    return 1.0 - std::tanh( n * x );
}

template< typename solution_t>
class TemperatureFunction:
        public Create< solution_t >,
        public Decorator< Create< solution_t > >,
        public Value<double>{
public:

    using DecoratorBase = Decorator< Create< solution_t > >;

    TemperatureFunction( typename DecoratorBase::ptr_t ptr, CooldownFunction f):
        DecoratorBase(ptr),_f(f){}

    virtual solution_t operator()(void){
        static size_t iter = 0;
        setValue( _f(iter++) );
        return DecoratorBase::_ptr->operator()();
    }
private:
   CooldownFunction _f;
};

}
}

#endif // SIMULATED_ANNEALING_H
