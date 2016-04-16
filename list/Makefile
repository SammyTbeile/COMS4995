CC  = clang++
CXX = clang++

CFLAGS   = -g -Wall -Werror
CXXFLAGS = -g -Wall -Werror -std=c++14

EXES = adjacency_list_test
OBJS = adjacency_list_test.o

build: $(EXES)

$(EXES):

$(OBJS): algorithms.hpp adjacency_list_exception.hpp adjacency_list.hpp

clean:
	rm -f *~ a.out core $(EXES) $(OBJS)

all: clean build

run: build
	clear; nice -20 ./adjacency_list_test

valgrind: build
	reset; nice -20 valgrind --leak-check=full --show-leak-kinds=all ./adjacency_list_test
