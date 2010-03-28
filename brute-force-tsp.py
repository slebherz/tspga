"""

   Brute Force TSP Solver:
      1) Generate all possible paths
      2) Evaluate all possible paths
      3) Find the minimum path

   Usage: python brute-force-tsp.py

"""

import itertools

data_fname = "tsp.dat"

# Merge two iterators into one.
def imerge(a, b):
    for i, j in itertools.izip(a,b):
        yield i
        yield j

# Evaluate a path: Sum the cost of all consecutive pairings
def Evaluate(path, cost_table):
   edges = (tuple(path[i-2:i]) for i in range(2, len(path)+1))
   return sum(cost_table[edge] for edge in edges)
            
def main():
   global data_fname
   """
      Build the cost table. Need to generate separate keys 
      for each pairing. For example, for the pairing (cityA, cityB)
      we need entries: (cityA, cityB) AND (cityB, cityA).
      
      Note that the lines will be stored in a list so we can use
      the splice operator.
   """
   lines = [line.split() for line in open(data_fname, "r")]
   triplets = ( ((int(line[0]), int(line[1])), int(line[2])) 
      for line in lines[1:])
   reverse_triplets = ( ((int(line[1]), int(line[0])), int(line[2])) 
      for line in lines[1:])
   cost_table = dict(imerge(triplets, reverse_triplets))

   # Generate all possible paths.
   num_cities = int(lines[0][0])
   paths = itertools.permutations(range(1,num_cities+1), num_cities)
   
   print "Data loaded from " + data_fname
   print "Solving a " + str(num_cities) + " city TSP."
   
   # Evaluate all possible paths.
   print "Minimum Path Cost: ", min(Evaluate(path, cost_table) for path in paths)
   
if __name__ == "__main__":
   main()
