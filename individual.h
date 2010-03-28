/*
   Individual Class - Maintains an individual which represents a
                      path in the TSP.
*/


#ifndef _INDIVIDUAL_H_
#define _INDIVIDUAL_H_

#include <vector>

using namespace std;

class Individual {

protected:
   vector<int> chromosome;
   double raw_fitness;
   double fitness;

public:
   Individual();
   double Fitness();
   double Raw_Fitness();
   void Mutate();
   void Print();
};

#endif
