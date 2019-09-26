#ifndef ATSP_H
#define ATSP_H

#include <vector>


// data types

struct Gambler
{
    vector< vector<double> > knowledge;
    double bankroll;
};

using Node = pair<int,int>;
using Path = vector<Node>;
using ProblemData = vector< vector<int> >;

// operators

void loadData(string fname, ProblemData & data);
void initGambler(Gambler&);
void createPath(Path&);
int evaluate(Path&);


#endif // ATSP_H
