"""

   Generates a cost table for a tsp given:
      a) number of cities in the tsp
      b) minimum desired cost
      c) maximum desired cost

   Usage: python tsp-builder.py <# cities> <min cost> <max cost>
   
   The cost table is written to a file specified in this script.

   File Format:
   # cities
   cityA cityB cost
   cityA cityC cost
   ...
   
   The costs are integers randomly generated in the range min cost to max cost.

"""
import sys
import random

out_fname = "tsp.dat"

# http://docs.python.org/library/itertools.html#itertools.combinations
# Note: this is available in Python 2.6
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
   0) Write the number of cities to a file.
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
   global out_fname
   outfile = open(out_fname, "w")
   outfile.write(str(num_cities) + "\n")
   
   # Generate pairings, write them to a file.
   for pairing in combinations(range(1, num_cities+1), 2):
      cost = int(random.uniform(min_cost, max_cost))
      outfile.write(str(pairing[0]) + " " + str(pairing[1]) + 
                    " " + str(cost) + "\n")

if __name__ == "__main__":
   main()
