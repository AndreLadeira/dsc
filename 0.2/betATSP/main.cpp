#include <iostream>
#include <vector>

using namespace std;

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

int main()
try
{
    Car * myCar = new Corolla;
    myCar = new AirConditioning( myCar );
    myCar = new AutomaticTransmission( myCar );
    myCar = new Tire( myCar, "1 old pirelli step");
    myCar = new Tire( myCar, "4 brand new michellin");

    //throw std::exception();

    std::cout<< (*myCar)() << endl;


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
};

struct AutomaticTransmission  : public CarDecorator
{
    AutomaticTransmission(shared_ptr<Car> c):CarDecorator(c){}
    ~AutomaticTransmission() { cout << "Automatic Transmission dtor\n"; }
    virtual string operator()(){ return (*_car)() + "automatic transmission "; }
};

struct Tire  : public CarDecorator
{
    Tire(shared_ptr<Car> c, string desc):CarDecorator(c), _desc(desc){}
    virtual string operator()(){ return (*_car)() + _desc + " tire "; }
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
    myCar = make_shared<Tire>(myCar,"4 brand new michellin");

    throw std::exception();

    std::cout<< (*myCar)() << endl;


    return 0;
}
catch(...)
{
    return 0;
}

*/
