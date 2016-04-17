CC  = clang++
CXX = clang++

CFLAGS   = -g -Wall -Werror
CXXFLAGS = -g -Wall -Werror -std=c++14

EXES = graph_helper_test
OBJS = graph_helper_test.o

build: $(EXES)

$(EXES):

$(OBJS):

clean:
	rm -f *~ a.out core $(EXES) $(OBJS)

all: clean build

run: build
	clear; nice -20 ./graph_helper_test

valgrind: build
	reset; nice -20 valgrind --leak-check=full --show-leak-kinds=all ./graph_helper_test
