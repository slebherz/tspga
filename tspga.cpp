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
#include <population.h>
#include <individual.h>

using namespace std;

#define EPSILON        10              /* SETTING */
#define BEST_PATH      100             /* SETTING */
#define MAX_ITERATIONS 1000            /* SETTING */
#define INITIAL_POP    "initial.dat"   /* SETTING */

bool terminate(int num_iterations, float highest_fitness);

int main() {
   int num_iterations = 0;
   
   /*
      Setup for evolution loop:
         1) Construct a new population.
         2) Genesis event occurs.
         3) Evaluate initial population
   */
   Population tsp_pop(INITIAL_POP);
   tsp_pop.Genesis();
   tsp_pop.Evaluate();
   
   /*
      Evolution - Do this until termination conditions are met:
         1) Reproduce
         2) Evaluate offspring.
         3) Merge current population and offspring.
         4) log dump, visualization update, etc...
   */
   while !terminate(num_iterations, Population.Fittest().raw_fitness) {
      tsp_pop.Reproduce();
      tsp_pop.Evaluate();
      tsp_pop.Merge();
      
      num_iterations++;
      if(num_iterations % 10 == 0)
         cout << "Generation: " << num_iterations << endl;
   }

   cout << "Total Generations: " << num_iterations << endl;
   tsp_pop.Fittest().Print()
   return 0;
}

/*
   Termination conditions - meeting any one is sufficient:
      1) Reached max number of iterations.
      2) Fittest individual's path is within epsilon of the best path.
*/
bool terminate(int num_iterations, float highest_fitness) {
   if(num_iterations == MAX_ITERATIONS)
      return true;
   
   if((highest_fitness - BEST_PATH) <= EPSILON)
      return true;
   
   return false;
}
