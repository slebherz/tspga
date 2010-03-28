/*
   Population Class - Maintains a population of individuals, each
                      representing a possible solution to a TSP.
*/

#ifndef _POPULATION_H_
#define _POPULATION_H_

#include <vector>
#include <string>
#include "individual.h"

class Population {
private:  
   vector<Individual> current_individuals; 
   vector<Individual> new_individuals;
   vector< vector<Individual> > breeders;
   
   // hash for cost table (maps vector<int> to int)
   // hash for uniques    (maps vector<int> to int)
   
   int size;
   double elitism;
   string initial_paths_file;
   string tsp_data_file;
public:
   Population(string initial_paths_file, string tsp_data_file, int size, 
              double elitism);
   Individual Fittest();
   void Reproduce();
   void Selection();
   void Breed();
   void Merge();
   void Genesis();
   void Evaluate();
};
#endif
