all: tspga

tspga: tspga.o population.o individual.o
	g++ tspga.o population.o individual.o -o tspga
   
tspga.o: tspga.cpp
	g++ -ansi -Wall -c tspga.cpp

population.o: population.cpp population.h
	g++ -ansi -Wall -c population.cpp

individual.o: individual.cpp individual.h
	g++ -ansi -Wall -c individual.cpp
   
clean:
	rm -rf *.o tspga
