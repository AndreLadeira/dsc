#include <iostream>
#include <vector>
#include <forward_list>
#include "path.h"

using namespace std;

int main()
{
    base::fast_srand();
    atsp::path p;
    atsp::get_random(p, 10);

    for( const auto & x:p   )
    {
       cout << x << " ";
    }
    cout << endl;

    return 0;
}
