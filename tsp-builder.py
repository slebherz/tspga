"""

   Generates a cost table for a tsp given:
      a) number of cities in the tsp
      b) minimum desired cost
      c) maximum desired cost

   Usage: python tsp-builder.py <# cities> <min cost> <max cost>
   
   The cost table is written to a file specified in this script.
   
   The costs are integers randomly generated in the range min cost to max cost.

"""

import sys
import random

def combinations(iterable, r):
    # combinations('ABCD', 2) --> AB AC AD BC BD CD
    # combinations(range(4), 3) --> 012 013 023 123
    pool = tuple(iterable)
    n = len(pool)
    if r > n:
        return
    indices = range(r)
    yield tuple(pool[i] for i in indices)
    while True:
        for i in reversed(range(r)):
            if indices[i] != i + n - r:
                break
        else:
            return
        indices[i] += 1
        for j in range(i+1, r):
            indices[j] = indices[j-1] + 1
        yield tuple(pool[i] for i in indices)

"""
   1) Generate all possible combinations of city pairings.
   2) Write pairings to a file, with a random cost per pairing.
"""
def main():
   if len(sys.argv) != 4:
      print "Usage: python tsp-builder.py <# cities> <min cost> <max cost>"
      sys.exit()
   
   # Setup
   num_cities = int(sys.argv[1])
   min_cost = int(sys.argv[2])
   max_cost = int(sys.argv[3])
   outfile = open("tsp.dat", "w")
   
   # Generate pairings, write them to a file.
   for pairing in combinations(range(1, num_cities+1), 2):
      cost = int(random.uniform(min_cost, max_cost))
      outfile.write(str(pairing[0]) + " " + str(pairing[1]) + 
                    " " + str(cost) + "\n")

if __name__ == "__main__":
   main()
