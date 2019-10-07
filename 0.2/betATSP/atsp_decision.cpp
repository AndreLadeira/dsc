#include "atsp_decision.h"
#include <string>
#include <ostream>
#include <random>

//#include <fstream>
//#include <regex>

using namespace algorithm;
using namespace atsp_decision;

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

solution_t BasicCreateFunctor::operator()()
{
    // create a random path

    std::vector<size_t> path(_size+1);
    std::iota(path.begin(),path.end()-1,0);

    // begin+1 / end-1 to make paths always starting and ending at city 0,
    // with no loss of generality
    std::default_random_engine e( static_cast<unsigned int>(time(nullptr)) );
    std::shuffle(path.begin()+1,path.end()-1,e);

    // store it in the decision-node structure
    solution_t s(_size);
    for(size_t i = 0; i < _size; ++i)
    {
        auto city = path.at(i);
        auto next_city = path.at(i+1);
        s.at(city).next = next_city;
        s.at(next_city).prev = city;
    }

    return s;
}

atsp_decision::NeighborhoodFunctor::trvec_t
atsp_decision::NeighborhoodFunctor::operator()(const solution_t &s)
{
    const auto sz = s.size();
    trvec_t trvec;
    trvec.reserve( (sz-2)*(sz-2) );

    const auto range = sz - 1;

    for(int node = 1; node < signed(sz); ++node)// sz = 7, node [1..6]
    {
        for( int i = 0; i < signed(range); ++i )
        {
            int tr = 1 -node + i;// 1 -[1..6] + [0 1 2 3 4 5] = 0..5/-1..4/....-5..0
            if ( tr != -1 && tr != 0 )
                trvec.push_back( transformation_t(node,tr));
        }
    }

#ifdef __DEBUG__
        assert( trvec.size() == (sz-2)*(sz-2));
#endif

    return trvec;
}

std::ostream& atsp_decision::operator<<(std::ostream &os, const node_t &n)
{
  return os << "<" << n.prev << ","<< n.next << ">";
}



void atsp_decision::ObjectiveFunctor::operator()(
        const solution_t & s,
        const trvec_t & trvec,
        resvec_t & resvec) const
{
    size_t pos = 0;

    for( const auto& trans : trvec)
    {
        auto my_pos = trans.first;
        auto offset = trans.second;

        size_t res = 0;

        resvec.at(pos++) = res;
    }
}
