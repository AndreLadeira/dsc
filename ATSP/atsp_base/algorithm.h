#ifndef ALGORITHM_H
#define ALGORITHM_H

//#include "path.h"

namespace atsp{
/*
 This class is the interface for the concept
 of an algorithm to solve the atsp problem.

 Many different algorithms exist, each with its
 particularities, but all have something in common:
 they do manipulate a path in the process of
 finding the minimum Eulerian Cycle

 Also, any algorithm works through two steps:

 1 - setup: values must be passed to the algorithm
 to set it up prior to its execution.

 The problem is that each algorithm has its own parameters.

 There are dozens of ways of doing this setup:

 class constructor: each dfferent algorithm requires different set
 of parameters what makes the implementation of polymorphism
 impossible.

 setters and getters: they are a pain in the neck and also change
 on each concrete algorithm

 some virtual method implemented as a variadic function: this is ugly,
 unsafe and slow, since the variable parameters shall be properly
 retrieved on every execution of the method

 Builder pattern: note to self: return on this later

 Derivation: is the chosen method. Its expected to have
 a single instance of an algorithm per execution, so
 the derived class variables are static.

 Access restrictions (read-write) are implemented through
 references, because there is only one instance of a particular
 algorithim and because direct access through references
 may speed things up a bit compared to a accessor method

 2 - execution: this can be done in many ways:
 I chose to enforce it by amking it just a functor.
 One less method to name (execute(), load(), action(),
 run().....)

*/

class Path;

class algorithm
{
public:
    typedef unsigned uint;
    virtual ~algorithm();
    virtual uint operator()(Path &) const = 0;
};

// greedy is used by many other algorithms

class greedy_algorithm : public algorithm
{

public:

    greedy_algorithm();

    virtual uint operator()(Path &) const;

    uint _pos;
    uint _length;

};

}

#endif // ALGORITHM_H
