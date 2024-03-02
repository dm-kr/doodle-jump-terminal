CFLAGS=-Wall -pedantic -std=gnu99 -O3 -g
CC=gcc
BLD=build
SRC=source
LFLAGS=-lm 
C_FILES=main.c player.c field.c getch.c bars.c render.c
O_FILES=main.o player.o field.o getch.o bars.o render.o

.PHONY: all build clean run leaks

all: build run clean

build: builddir main

main: $(O_FILES)
	@$(CC) $(CFLAGS) -o $(BLD)/main $(BLD)/*.o $(LFLAGS)

main.o: $(SRC)/main.c
	@$(CC) $(CFLAGS) -c $^ -o $(BLD)/main.o $(LFLAGS)

player.o: $(SRC)/player.c
	@$(CC) $(CFLAGS) -c $^ -o $(BLD)/player.o $(LFLAGS)

field.o: $(SRC)/field.c
	@$(CC) $(CFLAGS) -c $^ -o $(BLD)/field.o $(LFLAGS)

getch.o: $(SRC)/getch.c
	@$(CC) $(CFLAGS) -c $^ -o $(BLD)/getch.o $(LFLAGS)

bars.o: $(SRC)/bars.c
	@$(CC) $(CFLAGS) -c $^ -o $(BLD)/bars.o $(LFLAGS)

render.o: $(SRC)/render.c
	@$(CC) $(CFLAGS) -c $^ -o $(BLD)/render.o $(LFLAGS)

builddir:
	@mkdir -p $(BLD)

clean:
	@rm -rf $(BLD)/main $(BLD)/*.o

run:
	@./$(BLD)/main

leaks:
	@valgrind --tool=memcheck --leak-check=full -s ./$(BLD)/main

cppcheck:
	@cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem $(C_FILES)