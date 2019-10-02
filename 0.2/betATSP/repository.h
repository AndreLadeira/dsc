#ifndef REPOSITORY_H
#define REPOSITORY_H
/*

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

*/








  */
#endif // REPOSITORY_H
