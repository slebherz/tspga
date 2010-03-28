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
import itertools

out_fname = "tsp.dat"

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
   for pairing in itertools.combinations(range(1, num_cities+1), 2):
      cost = int(random.uniform(min_cost, max_cost))
      outfile.write(str(pairing[0]) + " " + str(pairing[1]) + 
                    " " + str(cost) + "\n")
   print "Successfully wrote " + out_fname

if __name__ == "__main__":
   main()
