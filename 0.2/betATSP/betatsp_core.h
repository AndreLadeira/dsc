#ifndef BETATSP_CORE_H
#define BETATSP_CORE_H

#include "core.h"
#include "atsp_decision.h"


namespace problems{
namespace atsp {
namespace atsp_decision{

struct Gambler
{
    Gambler():_k(_problem_sz,std::vector< double >(_problem_sz))
    {
        initKnowledge();
    }

    Gambler(const Gambler &g, double p):
        _k(g._k.size(),std::vector< double >(g._k.size()))
    {
        initKnowledge(g,p);
    }

    static void setProblemSize(size_t sz){_problem_sz = sz;}

    using matrix = std::vector< std::vector< double > >;
    //const matrix& k = _knowledge;

private:

    friend class House;

    matrix _k;
    void initKnowledge(void);
    void initKnowledge(const Gambler&, double p);

    static size_t _problem_sz;
};

class House
{
public:

    House() = delete;
    House(const House&) = delete;
    House& operator=(const House&) = delete;
    bool operator==(const House&) = delete;

    House( std::vector<Gambler>& gvec, double initialBankroll, double minBet, size_t trCount):
        //gamblers(gvec),
        _gamblers(gvec),
        _minBet(minBet),
        _initialBankroll(initialBankroll),
        _bankRolls(gvec.size(),initialBankroll),
        _picked(gvec.size(), std::vector<bool>(trCount)),
        _bet(gvec.size(),std::vector<double>(trCount)),
        _house_p(trCount)
    {}

    void getBets(const solution_t& s, const std::vector<transformation_t>& trvec);
    void processResults(const std::vector<int>& resvec);

   // const std::vector<const Gambler>& gamblers;

private:

   std::vector<Gambler>& _gamblers;
   // void replaceGambler();
   const double _minBet;
   const double _initialBankroll;

   std::vector<double> _bankRolls;
   std::vector< std::vector<bool> > _picked;
   std::vector< std::vector<double> > _bet;
   std::vector<double> _house_p;

};


}}}
#endif // BET_ATSP_H
