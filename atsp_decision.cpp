#include "atsp_decision.h"
#include <string>
#include <ostream>
#include <random>
#include <algorithm>
#include <chrono>

#ifdef __DEBUG__
#include <cassert>
#endif

using namespace problems::atsp;
using namespace atsp_decision;

void atsp_decision::to_path(const solution_t& s, path_t &path)
{
    path.clear();
    path.reserve( s.size() + 1);
    path.push_back(0);

    // traverse the solution like a linked list
    auto iter = s.begin();
    do
    {
        path.push_back(iter->next);
        iter = s.begin() + signed(iter->next);
    }
    while( iter != s.begin() );
}

void atsp_decision::from_path(const path_t & path, solution_t &s )
{
    for(size_t i = 0; i < path.size()-1; ++i)
    {
        auto city = path.at(i);
        auto next_city = path.at(i+1);
        s.at(city).next = next_city;
        s.at(next_city).prev = city;
    }
}

solution_t CreateRandom::operator()()
{
    // create a random path

    std::vector<size_t> path(_size+1);
    std::iota(path.begin(),path.end()-1,0);

    // begin+1 / end-1 to make paths always starting and ending at city 0,
    // with no loss of generality
    std::default_random_engine e( static_cast<unsigned int>(clock()) );
    std::shuffle(path.begin()+1,path.end()-1,e);

    // store it in the decision-node structure
    solution_t s(_size);
    from_path(path,s);

#ifdef __DEBUG__
    std::vector<size_t> p;
    atsp_decision::to_path(s,p);
    assert(path == p);
#endif

    return s;
}

std::ostream& atsp_decision::operator<<(std::ostream &os, const node_t &n)
{
  return os << "<" << n.prev << ","<< n.next << ">";
}

Neighborhood::trvec_t Neighborhood::operator()(const solution_t &s)
{
    const auto sz = s.size();
    static thread_local trvec_t trvec((sz-2)*(sz-2));
    //trvec_t trvec((sz-2)*(sz-2));

    // a transformation is defined as put city B after A
    // in the decision problem is equal to "activate bit AB"
    // the possible ways to do that to any given path without repetition
    // are limited.
    // each city on the path has a range of positions it can be switched to
    // for example
    // B on aBcdef can only be put after c,d,e,f: acBdef...acdefB
    // C on abCdef can only go after d,e,f. Note that before B is a repetition aCBdef
    //
    // the general rule is: a city at position P on the path, P=[1...N-1], can
    // only go back 1-P, forward N-P-1, cannot stay at the same place (0)
    // and go back one position (-1)
    // obs: starting at 1 and not at zero because, by definition, we consider
    // paths always starting and ending at city 0, with no loss of generality.
    //
    // Example
    //          0123456 (N = 7)
    // the D in abcDefg can go
    // 1-P = 1-3 = -2 postions backward (aDbcefg) to
    // N-P-1 = 7-3-1 = 3 positions forward (abcefgD)
    // cant stay at the same place (0)
    // cant move one position back (-1)
    //
    // each valid move defines a transformation AB: activate bit AB = put city B after A
    // on the path

    path_t path;
    to_path(s,path);
    size_t pos = 0;

    for(int P = 1; P < signed(sz); ++P)// sz = 7, cities [1..6]
    {
        auto cityB = path.at(size_t(P));

        for( int DP = 0; DP < signed(sz-1); ++DP )
        {
            int offset = 1 - P + DP;// 1 -[1..6] + [0 1 2 3 4 5] = 0..5/-1..4/....-5..0

            if ( offset != -1 && offset != 0 )
            {
                offset -= offset < 0 ? 1 : 0;
                auto cityA = path.at( size_t(P + offset) );
                trvec.at(pos++) = transformation_t(cityA,cityB);
            }
        }
    }

#ifdef __DEBUG__
        assert( pos == (sz-2)*(sz-2));
#endif

    return trvec_t(trvec);
    //return trvec;
}
#ifdef __DEBUG__
namespace
{

    using matrix = std::vector<std::vector<size_t>>;
    using path = std::vector<size_t>;

    size_t getCost(const matrix& data, const path& p)
    {
        uint cost = 0;
        auto sz = p.size();
        //path costs;
        for (uint i = 0; i < sz-1; ++i)
        {
          cost += data.at( p.at(i) ).at( p.at(i+1) );
          //costs.push_back( data.at( p.at(i) ).at( p.at(i+1) ) );
        }
        return cost;
    }

}
#endif

size_t atsp_decision::Objective::operator()(const solution_t & s)
{
   size_t cost = 0;
   size_t curr_city = 0;
   for(const auto& city : s)
   {
       cost += _data->at(curr_city++).at(city.next);
   }

#ifdef __DEBUG__

    path_t p;
    to_path(s,p);
    auto compare = getCost((*_data),p);
    assert(cost == compare);

#endif

   return cost;
}


std::vector<int> atsp_decision::DeltaObjective::operator()
(const solution_t & s, const std::vector<transformation_t>& trvec)
{
    size_t pos = 0;
    static thread_local std::vector<int> resvec( trvec.size() , 0);

    for(const auto& tr : trvec)
    {
        const auto & A = tr.first;
        const auto & Anext = s.at(A).next;
        const auto & B = tr.second;
        const auto & Bprev = s.at(B).prev;
        const auto & Bnext = s.at(B).next;

        signed delta = - int(_data->at(Bprev).at(B) +_data->at(B).at(Bnext) +_data->at(A).at(Anext) )
                + int(_data->at(Bprev).at(Bnext) + _data->at(A).at(B) + _data->at(B).at(Anext) );
        resvec.at(pos++) = delta;
        //resvec.push_back(delta);
    }

    return std::vector<int>(resvec);
}

DeltaAccept::Result DeltaAccept::operator()
(const delta_vector_t & delta_vec) const
{
    Result res;
    delta_t min = 0;
    size_t index = 0;

    for(const auto& d : delta_vec)
    {
        if (d < min)
        {
            min = d;
            res.index = index;
        }
        index++;
    }
    if (min<0) res.accepted = true;
    return res;
}

void Transform::operator()(solution_t & s, const transformation_t & t)
{
    const auto& A = t.first;
    const auto& B = t.second;
    auto Bnext = s.at(B).next;
    auto Bprev = s.at(B).prev;
    auto Anext = s.at(A).next;

    // remove B
    s.at(Bprev).next = Bnext;
    s.at(Bnext).prev = Bprev;

    // reinsert B after of A

    s.at(B).next = Anext;
    s.at(Anext).prev = B;
    s.at(B).prev = A;
    s.at(A).next = B;
}

DeltaAccept::Result DeltaAccept1stImprove::operator()
(const DeltaAccept::delta_vector_t & delta_vec) const
{
    Result res;
    size_t index = 0;

    for(const auto& d : delta_vec)
    {
        if (d < 0)
        {
            res.accepted = true;
            res.index = index;
            return res;
        }
        index++;
    }
    return res;
}

Neighborhood1StImprove::trvec_t Neighborhood1StImprove::operator()(const solution_t &s)
{
    const auto max_sz = ( s.size() - 2 )*( s.size() - 2 );
    static thread_local trvec_t trvec(max_sz);
    static thread_local size_t index = max_sz;

    if (index < max_sz)
    {
        index++;
        return trvec_t(1,trvec.at(index-1));
    }
    else
    {
        index = 1;
        atsp_decision::Neighborhood n;
        trvec = n(s);
        return trvec_t(1,trvec.at(0));
    }
}
