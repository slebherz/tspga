all: tspga

tspga: tspga.o population.o individual.o
	g++ tspga.o population.o individual.o -o tspga
   
tspga.o:
	g++ -ansi -Wall -c tspga.cpp

population.o:
	g++ -ansi -Wall -c population.cpp

individual.o:
	g++ -ansi -Wall -c individual.cpp
   
clean:
	rm -rf *.o tspga
