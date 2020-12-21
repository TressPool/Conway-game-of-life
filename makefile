# Makefile comments……
PROGRAMS = driver
CC = gcc
CFLAGS = -Wall -g
all: $(PROGRAMS)
clean:
	rm -f *.o
# C compilations
point2D.o: point2D.c point2D.h
	$(CC) $(CFLAGS) -c point2D.c
graph.o: graph.c graph.h point2D.h
	$(CC) $(CFLAGS) -c graph.c
driver.o: driver.c graph.h point2D.h
	$(CC) $(CFLAGS) -c driver.c
# Executable programs
driver: driver.o graph.o point2D.o
	$(CC) $(CFLAGS) -o driver driver.o graph.o point2D.o

