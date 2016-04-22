CC  = clang++
CXX = clang++

CFLAGS   = -g -Wall -Werror
CXXFLAGS = -g -Wall -Werror -std=c++14

EXES = tester
OBJS = tester.o algorithms.o create_tuple.o

build: $(EXES)

$(EXES): algorithms.o create_tuple.o tester.o

$(OBJS): algorithms.hpp algorithms.cpp create_tuple.hpp create_tuple.cpp \
         graph.hpp graph_helper.hpp tester.cpp

clean:
	rm -f *~ a.out core $(EXES) $(OBJS)

all: clean build

run: build
	clear; nice -20 ./tester

valgrind: build
	reset; nice -20 valgrind --leak-check=full --show-leak-kinds=all ./tester
