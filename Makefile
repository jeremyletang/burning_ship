## Makefile for burning_ship project

CC         = g++ -std=c++11
CFLAGS     = -c -Wall
BIN        = $(BIN_FOLDER)/burning_ship
# SRCS       = src/main.cpp
SRCS       = $(wildcard src/*.cpp)
INC        = -Iincludes
LIB        = -lpng -lm -fopenmp
BIN_FOLDER = bin
OBJS       = $(SRCS:.cpp=.o)
CFLAGS     = $(INC)


all: $(SRCS) $(BIN)

$(BIN): $(OBJS)
	mkdir -p $(BIN_FOLDER)
	$(CC) -std=c++11 $(LIB) $(OBJS) -o $@

clean:
	rm -rf src/*.o
	rm -rf $(BIN_FOLDER)/*.png
	rm -rf $(BIN_FOLDER)/*.mp4

fclean: clean
	rm -rf $(BIN_FOLDER)
