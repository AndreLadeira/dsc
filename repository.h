#ifndef REPOSITORY_H
#define REPOSITORY_H
/*

    //exec.addAlgorithm( make_shared< atsp_decision::GreedyBestChoice >(create,neighbor,delta,accept,transform));
    //auto final_solution = exec.runAlgorithms(start_solution);


struct Car
{
    virtual ~Car() = default;
    virtual string operator()() = 0;
};

struct Corolla : public Car
{
    ~Corolla() { cout << "Corolla dtor\n"; }
    virtual string operator()() { return "Toyota Corolla ";}


};
struct Civic : public Car
{
    ~Civic() { cout << "Civic dtor\n"; }
    virtual string operator()() { return "Honda Civic ";}
};

struct CarDecorator : public Car
{
    CarDecorator(Car * c):_car(c){}

protected:
    Car * _car;
};

struct AirConditioning: public CarDecorator
{
    AirConditioning(Car * c):CarDecorator(c){}
    ~AirConditioning() { cout << "Air Conditioning dtor\n"; }
    virtual string operator()(){ return (*_car)() + "air conditioning "; }
};

struct AutomaticTransmission  : public CarDecorator
{
    AutomaticTransmission(Car * c):CarDecorator(c){}
    ~AutomaticTransmission() { cout << "Automatic Transmission dtor\n"; }
    virtual string operator()(){ return (*_car)() + "automatic transmission "; }
};

struct Tire  : public CarDecorator
{
    Tire(Car * c, string desc):CarDecorator(c), _desc(desc){}
    virtual string operator()(){ return (*_car)() + _desc + " tire "; }
private:
    string _desc;
};

struct myInt
{
    explicit myInt(int v):_v(v){}
    //myInt(int&& v){_v = v;}
    ~myInt(){ cout<<"Detor " << _v << endl;}
    int _v;
};

const shared_ptr<myInt> doubleIt( const shared_ptr<myInt> val)
{
    (*val)._v *= 2;
     //val = make_shared<myInt>(20);
     return val;
}

int main()
try
{
//    Car * myCar = new Corolla;
//    myCar = new AirConditioning( myCar );
//    myCar = new AutomaticTransmission( myCar );
//    myCar = new Tire( myCar, "1 old pirelli step");
//    myCar = new Tire( myCar, "4 brand new michellin");



//    //throw std::exception();

//    std::cout<< (*myCar)() << endl;

//    delete myCar;
    auto v = make_shared<myInt>(10);
    std::cout<< doubleIt( v )->_v << endl;
    std::cout<< (*v)._v << endl;

    return 0;
}
catch(...)
{

    return 0;
}


/*

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

struct Car
{
    virtual ~Car() = default;
    virtual string operator()() = 0;
    virtual string run() { return "running";}
};

struct Corolla : public Car
{
    ~Corolla() { cout << "Corolla dtor\n"; }
    virtual string operator()() { return "Toyota Corolla ";}

};
struct Civic : public Car
{
    ~Civic() { cout << "Civic dtor\n"; }
    virtual string operator()() { return "Honda Civic ";}
};

struct CarDecorator : public Car
{
    CarDecorator() = delete;
    CarDecorator(shared_ptr<Car> c):_car(c){}

protected:
    shared_ptr<Car> _car;
};

struct AirConditioning: public CarDecorator
{
    AirConditioning(shared_ptr<Car> c):CarDecorator(c){}
    ~AirConditioning() { cout << "Air Conditioning dtor\n"; }
    virtual string operator()(){ return (*_car)() + "air conditioning "; }
    virtual string run() { return _car->run() + " cool ";}
};

struct AutomaticTransmission  : public CarDecorator
{
    AutomaticTransmission(shared_ptr<Car> c):CarDecorator(c){}
    ~AutomaticTransmission() { cout << "Automatic Transmission dtor\n"; }
    virtual string operator()(){ return (*_car)() + "automatic transmission "; }

    virtual string run() { return _car->run() + " and smooth ";}
};

struct Tire  : public CarDecorator
{
    Tire(shared_ptr<Car> c, string desc):CarDecorator(c), _desc(desc){}
    virtual string operator()(){ return (*_car)() + _desc + " tire "; }
    virtual string run(){ return _car->run();}
    string sing() { return " tire singing"; }
private:
    string _desc;
};

int main()
try
{
    shared_ptr<Car> myCar = make_shared<Corolla>();
    myCar = make_shared<AirConditioning>(myCar);
    myCar = make_shared<AutomaticTransmission>(myCar);
    myCar = make_shared<Tire>(myCar,"1 old pirelli step");
    shared_ptr<Tire> myCar2 = make_shared<Tire>(myCar,"4 brand new michellin");

    //throw std::exception();

    std::cout<< (*myCar)() << endl;
    std::cout<< myCar2->run() << myCar2->sing() << endl;


    return 0;
}
catch(...)
{
    return 0;
}

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

int main(void)
{
   using create_functor_t = CreateFunctor<solution_t,problem_data_t>;
   using call_counter_decorator_t = CallCounter<solution_t,problem_data_t>;

   auto create_functor = make_shared<create_functor_t>(create_solution);
   auto create_with_callcount = make_shared<call_counter_decorator_t>(create_functor);
   auto create_with_callcount2 = make_shared<call_counter_decorator_t>(create_with_callcount);

   run(create_with_callcount2.get());



   //(*create_with_callcount2)( problem_data_t(), 10);
   std::cout<< "Function was called " << create_with_callcount->getCounter() << " times\n";
   std::cout<< "Function was called " << create_with_callcount2->getCounter() << " times\n";

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


    car< decltype (*myFcn<int,double>), int,double >  myCar(myFcn);
    //
    myCar.run()


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


   //auto d1p = make_shared<d1>(bp);
//   bp = make_shared< d2<fcnt,int,int> >(d1p,foo,2,3);
//   bp = make_shared< d3 >(bp,foobar,1,2,"param");

     b * bb = new d;
     cout << bb->run(1,2) << endl;

//   bp->run();
//   bp->run();
//   someFunc(bp);
//   std::cout<< "count: " << d1p->counter << endl;

    //base<fcn_type, vector<int>, int> myBase(neighbor, {1,2,3},1);
    //std::vector<int> keys = myBase.fcn({1,2,3},1);
    /*
    auto neighFunctor = make_shared< NF<kt,st> >();
    auto neighFunctor = make_shared< NFParamDecor<kt,st,fcn,vector<int>,int> >(neighFunctor,{1,2,3,4},4);
    neighFunctor = make_shared< NFCallCountDecor<kt,st>(neighFunctor);
    neighFunctor = make_shared< NFPrint<kt,st>(neighFunctor);
    keys myKeys = neighFunctor();

   using create_functor_t = CreateFunctor<solution_t,problem_data_t>;
   using call_counter_decorator_t = CallCounter<solution_t,problem_data_t>;
   using print_decorator_t = PrintSolution<solution_t,problem_data_t>;

   auto create_functor = make_shared<create_functor_t>(create_solution);
   create_functor = make_shared<call_counter_decorator_t>(create_functor);
   create_functor = make_shared<print_decorator_t>(create_functor);
   auto create_with_callcount = make_shared<call_counter_decorator_t>(create_functor);


   //run(create_with_callcount2.get());
    //std::cout<< times(2,4,78,1,1,1,1,1) << endl;
    //std::cout<< times(2,4) << endl;
    //std::cout<< times(2) << endl;


//   (*create_with_callcount)( problem_data_t(), 10);
//   std::cout<< "Function was called " << create_with_callcount->getCounter() << " times\n";
   //std::cout<< "Function was called " << create_with_callcount->getCounter() << " times\n";

/*
 *
 * vector<int> deltas( neighbors.size() );

    (*deltacost)(s,neighbors,deltas);

    atsp_decision::Accept::result_t accepted = (*accept)(deltas);

    std::cout<< "Improvement possible: " << std::boolalpha << accepted.first << endl;

    auto bestimprove = deltas.at(accepted.second);

    if ( accepted.first )
    {
        std::cout<< "Best solution cost improvement: " << bestimprove
                 << " at index " << accepted.second << endl;

        auto expectedCost = signed((*cost)(s)) + bestimprove;

        std::cout<< "Expected modified solution cost is: " << expectedCost << endl;

        auto transform = make_shared<atsp_decision::Transform>();
        (*transform)(s,neighbors.at(accepted.second));

        auto obtainedCost = signed((*cost)(s));

        std::cout<< "Obtained solution cost is: " << obtainedCost << endl;

#ifdef __DEBUG__
        assert( expectedCost == obtainedCost );
#endif

    }


*/



#endif // REPOSITORY_H
