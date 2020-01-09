#ifndef STD_DECORATORS_H
#define STD_DECORATORS_H

#include "core.h"
#include "functors.h"
#include <iosfwd>

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
class IntesificationRecorder:
        public Create< solution_t >,
        public Decorator< Create< solution_t > >,
        public Recorder<>{

public:

    using DecoratorBase = Decorator< Create< solution_t > >;

    IntesificationRecorder() = delete;
    IntesificationRecorder( typename DecoratorBase::ptr_t ptr, core::Resettable<>& ncc ):
        DecoratorBase(ptr),_neighbors_resettable(ncc){}

    virtual solution_t operator()(void){

        static size_t callsCounter = 0;

        if ( callsCounter ){
            record(callsCounter,_neighbors_resettable.getValue());
            _neighbors_resettable.reset();
        }

        callsCounter++;
        return DecoratorBase::_ptr->operator()();
    }

private:

    core::Resettable<>& _neighbors_resettable;

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

template< typename solution_t, typename data_t, typename result_t = size_t >
class ObjectiveCallsCounter:
        public Objective< solution_t, data_t, result_t >,
        public Decorator< Objective< solution_t, data_t, result_t > >,
        public Counter<>{

public:

    using DecoratorBase = Decorator< Objective< solution_t, data_t, result_t > >;

    ObjectiveCallsCounter() = delete;
    ObjectiveCallsCounter( typename DecoratorBase::ptr_t ptr ):DecoratorBase(ptr){}

    virtual size_t operator()(const solution_t& s){
        increment(1);
        return DecoratorBase::_ptr->operator()(s);
    }

};

template< typename solution_t, typename data_t, typename result_t = size_t >
class ObjectiveProgress:
        public Objective< solution_t, data_t, result_t >,
        public Decorator< Objective< solution_t, data_t, result_t > >,
        public Progress<>{

public:

    using DecoratorBase = Decorator< Objective< solution_t, data_t, result_t > >;

    ObjectiveProgress() = delete;
    ObjectiveProgress( typename DecoratorBase::ptr_t ptr):
        DecoratorBase(ptr){}

    virtual size_t operator()(const solution_t& s){

        static bool first = true;
        auto c = DecoratorBase::_ptr->operator()(s);

        if (first) { setInitialValue(c); first = false; }
        else setProgress(c);

        return c;
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


//template< typename _delta_t = int >
//class ProgressLogger:
//        public DeltaAccept< _delta_t >,
//        public Decorator< DeltaAccept< _delta_t > >,
//        public NonCopyable
//{
//public:
//    using DecoratorBase = Decorator< DeltaAccept< _delta_t > >;
//    using Result = typename DecoratorBase::Result;
//    using delta_vector_t = typename DecoratorBase::delta_vector_t;

//    ProgressLogger(std::ostream& os):_os(os){}
//    virtual Result operator()(const delta_vector_t& dvec){
//        Result r = DecoratorBase::_ptr->operator()(dvec);
//        if ( r.accepted ){

//        }
//    }

//    void addValue( std::shared_ptr< core::Ostreamable > v ){
//        _values.push_back(v);
//    }

//private:

//    std::ostream& _os;
//    std::vector< std::shared_ptr< core::Ostreamable > > _values;
//};

}
#endif // STD_DECORATORS_H
