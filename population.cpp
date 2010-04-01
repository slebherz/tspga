/*
   Population Class - Maintains a population of individuals, each
                      representing a possible solution to a TSP.
*/

#include "population.h"
#include <cstdlib>
#include <vector>
#include <iostream>
#include <istream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include "explode.h"

using namespace std;

/* INCOMPLETE - add MUTATION_RATE */
Population::Population(string initial_paths_file, string tsp_data_file,
                       int size, double elitism) {

   string line;
   vector<double> line_values;
   set<int> city_pair;

   this->elitism = elitism;
   this->size = size;

   // Load the cost table
   ifstream cost_file;
   cost_file.open(tsp_data_file.c_str());

   // throw away the first line (number of cities)
   cost_file >> line;

   // populate the cost table with key/value pairs of (citypair, travel_cost)
   while( !cost_file.eof() )
   {
      cost_file >> line;
      line_values = double_explode(" ", line);
      city_pair.insert( (int)line_values[0] );
      city_pair.insert( (int)line_values[1] );
      this->cost_table[city_pair] = line_values[2];
      city_pair.clear();
   }
   cost_file.close();
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
   unsigned int i=0, j, prev_ind_index;
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
    for(it = this->current_individuals.begin(); it != this->current_individuals.end(); it++) {
      percent_contrib[i] = prev_sum + ((*it).Raw_Fitness() / total_pop_fitness);
      i++;
   }
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
   while(this->breeders.size() < ceil(this->size / 2)) {
      
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

/*
   Breeds a population of new individuals from the breeding pairs:
      1) Crossover
      2) Mutation
      3) Filter repeats
*/
void Population::Breed() {
   vector< vector< vector<int> > >::iterator it;
   vector<Individual>::iterator it2;
   
   while(this->new_individuals.size() < this->size) {
      
      // 1) Crossover
      for(it = this->breeders.begin(); it != this->breeders.end(); it++)
         this->Crossover((*it)[0], (*it)[1]);
      
      // 2) Mutation
      this->Mutation();

      /*
         3) Filter repeats: avoid wasting resources by filtering 
            out those new individuals that have already been evaluated
            in some prior generation.
      */
      for(it2 = this->new_individuals.begin(); it2 != this->new_individuals.end(); it2++) {
         // if ind is in uniques hash
            // remove them from this->new_pop
      }
   }
   this->breeders.clear();
}

/*
   Breed the pair to generate two children. Uses the 
*/
void Population::Crossover(vector<int> parent_a, vector<int> parent_b) {

}

/*
   Mutate the individuals in the population with a specified rate.
*/
void Population::Mutation() {
   double mutation_chance;
   vector<Individual>::iterator it;
   
   for(it = this->new_individuals.begin(); it != this->new_individuals.end(); it++) {
      mutation_chance = rand() / (double) (RAND_MAX + 1.0);
      if(this->mutation_rate < mutation_chance)
         (*it).Mutate();
   }
}

/*
   Merge the current population and the population of freshly evaluated
   individuals into the next generation of the current population:
      1) Choose the best <elitism>% members of the current population
      2) Fill the remaining slots with the best members of the
         union of the current and new populations.
   
   Elitism ensures that a portion of the best performers from the current
   population live to breed again.
*/
void Population::Merge() {

   vector<Individual> next_individuals;
   // pick the best <elitism>% members of old population
   int i, elite_count = (int)(elitism * size);

  sort(this->current_individuals.begin(), this->current_individuals.end());

   for(i = 0; i < elite_count; i++) {
      next_individuals.push_back(this->current_individuals.back());
      this->current_individuals.pop_back();
   }

   // fill remaining slots with the best of old and new populations
   
   // [size - size * <1 - elitism>] individuals
}

void Population::Genesis() {
   string line_in;
   vector<int> path;
   ifstream path_file_stream;
   path_file_stream.open(this->initial_paths_file.c_str());

   // create individuals with initial paths
   for(unsigned int i = 0; i < this->size; i++) {
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

bool operator<(const Individual& lhs, const Individual& rhs) {
  return ((Individual)lhs).Raw_Fitness() < ((Individual)rhs).Raw_Fitness();
}

