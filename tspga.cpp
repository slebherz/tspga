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
#include <cstdio>
#include <time.h>
#include <sys/time.h>
#include "population.h"
#include "individual.h"

using namespace std;

#define EPSILON              0               // A percent (of the best path)
#define BEST_PATH            847             // Brute force tsp solution
#define MAX_ITERATIONS       100000          // Stop evolve loop when reached
#define MAX_STALE            1000             // Max consecutive iterations
                                             //    allowed without improvement
#define POP_SIZE             100             // Size of popultion. this is the 
                                             //    number of paths that Genesis
                                             //    will read in
#define ELITISM              0.20            // Percent of pop to preserve
#define MUTATION_RATE        0.30            // Chance a new indiv will mutate
#define INITIAL_PATHS_FNAME  "initial.dat"   // Paths for initial population
#define TSP_DATA_FNAME       "tsp.dat"       // TSP loaded from here

bool terminate(int num_iterations, double highest_fitness, int stale_iterations);
void log(int num_iterations, Population* tsp_pop);

int main() {
   struct timeval systime;
	double t1, t2, total_time;
   int num_iterations = 0;
   int last_fitness = 0;
   int stale_iterations = 0;

   /* Start Timer */
   gettimeofday(&systime,NULL);
	t1 = systime.tv_sec + (systime.tv_usec/1000000.0);
   
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

   while(!terminate(num_iterations, tsp_pop.Fittest().Raw_Fitness(), stale_iterations)) {
      tsp_pop.Reproduce();
      tsp_pop.Evaluate();
      tsp_pop.Merge();
      
      num_iterations++;

      // if there was no improvement of the max, increase stale_iterations
      if(tsp_pop.Fittest().Raw_Fitness() == last_fitness) {
         stale_iterations++;
      }
      else {
         stale_iterations = 0;
         last_fitness = tsp_pop.Fittest().Raw_Fitness();
      }

      // output stats every 10 generations
      if(num_iterations % 10 == 0) {
         log(num_iterations, &tsp_pop);
      }
   }
  
   /* End Timer */
   gettimeofday(&systime,NULL);
   t2 = systime.tv_sec + (systime.tv_usec/1000000.0);
   total_time = t2-t1;
   
   // Did we find the optimal path?
   if(tsp_pop.Fittest().Raw_Fitness() == BEST_PATH) {
      cout << "Optimal path (" << BEST_PATH << ") found!" << endl;
   }
   else {
      cout << "Optimal path (" << BEST_PATH << ") NOT found!" << endl;
   }
   
   printf("GA Time: %.1lf (seconds)\n", total_time);
   
   log(num_iterations, &tsp_pop);
   return 0;
}

/*
   Termination conditions - meeting any one is sufficient:
      1) Reached max number of iterations.
      2) Fittest individual's path is within epsilon of the best path.
*/
bool terminate(int num_iterations, double highest_fitness, int stale_iterations) {
   if(num_iterations == MAX_ITERATIONS)
      return true;
   
   if((highest_fitness - BEST_PATH) <= (EPSILON * BEST_PATH))
      return true;

   if(stale_iterations == MAX_STALE)
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
   printf("Average Fitness: %.1f\n", tsp_pop->Avg_Fitness());
   cout << "Fittest Individual:" << endl;
   tsp_pop->Fittest().Print();
   cout << endl << endl;
}
