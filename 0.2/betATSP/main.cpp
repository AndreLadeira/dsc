#include <iostream>
#include <vector>

#include "functors.h"
#include "decorators.h"

using namespace std;


using solution_t = vector< size_t >;
using problem_data_t = vector< vector< size_t> >;

solution_t create_solution(const problem_data_t & pdata, size_t sz,
                           const solution_t * const source = nullptr)
{
    solution_t s(sz,0);
    for(size_t i = 0; i < sz; ++i  )
      s.at(i) = i;
    return s;
}

template< typename solution_t , typename problem_data_t >
void run(CreateFunctor<solution_t, problem_data_t> * const createSolution)
{
    for(int i = 0; i < 100; i++)
        (*createSolution)(problem_data_t(),20,nullptr);
}

//template < typename A>
//A times(const A& a)
//{
//    return a;
//}
template < typename A, typename T, typename ...Args>
A times(const A& a, const T& t, const Args&... rest)
{
    return a+t;
}

template< typename fcn_t, typename ...Args>
struct car
{
    car(fcn_t f):_fcn(f){}
//    template<> int run()
//    {
//        return 100;
//    }
    void run()
    {
        return _fcn(2,1);
    }
private:
    fcn_t _fcn;
};

template<typename p1, typename p2, typename ...Args>
void myFcn(const p1& _p1, const p2& _p2, const Args&...)
{
    std::cout<< _p1 + _p2 <<endl;
}


int main(void)
{
//   using create_functor_t = CreateFunctor<solution_t,problem_data_t>;
//   using call_counter_decorator_t = CallCounter<solution_t,problem_data_t>;
//   using print_decorator_t = PrintSolution<solution_t,problem_data_t>;

//   auto create_functor = make_shared<create_functor_t>(create_solution);
//   create_functor = make_shared<call_counter_decorator_t>(create_functor);
//   create_functor = make_shared<print_decorator_t>(create_functor);
//   auto create_with_callcount = make_shared<call_counter_decorator_t>(create_functor);


   //run(create_with_callcount2.get());
    std::cout<< times(2,4,78,1,1,1,1,1) << endl;
    std::cout<< times(2,4) << endl;
    //std::cout<< times(2) << endl;
    car< decltype (*myFcn<int,double>), int,double >  myCar(myFcn);
    //
    myCar.run();

//   (*create_with_callcount)( problem_data_t(), 10);
//   std::cout<< "Function was called " << create_with_callcount->getCounter() << " times\n";
   //std::cout<< "Function was called " << create_with_callcount->getCounter() << " times\n";

}
