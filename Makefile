CC       = clang++
CXX      = clang++
CFLAGS   = -g -Wall -Werror
CXXFLAGS = -g -Wall -Werror -std=c++14
LDLIBS   = -lmysqlcppconn
EXES     = tester
OBJS     = create_tuple.o tester.o

build: $(EXES)

$(EXES): create_tuple.o tester.o

$(OBJS): algorithms.hpp create_tuple.cpp create_tuple.hpp graph.hpp \
         graph_helper.hpp tester.cpp

clean:
	rm -f *~ a.out core $(EXES) $(OBJS)

all: clean build

run: build
	clear; nice -20 ./tester

valgrind: build
	reset; nice -20 valgrind --leak-check=full --show-leak-kinds=all ./tester
