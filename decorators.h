#ifndef STD_DECORATORS_H
#define STD_DECORATORS_H

#include "core.h"
#include "functors.h"
#include <iosfwd>

namespace core{

template< typename solution_t >
class CreateCallsAccumulator:
        public Create< solution_t >,
        public Decorator< Create< solution_t > >,
        public Counter<>{
public:

    using DecoratorBase = Decorator< Create< solution_t > >;

    CreateCallsAccumulator( typename DecoratorBase::ptr_t ptr ):DecoratorBase(ptr){}

    virtual solution_t operator()(void){
        Counter::increment(1);
        return DecoratorBase::_ptr->operator()();
    }

};

template< typename solution_t >
class PrintSolution:
        public Create< solution_t >,
        public Decorator< Create< solution_t > >
{
public:

    using DecoratorBase = Decorator< Create< solution_t > >;

    PrintSolution( typename DecoratorBase::ptr_t ptr, std::ostream & os):
        DecoratorBase(ptr),_os(os){}

    virtual solution_t operator()(void)
    {
        // get the newly created solution
        solution_t s = DecoratorBase::_ptr->operator()();

        //print it
        for (auto const& i: s) _os << i << "\t";
        _os << "\n";

        // pass it along
        return s;
    }

private:

    std::ostream & _os;
};

template< typename solution_t , typename transformation_t >
class NeighborCallAccumulator:
        public Neighborhood< solution_t, transformation_t >,
        public Decorator< Neighborhood< solution_t, transformation_t > >,
        public Accumulator<>
{
public:

    using DecoratorBase = Decorator< Neighborhood< solution_t, transformation_t > >;

    NeighborCallAccumulator(typename DecoratorBase::ptr_t ptr):DecoratorBase(ptr){}

    virtual ~NeighborCallAccumulator() = default;
    virtual std::vector<transformation_t> operator()( const solution_t& s ){
        Accumulator::increment(1);
        return DecoratorBase::_ptr->operator()(s);
    }
};

template< typename solution_t , typename transformation_t >
class NeighborAccumulator:
        public Neighborhood< solution_t, transformation_t >,
        public Decorator< Neighborhood< solution_t, transformation_t > >,
        public Accumulator<>
{
public:

    using DecoratorBase = Decorator< Neighborhood< solution_t, transformation_t > >;

    NeighborAccumulator(typename DecoratorBase::ptr_t ptr):DecoratorBase(ptr){}

    virtual ~NeighborAccumulator() = default;
    virtual std::vector<transformation_t> operator()( const solution_t& s ){
        auto n = DecoratorBase::_ptr->operator()(s);
        Accumulator::increment(n.size());
        return n;
    }
};

template< typename solution_t , typename transformation_t >
class NeighborCounter:
        public Neighborhood< solution_t, transformation_t >,
        public Decorator< Neighborhood< solution_t, transformation_t > >,
        public Counter<>
{
public:

    using DecoratorBase = Decorator< Neighborhood< solution_t, transformation_t > >;

    NeighborCounter(typename DecoratorBase::ptr_t ptr):DecoratorBase(ptr){}

    virtual ~NeighborCounter() = default;
    virtual std::vector<transformation_t> operator()( const solution_t& s ){
        auto n = DecoratorBase::_ptr->operator()(s);
        Counter::increment(n.size());
        return n;
    }
};

template< typename solution_t, typename data_t, typename result_t = size_t >
class ObjectiveCallAccumulator:
        public Objective< solution_t, data_t, result_t >,
        public Decorator< Objective< solution_t, data_t, result_t > >,
        public Accumulator<>{

public:

    using DecoratorBase = Decorator< Objective< solution_t, data_t, result_t > >;

    ObjectiveCallAccumulator() = delete;
    ObjectiveCallAccumulator( typename DecoratorBase::ptr_t ptr ):DecoratorBase(ptr){}

    virtual size_t operator()(const solution_t& s){
        increment(1);
        return DecoratorBase::_ptr->operator()(s);
    }

};


template< typename solution_t, typename transformation_t, typename data_t, typename delta_t = int>
class DeltaObjectiveCallAccumulator:
        public DeltaObjective< solution_t, transformation_t, data_t, delta_t>,
        public Decorator<DeltaObjective< solution_t, transformation_t, data_t, delta_t>>,
        public Accumulator<>{

public:

    using DecoratorBase = Decorator<DeltaObjective< solution_t, transformation_t, data_t, delta_t>>;

    DeltaObjectiveCallAccumulator() = delete;
    DeltaObjectiveCallAccumulator( typename DecoratorBase::ptr_t ptr ):DecoratorBase(ptr){}

    virtual std::vector<delta_t> operator()(const solution_t& s,const std::vector<transformation_t>& trvec){
        increment(1);
        return DecoratorBase::_ptr->operator()(s,trvec);
    }
};

}

#endif // STD_DECORATORS_H
