CC  = clang++
CXX = clang++

CFLAGS   = -g -Wall -Werror
CXXFLAGS = -g -Wall -Werror -std=c++14

EXES = graph_test
OBJS = graph_test.o

build: $(EXES)

$(EXES):

$(OBJS): graph.hpp graph_enum.hpp

clean:
	rm -f *~ a.out core $(EXES) $(OBJS)

all: clean build

run: build
	clear; nice -20 ./graph_test

valgrind: build
	reset; nice -20 valgrind --leak-check=full --show-leak-kinds=all ./graph_test
