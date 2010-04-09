/*
   Population Class - Maintains a population of individuals, each
                      representing a possible solution to a TSP.
*/

#ifndef _POPULATION_H_
#define _POPULATION_H_

#include <vector>
#include <string>
#include <map>
#include <set>
#include "individual.h"

class Population {
private:  
   vector<Individual> current_individuals;
   vector<Individual> new_individuals;
   vector< vector< vector<int> > > breeders;
   
   // hash for cost table: maps set<int> to double (city pairs to distance)
   map< set<int>, double > cost_table;
   // hash for uniques    (maps vector<int> to int)
   set< vector<int> > unique_paths;

   unsigned int size;
   double elitism;
   double mutation_rate;
   string initial_paths_file;
   string tsp_data_file;
public:
   Population(string initial_paths_file, string tsp_data_file, int size, 
              double elitism, double mutation_rate);
   double Avg_Fitness();
   Individual Fittest();
   void Reproduce();
   void Selection();
   void Breed();
   void Crossover(vector<int> parent_a, vector<int> parent_b);
   void Mutation();
   void Filter();
   void Merge(bool init=false);
   void Genesis();
   void Evaluate();
};
#endif
