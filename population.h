/*
   Population Class - Maintains a population of individuals, each
                      representing a possible solution to a TSP.
*/

#include <vector>
#include <string>
#include "individual.h"

class Population {
private:  
   vector<Individual> current_individuals; 
   vector<Individual> new_individuals;
   int size;
   double elitism;
public:
   Population(string initial_paths_file, string tsp_data_file, int size, 
              double elitism);
   Individual Fittest();
   void Reproduce();
   void Selection();
   void Merge();
   void Genesis();
   void Evaluate();
};
