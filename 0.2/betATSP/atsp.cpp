#include "atsp.h"
#include <fstream>
#include <regex>

using namespace std;

//void loadData(std::ifstream file, ProblemData & data)
//{
//    string line;
//    getline(file,line); // problem name
//    getline(file,line); // type
//    getline(file,line); // comment
//    getline(file,line); // matrix size

//    smatch m;
//    regex e("^\\s*DIMENSION\\s*:\\s*(\\d+)");

//    if ( regex_search (line,m,e) )
//    {
//        const uint size = static_cast<uint>(stoul(m[1]));

//        getline(file,line); // weight type
//        getline(file,line); // weight format
//        getline(file,line); // weight section

//        data.reserve(size);

//        for( uint i = 0; i < size; ++i )
//        {
//            vector<int> row(size,0);

//            for( uint j = 0; j < size; ++j )
//                file >> row[j];

//            data.push_back(row);
//        }
//    }
//    else
//    {
//        throw std::runtime_error("Could not read data from tsplib input file.");
//    }
//}
