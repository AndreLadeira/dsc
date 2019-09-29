#ifndef ATSP_H
#define ATSP_H

#include <vector>
#include <utility>
#include <string>
#include <fstream>

// data types

using std::vector;
using std::pair;
using std::string;
using std::ifstream;

struct Gambler
{
    Gambler(double initialBankroll);
    vector< vector<double> > knowledge;
    double bankroll;
};

using Node = pair<int,int>;
using Path = vector<Node>;
using ProblemData = vector< vector<int> >;

using loadDataFunctionT = void (*)(ifstream fname, ProblemData & data);
using createSolutionT   = void (*)(Path&);
using objectiveFunctionT =  int(Path&);

// operators

void loadData(ifstream fname, ProblemData & data);
void createSolution(Path&);
int  objectiveFunction(Path&);
// bool acceptSolution();


#endif // ATSP_H
