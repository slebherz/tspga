/*
   Population Class - Maintains a population of individuals, each
                      representing a possible solution to a TSP.
*/

#include <vector>
#include "individual.h"

class Population {
private:  

public:
   vector<Population> bar;
   
   Individual Fittest();
   void Reproduce();
   void Selection();
   void Merge();
   void Genesis();
   void Evaluate();
};
