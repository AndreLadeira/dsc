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

struct base
{
    virtual ~base() = default;
    virtual void run(...) = 0;
};

struct decor : public base
{
    virtual ~decor() = default;
    explicit decor( shared_ptr<base> p ):bp(p){}

    virtual void run(...) = 0;

    shared_ptr<base> bp;
};

struct d1 : public decor
{
  explicit d1( shared_ptr<base> p ):decor(p){}
  void run(...)
  {
      bp->run();
      counter++;
      std::cout<<"counter run\n";
  }
  int counter;
};

template<typename fcn, typename ...Args>
struct d2 : public decor
{
  d2( shared_ptr<base> p,
      fcn f, const Args&... args ):
        decor(p), myf(f){ extract(args...); } // sets the state

  void run() // uses the state indirectly
  {
      bp->run();
      std::cout<< "Core run: " << myf(params) << endl;
  }

private:

  template<typename T> void extract(const T& t)
  {
      params[sizeof...(Args)-1] = t;
  }
  template<typename T, typename ...args> void extract(const T& t, const args&... rest)
  {
      int pos = sizeof...(Args) - sizeof...(rest) - 1;
      params[pos] = t;
      extract(rest...);
  }
  int params[sizeof...(Args)];
  fcn myf;
};

int foo(int params[])
{
    return params[0] + params[1];
}
int bar(int params[])
{
    return params[0] * params[1];
}

using fcnt = int(*)(int[]);

#include <sstream>

string foobar(int i, float f, string s)
{
    stringstream ss;
    ss << "int " << i << " float " << f << " string " << s;
    return ss.str();
}

struct d3 : public decor
{
    using fcn_t = string (*)(int,float,string);

    d3(shared_ptr<base> p, fcn_t fcn, int i, float f, string s):
        decor(p),_fcn(fcn),_p1(i),_p2(f),_p3(s){}

    void run()
    {
        bp->run();
        std::cout<< "Decor 3 : " << _fcn(_p1,_p2,_p3) << endl;
    }

private:

    fcn_t _fcn;
    int _p1;
    float _p2;
    string _p3;

};

void someFunc( const shared_ptr<base> bp )
{
    bp->run();
}


//int main(void)
//{
//   //auto d1p = make_shared<d1>(bp);
////   bp = make_shared< d2<fcnt,int,int> >(d1p,foo,2,3);
////   bp = make_shared< d3 >(bp,foobar,1,2,"param");

//     b * bb = new d;
//     cout << bb->run(1,2) << endl;

////   bp->run();
////   bp->run();
////   someFunc(bp);
////   std::cout<< "count: " << d1p->counter << endl;

////   using create_functor_t = CreateFunctor<solution_t,problem_data_t>;
////   using call_counter_decorator_t = CallCounter<solution_t,problem_data_t>;
////   using print_decorator_t = PrintSolution<solution_t,problem_data_t>;

////   auto create_functor = make_shared<create_functor_t>(create_solution);
////   create_functor = make_shared<call_counter_decorator_t>(create_functor);
////   create_functor = make_shared<print_decorator_t>(create_functor);
////   auto create_with_callcount = make_shared<call_counter_decorator_t>(create_functor);


//   //run(create_with_callcount2.get());
//    //std::cout<< times(2,4,78,1,1,1,1,1) << endl;
//    //std::cout<< times(2,4) << endl;
//    //std::cout<< times(2) << endl;


////   (*create_with_callcount)( problem_data_t(), 10);
////   std::cout<< "Function was called " << create_with_callcount->getCounter() << " times\n";
//   //std::cout<< "Function was called " << create_with_callcount->getCounter() << " times\n";

//    //base<fcn_type, vector<int>, int> myBase(neighbor, {1,2,3},1);
//    //std::vector<int> keys = myBase.fcn({1,2,3},1);
//    /*
//    auto neighFunctor = make_shared< NF<kt,st> >();
//    auto neighFunctor = make_shared< NFParamDecor<kt,st,fcn,vector<int>,int> >(neighFunctor,{1,2,3,4},4);
//    neighFunctor = make_shared< NFCallCountDecor<kt,st>(neighFunctor);
//    neighFunctor = make_shared< NFPrint<kt,st>(neighFunctor);
//    keys myKeys = neighFunctor();
//    */


//}
