#include <iostream>
#include <vector>
#include <algorithm>

#include "functors.h"
#include "decorators.h"
#include "atsp.h"
#include "atsp_decision.h"

using namespace std;
using namespace algorithm;
using namespace problems::atsp;


template<typename T>
struct value
{
    value():_v(T(0)){}
    T get(void) const {return _v;}

protected:

    T _v;

};
template<typename T>
struct counter : public value<T>
{
    counter() = default;
protected:
    void increment(T amount){ value<T>::_v += amount;}
    void reset(){ value<T>::_v = T(0);}
};

struct base
{   base(){}
    virtual ~base() = default;
    virtual int exec(){ return std::rand() % 100;}
};

struct deco : public base
{
    deco(base* bp):ptr(bp){}
    virtual int exec() override = 0;

protected:

    base * ptr;
};

struct down10 : public deco, public value<int>
{
    down10(base* bp):deco(bp){}
    virtual int exec() override
    {
       value::_v = ptr->exec() - 10;
       return _v;
    }
};


struct sensor
{
    virtual ~sensor() = default;
    virtual operator bool() const = 0;
};


template <typename T>
struct concrete_sensor : public sensor
{
    using compare = bool (*)(T,T);
    static T abs(T x){ if (x<0) return -x; else return x; }
    static bool less(const T a, const T b){return a<b;}
    static bool greater(const T a, const T b){return a>b;}
    static bool equal_to(const T a, const T b){return a==b;}

    concrete_sensor(const value<T> & value, T limit , compare c = greater):
        _value(value),_limit(limit), _compare(c){}

    virtual operator bool() const
    {
        return _compare(_value.get(),_limit);
    }

private:

    const value<T> & _value;
    T _limit;
    compare _compare;
};


struct callcounter : public deco, public counter<int>
{
    callcounter(base* bp):deco(bp){}
    virtual int exec() override
    {
        counter::increment(1);
        return ptr->exec();
    }
};

struct execution_controller
{

    bool restart(){
        for( auto * sensor : restartSensors )
            if (*sensor) return true;
        return false;
    }
    bool stop(){
        for( auto * sensor : stopSensors )
            if (*sensor) return true;
        return false;
    }

    void addRestartTrigger( sensor * s){
        restartSensors.push_back(s);
    }
    void addStopTrigger( sensor * s){
        stopSensors.push_back(s);
    }

private:

    std::vector<sensor*> stopSensors;
    std::vector<sensor*> restartSensors;


};




int main(void)
{
    //const std::vector<size_t> p = {0,12,16,11,1,9,2,13,8,3,10,5,6,14,15,7,4,0};
    execution_controller exec;

    auto * basep = new base;
    basep = new down10(basep);
    exec.addRestartTrigger( new concrete_sensor<int>(dynamic_cast<down10&>(*basep),0,
                                                     concrete_sensor<int>::equal_to));

    basep = new callcounter( basep );
    exec.addStopTrigger( new concrete_sensor<int>(dynamic_cast<callcounter&>(*basep),1000) );

    while( !exec.stop() )
    {
        std::cout<< basep->exec() << endl;

        if ( exec.restart() )
        std::cout<<"======== RESTARTING ========\n";
    }


    using createFunctor = core::CreateFunctor<atsp_decision::solution_t>;
    using createCallCnt = core::CreateFunctorCallCounter<atsp_decision::solution_t>;
    using printCreated = core::PrintSolution<atsp_decision::solution_t>;

    atsp_decision::problem_data_t tspdata;
    problems::atsp::loadTSPLIB(std::ifstream("../tsplib/br17.atsp"),tspdata);

    shared_ptr<createFunctor> create = make_shared<atsp_decision::BasicCreateFunctor>(tspdata.size());
    create = make_shared<printCreated>(create);
    create = make_shared<createCallCnt>(create);

    auto s = (*create)();

    using neighborFunctor =
    core::NeighborhoodFunctor< atsp_decision::solution_t, atsp_decision::transformation_t >;
    using neighborCallCnt =
    core::NeighborhoodFunctorCallCounter< atsp_decision::solution_t, atsp_decision::transformation_t >;

    shared_ptr<neighborFunctor>  neighbor = make_shared< atsp_decision::NeighborhoodFunctor >();
    neighbor = make_shared< neighborCallCnt >(neighbor);

    auto neighbors = (*neighbor)(s);
    std::cout<< "Number of neighbors: " << neighbors.size() << endl;

    using objFunctor =
    core::ObjectiveFunctor< atsp_decision::solution_t, atsp_decision::problem_data_t>;
    using objCallCounter = core::ObjectiveFunctorCallCounter< atsp_decision::solution_t, atsp_decision::problem_data_t>;

    shared_ptr<objFunctor> cost = make_shared<atsp_decision::ObjectiveFunctor>(tspdata);
    cost = make_shared<objCallCounter>(cost);

    std::cout<< "Solution cost: " << (*cost)(s) << endl;

    using deltaObjFunctor =
    core::DeltaObjectiveFunctor< atsp_decision::solution_t, atsp_decision::transformation_t, atsp_decision::problem_data_t>;

    shared_ptr<deltaObjFunctor> deltacost = make_shared<atsp_decision::DeltaObjectiveFunctor>(tspdata);
    atsp_decision::DeltaObjectiveFunctor::result_vector_type deltas( neighbors.size() );

    (*deltacost)(s,neighbors,deltas);

    shared_ptr<atsp_decision::AcceptFunctor> accept = make_shared<atsp_decision::AcceptFunctor>();

    atsp_decision::AcceptFunctor::result_t accepted = (*accept)(deltas);

    std::cout<< "Improvement possible: " << std::boolalpha << accepted.first << endl;

    auto bestimprove = deltas.at(accepted.second);

    if ( accepted.first )
    {
        std::cout<< "Best solution cost improvement: " << bestimprove
                 << " at index " << accepted.second << endl;

        auto expectedCost = signed((*cost)(s)) + bestimprove;

        std::cout<< "Expected modified solution cost is: " << expectedCost << endl;

        auto transform = make_shared<atsp_decision::TransformFunctor>();
        (*transform)(s,neighbors.at(accepted.second));

        auto obtainedCost = signed((*cost)(s));

        std::cout<< "Obtained solution cost is: " << obtainedCost << endl;

#ifdef __DEBUG__
        assert( expectedCost == obtainedCost );
#endif

    }
    std::cout<< "Times create called: " <<
                dynamic_cast<createCallCnt*>(create.get())->getCounter() << endl;
    std::cout<< "Times neighbor called: " <<
                dynamic_cast<neighborCallCnt*>(neighbor.get())->getCounter() << endl;
    std::cout<< "Times objective function was called: " <<
                dynamic_cast<objCallCounter*>(cost.get())->getCounter() << endl;

    std::sort(deltas.begin(),deltas.end(),less<int>());


    return 0;
}
