CC  = clang++
CXX = clang++

CFLAGS   = -g -Wall -Werror
CXXFLAGS = -g -Wall -Werror -std=c++14

EXES = algorithms_test
OBJS = algorithms_test.o

build: $(EXES)

$(EXES): algorithms.o

$(OBJS): algorithms.hpp \
         adjacency_matrix.hpp           adjacency_list.hpp \
         adjacency_matrix_exception.hpp adjacency_list_exception.hpp

clean:
	rm -f *~ a.out core $(EXES) $(OBJS)

all: clean build

run: build
	clear; nice -20 ./algorithm_test

valgrind: build
	reset; nice -20 valgrind --leak-check=full --show-leak-kinds=all ./algorithm_test
