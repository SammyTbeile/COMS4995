CC  = clang++
CXX = clang++

CFLAGS   = -g -Wall -Werror
CXXFLAGS = -g -Wall -Werror -std=c++14

EXES = adjacency_matrix_test
OBJS = adjacency_matrix_test.o

build: $(EXES)

$(EXES):

$(OBJS): algorithms.hpp adjacency_matrix_exception.hpp adjacency_matrix.hpp

clean:
	rm -f *~ a.out core $(EXES) $(OBJS)

all: clean build

run: build
	clear; nice -20 ./adjacency_matrix_test

valgrind: build
	reset; nice -20 valgrind --leak-check=full --show-leak-kinds=all ./adjacency_matrix_test
