/*
   Population Class - Maintains a population of individuals, each
                      representing a possible solution to a TSP.
*/

#include "population.h"
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
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

/*
   Pairs up individuals for breeding. The higher an individual's fitness
   the more likely it will be selected to breed.
*/
void Population::Selection() {
   unsigned int i, j, prev_ind_index;
   bool asexual;
   double total_pop_fitness = 0;
   double prev_sum = 0;
   double breeding_chance, current_chance;
   vector<double> percent_contrib;
   vector< vector<int> > breed_pair;
   vector<Individual>::iterator it;

   // 1) Calculate total fitness of the population.
   for(it = this->current_individuals.begin(); it != this->current_individuals.end(); it++)
      total_pop_fitness += (*it).Raw_Fitness();
      
   // 2) Build lookup table of percent contribution to total.
    for(it = this->current_individuals.begin(); it != this->current_individuals.end(); it++)
      percent_contrib[i] = prev_sum + ((*it).Raw_Fitness() / total_pop_fitness);
   
   /* 
      3) Make breeder pairs:
         Until we have paired up enough breeders:
            Select using the 'roulette wheel' approach. 'Spin' the roulette
            to get a breeding chance. Then iterate through the individuals,
            summing their percent contribution until we hit the lucky 
            'partition' of the roulette wheel: where the cumulative percent
            contribution is greater than the breeding chance.
            
         We will match up a number of pairs equal to the ceiling of
         (POP SIZE / 2). This is because each breeding pair should, 
         ideally, breed 2 children for a total of POP SIZE children.
   */
   while(this->breeders.size() < ceil(this->current_individuals.size() / 2)) {
      
      for(i = 0; i < 2; i++) { // Make a couple.
         current_chance = 0;
         breeding_chance = rand() / (double) (RAND_MAX + 1.0);
         
         // Find the lucky individual.
         for(j = 0; j < percent_contrib.size(); j++) {
            current_chance += percent_contrib[j];
            
            if(current_chance > breeding_chance) { // lucky individual found!
               current_chance = 0;
               break;
            }
         }
         
         // Keep track of indices of selected inds to prevent asexual selection.
         if(i == 0) {
            prev_ind_index = j;
            asexual = false;
         }
         if( (i == 1) && (prev_ind_index == j) ) {
            asexual = true;
         }
      
         // Add the selected individual's path to a breeding pair.
         breed_pair.push_back((this->current_individuals[j]).Chromosome());
      }
      
      // asexual reproduction prohibited
      if(!asexual) {
         vector< vector<int> > breed_pair_copy (breed_pair);
         this->breeders.push_back(breed_pair_copy);
      }
      breed_pair.clear();
   }
}

void Population::Breed() {
   // while the number of new individuals is less than the desired number:
      // crossover
      // mutation
      // filter repeats
   // empty this->breeders
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
