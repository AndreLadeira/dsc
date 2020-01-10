#ifndef STD_DECORATORS_H
#define STD_DECORATORS_H

#include "core.h"
#include "functors.h"
#include <iosfwd>
#include <iostream>

namespace core{

template< typename solution_t >
class CreateCallsCounter:
        public Create< solution_t >,
        public Decorator< Create< solution_t > >,
        public Counter<>{
public:

    using DecoratorBase = Decorator< Create< solution_t > >;

    CreateCallsCounter( typename DecoratorBase::ptr_t ptr ):DecoratorBase(ptr){}

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
class NeighborCallsCounter:
        public Neighborhood< solution_t, transformation_t >,
        public Decorator< Neighborhood< solution_t, transformation_t > >,
        public Counter<>
{
public:

    using DecoratorBase = Decorator< Neighborhood< solution_t, transformation_t > >;

    NeighborCallsCounter(typename DecoratorBase::ptr_t ptr):DecoratorBase(ptr){}

    virtual ~NeighborCallsCounter() = default;
    virtual std::vector<transformation_t> operator()( const solution_t& s ){
        Counter::increment(1);
        return DecoratorBase::_ptr->operator()(s);
    }
};

template< typename solution_t , typename transformation_t >
class NeighborCallsResettable:
        public Neighborhood< solution_t, transformation_t >,
        public Decorator< Neighborhood< solution_t, transformation_t > >,
        public Resettable<>
{
public:

    using DecoratorBase = Decorator< Neighborhood< solution_t, transformation_t > >;

    NeighborCallsResettable(typename DecoratorBase::ptr_t ptr):DecoratorBase(ptr){}

    virtual ~NeighborCallsResettable() = default;
    virtual std::vector<transformation_t> operator()( const solution_t& s ){
        auto n = DecoratorBase::_ptr->operator()(s);
        Counter::increment(1);
        return n;
    }

};

template< typename solution_t , typename transformation_t >
class NeighborsExploredCounter:
        public Neighborhood< solution_t, transformation_t >,
        public Decorator< Neighborhood< solution_t, transformation_t > >,
        public Counter<>
{
public:

    using DecoratorBase = Decorator< Neighborhood< solution_t, transformation_t > >;

    NeighborsExploredCounter(typename DecoratorBase::ptr_t ptr):DecoratorBase(ptr){}

    virtual ~NeighborsExploredCounter() = default;
    virtual std::vector<transformation_t> operator()( const solution_t& s ){
        auto n = DecoratorBase::_ptr->operator()(s);
        Counter::increment(n.size());
        return n;
    }

};

template< typename solution_t , typename transformation_t >
class NeighborsExploredResettable:
        public Neighborhood< solution_t, transformation_t >,
        public Decorator< Neighborhood< solution_t, transformation_t > >,
        public Resettable<>
{
public:

    using DecoratorBase = Decorator< Neighborhood< solution_t, transformation_t > >;

    NeighborsExploredResettable(typename DecoratorBase::ptr_t ptr):DecoratorBase(ptr){}

    virtual ~NeighborsExploredResettable() = default;
    virtual std::vector<transformation_t> operator()( const solution_t& s ){
        auto n = DecoratorBase::_ptr->operator()(s);
        Counter::increment(n.size());
        return n;
    }

};

template< typename solution_t, typename data_t, typename objective_t = int >
class ObjectiveCallsCounter:
        public Objective< solution_t, data_t, objective_t >,
        public Decorator< Objective< solution_t, data_t, objective_t > >,
        public Counter<>{

public:

    using DecoratorBase = Decorator< Objective< solution_t, data_t, objective_t > >;

    ObjectiveCallsCounter() = delete;
    ObjectiveCallsCounter( typename DecoratorBase::ptr_t ptr ):DecoratorBase(ptr){}

    virtual objective_t operator()(const solution_t& s){
        increment(1);
        return DecoratorBase::_ptr->operator()(s);
    }

};

template< typename solution_t, typename transformation_t, typename data_t, typename delta_t = int>
class DeltaObjectiveCallsCounter:
        public DeltaObjective< solution_t, transformation_t, data_t, delta_t>,
        public Decorator<DeltaObjective< solution_t, transformation_t, data_t, delta_t>>,
        public Counter<>{

public:

    using DecoratorBase = Decorator<DeltaObjective< solution_t, transformation_t, data_t, delta_t>>;

    DeltaObjectiveCallsCounter() = delete;
    DeltaObjectiveCallsCounter( typename DecoratorBase::ptr_t ptr ):DecoratorBase(ptr){}

    virtual std::vector<delta_t> operator()(const solution_t& s,const std::vector<transformation_t>& trvec){
        increment(1);
        return DecoratorBase::_ptr->operator()(s,trvec);
    }
};

template< typename solution_t,
          typename objective_t,
          typename Compare<objective_t>::compare_fcn_t compare>
class ObjectiveProgress:
        public Update< solution_t, objective_t, compare >,
        public Decorator< Update< solution_t, objective_t, compare > >,
        public Progress<>{

public:

    using DecoratorBase = Decorator< Update< solution_t, objective_t, compare > >;

    ObjectiveProgress() = delete;
    ObjectiveProgress( typename DecoratorBase::ptr_t ptr):
        DecoratorBase(ptr){}

    virtual bool operator()(solution_t& bestSoFar, objective_t& bsfCost,
                            const solution_t& candidate, const objective_t candidateCost ){

        static bool first = true;

        if (first)
            { setInitialValue(bsfCost); first = false; }
        else if ( candidateCost < bsfCost )  setProgress(candidateCost);

        return DecoratorBase::_ptr->operator()(bestSoFar,bsfCost,candidate,candidateCost);
    }
};



template< typename solution_t,
          typename objective_t,
          typename Compare<objective_t>::compare_fcn_t compare>
class NeighborsCallsRecorder:
        public Update< solution_t, objective_t, compare >,
        public Decorator< Update< solution_t, objective_t, compare > >,
        public Recorder<>{

public:

    using DecoratorBase = Decorator< Update< solution_t, objective_t, compare > >;

    NeighborsCallsRecorder() = delete;
    NeighborsCallsRecorder( typename DecoratorBase::ptr_t ptr, core::Resettable<>& ncc ):
        DecoratorBase(ptr),_neighbors_resettable(ncc){}

    virtual bool operator()(solution_t& bestSoFar, objective_t& bsfCost,
                            const solution_t& candidate, const objective_t candidateCost ){
        static size_t callsCounter = 1;
        record(callsCounter++,_neighbors_resettable.getValue());
        _neighbors_resettable.reset();
        return DecoratorBase::_ptr->operator()(bestSoFar,bsfCost,candidate,candidateCost);
    }

private:

    core::Resettable<>& _neighbors_resettable;

};

template< typename solution_t,
          typename objective_t,
          typename Compare<objective_t>::compare_fcn_t compare>
class StagnationCounter:
        public Update< solution_t, objective_t, compare >,
        public Decorator< Update< solution_t, objective_t, compare > >,
        public Resettable<>{

public:

    using DecoratorBase = Decorator< Update< solution_t, objective_t, compare > >;

    StagnationCounter() = delete;
    StagnationCounter( typename DecoratorBase::ptr_t ptr):
        DecoratorBase(ptr){}

    virtual bool operator()(solution_t& bestSoFar, objective_t& bsfCost,
                            const solution_t& candidate, const objective_t candidateCost ){
        bool updated = DecoratorBase::_ptr->operator()(bestSoFar,bsfCost,candidate,candidateCost);
        if ( updated )
            reset();
        else
            increment(1);
        return updated;
    }
};

}
#endif // STD_DECORATORS_H
