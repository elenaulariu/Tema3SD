build: movies

movies: movies.o graph.o queue.o
	gcc movies.o graph.o queue.o -o movies

movies.o: movies.c

graph.o: graph.h graph.c

queue.o: queue.h queue.c

run:
	./movies

memcheck:
	valgrind --leak-check=full ./movies

make clean:
	rm -f *.o movies