#include <iostream>
#include "functor.h"
#include <utility>

using namespace std;

int add2(int x){return x+2;}
int square(int x){ return x*x;}

template< class res >
class param
{
public:
    using type = res;
};

using fcnT = int(*)(int);

template< class a, class b >
class x
{
public:
    param<a>::type getX(void){};

}

//class wrapper
//{
//public:

//    //wrapper( _1ParamOperator(_fcnT) op );
////    void setOperator(T f){_op = f;}
////    void operator()(){ std::cout<< _op(_v) << endl; }

//private:
//    //T _op;
//    int _v;
//};



int main()
{
    std::pair<int,string> p(1,"maria");

//    wrapper<fcnT> wrap(4);

//    char op = 0;
//    do
//    {
//        cout<< "1 - add2\n";
//        cout<< "2 - square\n";
//        cin >> op;

//        if ( op == '1')
//            wrap.setOperator(add2);
//        else
//            wrap.setOperator(square);

//        wrap();
//    }
//    while( op == '1' || op == '2');

}
