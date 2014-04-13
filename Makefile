## Makefile for burning_ship project

CC         = g++
CFLAGS     = -c -Wall
BIN        = $(BIN_FOLDER)/burning_ship
# SRCS       = src/main.cpp
SRCS       = $(wildcard src/*.cpp)
INC        = -Iincludes
LIB        = -lpng -lm
BIN_FOLDER = bin
OBJS       = $(SRCS:.cpp=.o)
CFLAGS     = $(INC) -std=c++11


all: $(SRCS) $(BIN)

$(BIN): $(OBJS)
	mkdir -p $(BIN_FOLDER)
	$(CC) $(LIB) $(OBJS) -o $@

clean:
	rm -rf src/*.o

fclean: clean
	rm -rf $(BIN_FOLDER)
