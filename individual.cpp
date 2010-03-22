/*
File: individual.cpp

Represents an individual of a popultion for a genetic algorithm.


*/


#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

class Individual {

protected:
   vector<int> chromosome;
   double raw_fitness;
   double fitness;

public:

   Individual() {

   }

   double fitness() {

   }
 
  
   double raw_fitness() {
   
   }  

   
   void Mutate() {

   }
};
