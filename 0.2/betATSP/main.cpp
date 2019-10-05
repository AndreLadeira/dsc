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
    typedef res type;
    using utype = res;
};

using fcnT = int(*)(int);

template< class T > bool compare(T a, T b)
{
    return (a<b);
}

template<typename ... Args> void g(Args ... args) {
cout << sizeof...(Args) << endl; // number of type parameters
cout << sizeof...(args) << endl; // number of function parameters
}

class wrapper
{
public:

    //wrapper( _1ParamOperator(_fcnT) op );
//    void setOperator(T f){_op = f;}
//    void operator()(){ std::cout<< _op(_v) << endl; }



private:
    //T _op;
    //int _v;
};



int main()
{
//    std::pair<int,string> p(1,"maria");
//    long x = 20;
//    bool res = compare(10,20);
//    pair p2(10,10);

    int i = 0; double d = 3.14; string s = "how now brown cow";
    g(i, s, 42, d); // three parameters in the pack
    g(s, 42, "hi"); // two parameters in the pack
    g(d, s); // one parameter in the pack
    g("hi"); // empty pack

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
