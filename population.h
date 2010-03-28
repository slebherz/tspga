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
   double elitism;
public:
   Population(string initial_paths_file, string data_file, double elitism);
   Individual Fittest();
   void Reproduce();
   void Selection();
   void Merge();
   void Genesis();
   void Evaluate();
};

#endif