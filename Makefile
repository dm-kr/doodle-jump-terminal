CFLAGS=-Wall -pedantic -std=gnu99 -O3 -g
CC=gcc
BLD=build
LFLAGS=-lm

all: clean build

build: main

main: main.o player.o field.o getch.o
	@$(CC) $(CFLAGS) -o $(BLD)/main $(BLD)/main.o $(BLD)/player.o $(BLD)/field.o $(BLD)/getch.o $(LFLAGS)

main.o: main.c
	@$(CC) $(CFLAGS) -c main.c -o $(BLD)/main.o $(LFLAGS)

player.o: player.c
	@$(CC) $(CFLAGS) -c player.c -o $(BLD)/player.o $(LFLAGS)

field.o: field.c
	@$(CC) $(CFLAGS) -c field.c -o $(BLD)/field.o $(LFLAGS)

getch.o: getch.c
	@$(CC) $(CFLAGS) -c getch.c -o $(BLD)/getch.o $(LFLAGS)

clean:
	@rm -f main

run:
	@./$(BLD)/main

leaks:
	@valgrind --tool=memcheck --leak-check=full -s ./$(BLD)/main