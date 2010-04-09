/*
   Driver that constructs a Genetic Algorithm (GA) to 
   solve the Traveling Salesman Problem (TSP).
   
   Essentially, here is what goes down:
   
      1) Construct a population.
      2) Genesis, initial evaluation.
      3) Evolve until termination conditions are satisfied:
         a) Reproduce
         b) Evaluate
         c) Merge
*/

#include <iostream>
#include "population.h"
#include "individual.h"

using namespace std;

#define EPSILON              0               // a percent (of the best path)
#define BEST_PATH            554             // brute force tsp solution
#define MAX_ITERATIONS       1000            // stop evolve loop when reached
#define POP_SIZE             100             // size of popultion. this is the number of paths that Genesis will read in
#define ELITISM              0.20            // percent of pop to preserve
#define MUTATION_RATE        0.20            // chance a new ind will mutate
#define INITIAL_PATHS_FNAME  "initial.dat"   // paths for initial population
#define TSP_DATA_FNAME       "tsp.dat"       // tsp loaded from here

bool terminate(int num_iterations, double highest_fitness);
void log(int num_iterations, Population* tsp_pop);

int main() {
   int num_iterations = 0;
   
   /*
      Setup for evolution loop:
         1) Construct a new population.
         2) Genesis event occurs.
         3) Evaluate initial population
   */
   Population tsp_pop(INITIAL_PATHS_FNAME, TSP_DATA_FNAME, POP_SIZE, ELITISM, MUTATION_RATE);
   tsp_pop.Genesis();
   tsp_pop.Evaluate();
   tsp_pop.Merge(true);
   
   /*
      Evolution - Do this until termination conditions are met:
         1) Reproduce
         2) Evaluate offspring.
         3) Merge current population and offspring.
         4) log dump, visualization update, etc...
   */

   while(!terminate(num_iterations, tsp_pop.Fittest().Raw_Fitness())) {
      tsp_pop.Reproduce();
      tsp_pop.Evaluate();
      tsp_pop.Merge();
      
      num_iterations++;
      if(num_iterations % 10 == 0) {
         log(num_iterations, &tsp_pop);
      }
   }
   
   log(num_iterations, &tsp_pop);
   return 0;
}

/*
   Termination conditions - meeting any one is sufficient:
      1) Reached max number of iterations.
      2) Fittest individual's path is within epsilon of the best path.
*/
bool terminate(int num_iterations, double highest_fitness) {
   if(num_iterations == MAX_ITERATIONS)
      return true;
   
   if((highest_fitness - BEST_PATH) <= (EPSILON * BEST_PATH))
      return true;
   
   return false;
}

/*
   Displays:
      Generation
      Average Fitness
      Best Individual
*/
void log(int num_iterations, Population* tsp_pop) {
   cout << "Generation: " << num_iterations << endl;
   printf("%.1f\n", tsp_pop->Avg_Fitness());
   tsp_pop->Fittest().Print();
   cout << endl << endl;
}
