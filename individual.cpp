/*
   Individual Class - Maintains an individual which represents a
                      path in the TSP.
*/

#include <cstdlib>
#include <iostream>
#include <vector>
#include "individual.h"

using namespace std;

   Individual::Individual() {

   }

   double Individual::Fitness() {
      return this->fitness;
   }
 
   double Individual::Raw_Fitness() {
      return this->raw_fitness;
   }
   
   /*
      Selects two cities at random and exchanges them.
   */
   void Individual::Mutate() {

   }
   
   void Individual::Print() {
   
   }
