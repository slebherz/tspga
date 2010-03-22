all: tspga

tspga: tspga.o population.o individual.o
	g++ tspga.o population.o individual.o -o tspga
   
tspga.o:
	g++ -ansi -Wall tspga.cpp

population.o:
	g++ -ansi -Wall population.cpp

individual.o:
	g++ -ansi -Wall individual.cpp
   
clean:
	rm -rf *.o tspga
