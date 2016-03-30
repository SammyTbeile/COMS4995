CC  = clang++
CXX = clang++

CFLAGS   = -g -Wall -Werror
CXXFLAGS = -g -Wall -Werror -std=c++14

EXES = test_am
OBJS = test_am.o adjacency_matrix.o

build: $(EXES)

$(EXES): adjacency_matrix.o

$(OBJS): adjacency_matrix.h

clean:
	rm -f *~ a.out core $(EXES) $(OBJS)

run: build
	clear; nice -20 ./$(EXES)

all: clean build run

test: build
	reset; nice -20 valgrind --leak-check=full --show-leak-kinds=all ./$(EXES)
