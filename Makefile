CFLAGS=-Wall -pedantic -std=gnu99 -O3 -g
CC=gcc
BLD=build
LFLAGS=-lm 
C_FILES=main.c player.c field.c getch.c bars.c render.c
O_FILES=main.o player.o field.o getch.o bars.o render.o

.PHONY: all build clean run leaks

all: clean build

build: main

main: $(O_FILES)
	@$(CC) $(CFLAGS) -o $(BLD)/main $(BLD)/*.o $(LFLAGS)

main.o: main.c
	@$(CC) $(CFLAGS) -c main.c -o $(BLD)/main.o $(LFLAGS)

player.o: player.c
	@$(CC) $(CFLAGS) -c player.c -o $(BLD)/player.o $(LFLAGS)

field.o: field.c
	@$(CC) $(CFLAGS) -c field.c -o $(BLD)/field.o $(LFLAGS)

getch.o: getch.c
	@$(CC) $(CFLAGS) -c getch.c -o $(BLD)/getch.o $(LFLAGS)

bars.o: bars.c
	@$(CC) $(CFLAGS) -c bars.c -o $(BLD)/bars.o $(LFLAGS)

render.o: render.c
	@$(CC) $(CFLAGS) -c render.c -o $(BLD)/render.o $(LFLAGS)

clean:
	@rm -f main

run:
	@./$(BLD)/main

leaks:
	@valgrind --tool=memcheck --leak-check=full -s ./$(BLD)/main

cppcheck:
	@cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem $(C_FILES)