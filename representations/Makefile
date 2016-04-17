CC  = clang++
CXX = clang++

CFLAGS   = -g -Wall -Werror
CXXFLAGS = -g -Wall -Werror -std=c++14

LDLIBS = -lmysqlcppconn

EXES = create_tuple_test
OBJS = create_tuple_test.o create_tuple.o

build: $(EXES)

$(EXES): create_tuple.o

$(OBJS): create_tuple.hpp graph_helper.hpp graph.hpp graph_enum.hpp

clean:
	rm -f *~ a.out core $(EXES) $(OBJS)

all: clean build

run: build
	clear; nice -20 ./create_tuple_test

valgrind: build
	reset; nice -20 valgrind --leak-check=full --show-leak-kinds=all ./create_tuple_test
