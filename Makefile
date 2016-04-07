CC  = clang++
CXX = clang++

CFLAGS   = -g -Wall -Werror
CXXFLAGS = -g -Wall -Werror -std=c++14

EXES = matrix_test   list_test
OBJS = matrix_test.o list_test.o

build: $(EXES)

$(EXES):

$(OBJS): adjacency_matrix.h adjacency_list.h

clean:
	rm -f *~ a.out core $(EXES) $(OBJS)

all: clean build

matrix: matrix_test

list: list_test

run_matrix: matrix
	clear; nice -20 ./matrix_test

run_list: list
	clear; nice -20 ./list_test

valgrind_matrix: matrix
	reset; nice -20 valgrind --leak-check=full --show-leak-kinds=all ./matrix_test

valgrind_test: list
	reset; nice -20 valgrind --leak-check=full --show-leak-kinds=all ./list_test
