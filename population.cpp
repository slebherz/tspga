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
}

Individual Population::Fittest() {

}

void Population::Reproduce() {
   // lots of crossover business
}

void Population::Selection() {

}

void Population::Merge() {

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

}
