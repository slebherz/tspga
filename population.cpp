/*
   Population Class - Maintains a population of individuals, each
                      representing a possible solution to a TSP.
*/

#include "population.h"
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include "explode.h"

using namespace std;

Population::Population(string initial_paths_file, string tsp_data_file,
                       int size, double elitism) {
   this->tsp_data_file = tsp_data_file;
   
   // Load the cost table
   
   // Assign size and elitism
}

Individual Population::Fittest() {
   // return the most fit individual in the population
}

void Population::Reproduce() {
   this->Selection();
   this->Breed();
}

void Population::Selection() {
   //  standardize each score to a percent
   // get a random in 0,1 and iterate through stand. ind scores until you hit the correct one
}

void Population::Breed() {
   // while the number of new individuals is less than the desired number:
      // crossover
      // mutation
      // filter repeats
}

void Population::Merge() {
   // pick the best <elitism>% members of old population
   // fill remaining slots with the best of old and new populations
   // [size - size * <1 - elitism>] individuals
}

void Population::Genesis() {
   string line_in;
   vector<int> path;
   ifstream path_file_stream;
   path_file_stream.open(this->initial_paths_file.c_str());

   // create individuals with initial paths
   int i;
   for(i = 0; i < this->size; i++) {
      path_file_stream >> line_in;
      path = int_explode(" ", line_in);
      this->current_individuals.push_back(Individual(path));
   }

   path_file_stream.close();
}

void Population::Evaluate() {
   /*
      for individual in new population
         look at each adjacent city-pair in chromosome:
            sum += cost(pair)
   */
}
