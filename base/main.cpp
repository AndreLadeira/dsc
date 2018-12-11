#include <iostream>
#include <ctime>
#include <iomanip>
#include "teste.h"

using namespace std;

int main()
{
    cout<<"Starting...\n";

    A a(17);
    B b(17);
    clock_t begin = clock();

    randomize(a);
    cout<< "Elapsed time: " << setprecision(3) <<
           (clock() - begin) / static_cast<double>(CLOCKS_PER_SEC) << endl;

    begin = clock();
    randomize(b);
    cout<< "Elapsed time: " << setprecision(3) <<
           (clock() - begin) / static_cast<double>(CLOCKS_PER_SEC) << endl;
}
