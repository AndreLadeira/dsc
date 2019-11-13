#include <random>
#include <algorithm>
#include <cassert>
#include "betatsp_core.h"

using namespace problems::atsp::atsp_decision;

size_t Gambler::_problem_sz = 0;

void Gambler::initKnowledge()
{
    std::default_random_engine e( static_cast<unsigned int>(clock()) );
    auto max = e.max();

    for(auto & row : _k )
    {
        for( auto & value: row)
        {
            auto v = 1.0 * e() / max;
            value = v;
        }
    }
}

void Gambler::initKnowledge(const Gambler& g, double p)
{
    std::default_random_engine e( static_cast<unsigned int>(clock()) );
    auto max = e.max();

    size_t rowcnt = 0;
    for( auto& row : _k )
    {
        if ( ( e()/max) <= p )// copies from gambler, with prob. p
           //std::copy(row.begin(),row.end(),g._k.at(rowcnt).cbegin());
           row = g._k.at(rowcnt);
        else
            for( auto & value: row)
                value = e() / max; // or, else, gets new random values
        rowcnt++;
    }
}

void House::getBets(const solution_t& s, const std::vector<transformation_t> &trvec)
{
    // gamblers probabilities for each transformation
    // matrix of dimension #of_gamblers x #of_transformations
    std::vector< std::vector<double> >
            gamblers_p(_gamblers.size(), std::vector<double>(trvec.size()) );

    {
    size_t trCounter = 0;

    // 1st loop gets gamblers and house's probs

    for(const auto & tr : trvec)
    {
        const auto & A = tr.first;
        const auto & Anext = s.at(A).next;
        const auto & B = tr.second;
        const auto & Bprev = s.at(B).prev;
        const auto & Bnext = s.at(B).next;

        size_t gamblerCounter = 0;

        for( const auto & g : _gamblers)
        {
            const auto & k = g._k;

            auto p = -( k.at(Bprev).at(B) +k.at(B).at(Bnext) +k.at(A).at(Anext) )
                     +( k.at(Bprev).at(Bnext) + k.at(A).at(B) + k.at(B).at(Anext) );

            // (3+p)/6 takes p from [-3..3] to [0..1]
            p = (3 + p)/6;
            _house_p.at(trCounter) += p;
            gamblers_p.at(gamblerCounter).at(trCounter) = p;
#ifdef __DEBUG__
            assert( p <= 1.0 );
#endif

            gamblerCounter++;
        }
        _house_p.at(trCounter) /= _gamblers.size();
        trCounter++;
    }
    }

    // 2nd loop gets bets
    // if ones prob is bigger than house's, they bet.
    // ammount is given by Kelly's creterion


    {
    size_t gambler = 0;

    auto sz = _picked.at(gambler).size();

    for( const auto& gpvec : gamblers_p)
    {
        size_t transf = 0;
        // reset previous picks
        _picked.at(gambler) = std::vector<bool>(sz,false);

        for( const auto& p : gpvec )
        {
            const auto& hp = _house_p.at(transf);
            if (p > hp)
            {
                const auto o = 1.0/hp;
                const auto po = p*o;
                const auto kelly = (po - 1.0)/(o - 1.0);
                auto& bankroll = _bankRolls.at(gambler);
                auto bet = kelly * bankroll;

                bet = bet > _minBet ? bet : _minBet;
                bet = bet > bankroll ? bankroll : bet;

                bankroll -= bet;
                _picked.at(gambler).at(transf) = true;
                _bet.at(gambler).at(transf) = bet;

            }
            transf++;
        }
        gambler++;
    }
    }
}

void House::processResults(const std::vector<int> &resvec)
{
    const auto gcount = _gamblers.size();
    const auto rescount = resvec.size();

    for(size_t r = 0; r < rescount; r++)
    {
        const auto & res = resvec.at(r);
        for( size_t g = 0; g < gcount; g++)
        {
            if (_picked.at(g).at(r) && res > 0 )
                _bankRolls.at(g) += _bet.at(g).at(r) / _house_p.at(r);
        }
    }
}
/*



    std::vector<double> house_p(_gamblers.size());
    auto gcount = _gamblers.size();

    size_t gcounter = 0;

    // gets pij = probability of gambler i for the transformation j
    for( const auto & g : _gamblers )
    {
        size_t trcounter = 0;
        const auto & k = g.k;

        for(const auto & tr : transfs)
        {
            const auto & A = tr.first;
            const auto & Anext = s.at(A).next;
            const auto & B = tr.second;
            const auto & Bprev = s.at(B).prev;
            const auto & Bnext = s.at(B).next;



            gambler_p.at(gcounter).at(trcounter++) = p;
            house_p.at(gcounter) += p / gcount;
        }
        gcounter++;
    }

    // if my probability is bigger than house's...


    */




