COMPILER = gcc
CCFLAGS = -g -Wall
all: m1

m1: main.o mallocwithcomments.o
	$(COMPILER) $(CCFLAGS) -o m1 main.o mallocwithcomments.o
main.o: main.c malloc.h
	$(COMPILER) $(CCFLAGS) -c main.c
mallocwithcomments.o: mallocwithcomments.c malloc.h
	$(COMPILER) $(CCFLAGS) -c mallocwithcomments.c
clean:
	rm -f m1
	rm -f *.o
