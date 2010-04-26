all: tspga

tspga: tspga.o population.o individual.o Makefile
	g++ -fopenmp -march=native tspga.o population.o individual.o -o tspga

tspga.o: tspga.cpp Makefile
	g++ -fopenmp -march=native -ansi -Wall -c tspga.cpp

population.o: population.cpp population.h Makefile
	g++ -fopenmp -march=native -ansi -Wall -c population.cpp

individual.o: individual.cpp individual.h Makefile
	g++ -fopenmp -march=native -ansi -Wall -c individual.cpp

clean:
	rm -rf *.o tspga Otsp* tsp.mas tsp.pul tsp.sol tsp.sav
