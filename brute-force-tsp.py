"""

   Brute Force TSP Solver:
      1) Generate all possible paths
      2) Evaluate all possible paths
      3) Find the minimum path

"""

import itertools

# From: http://docs.python.org/library/itertools.html#itertools.permutations
# Note: this is available in Python 2.6
def permutations(iterable, r=None):
    # permutations('ABCD', 2) --> AB AC AD BA BC BD CA CB CD DA DB DC
    # permutations(range(3)) --> 012 021 102 120 201 210
    pool = tuple(iterable)
    n = len(pool)
    r = n if r is None else r
    if r > n:
        return
    indices = range(n)
    cycles = range(n, n-r, -1)
    yield tuple(pool[i] for i in indices[:r])
    while n:
        for i in reversed(range(r)):
            cycles[i] -= 1
            if cycles[i] == 0:
                indices[i:] = indices[i+1:] + indices[i:i+1]
                cycles[i] = n - i
            else:
                j = cycles[i]
                indices[i], indices[-j] = indices[-j], indices[i]
                yield tuple(pool[i] for i in indices[:r])
                break
        else:
            return

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
   """
      Build the cost table. Need to generate separate keys 
      for each pairing. For example, for the pairing (cityA, cityB)
      we need entries: (cityA, cityB) AND (cityB, cityA).
   """
   lines = [line.split() for line in open("tsp.dat", "r")]
   triplets = ( ((int(line[0]), int(line[1])), int(line[2])) 
      for line in lines[1:])
   reverse_triplets = ( ((int(line[1]), int(line[0])), int(line[2])) 
      for line in lines[1:])
   cost_table = dict(imerge(triplets, reverse_triplets))

   # Generate all possible paths.
   num_cities = int(lines[0][0])
   paths = permutations(range(1,num_cities+1), num_cities)
   
   # Evaluate all possible paths.
   print "Minimum Path Cost: ", min(Evaluate(path, cost_table) for path in paths)
   
if __name__ == "__main__":
   main()
