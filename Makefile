CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb `pkg-config --cflags sdl2`
LIBS=`pkg-config --libs sdl2` -lm

dvd-logo: main.o
	$(CC) $(CFLAGS) -o dvd-logo main.o $(LIBS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o $(LIBS)
