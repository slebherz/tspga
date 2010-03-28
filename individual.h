/*
   Individual Class - Maintains an individual which represents a
                      path in the TSP.
*/

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
