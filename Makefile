CC       = clang++
CXX      = clang++
CFLAGS   = -g -Wall -Werror
CXXFLAGS = -g -Wall -Werror -std=c++14
LDLIBS   = -lmysqlcppconn
EXES     = test_bellmanford   test_dijkstras
OBJS     = test_bellmanford.o test_dijkstras.o test_helper.o

main:               test_bellmanford     test_dijkstras 

test_bellmanford:   test_bellmanford.o   test_helper.o

test_dijkstras:     test_dijkstras.o     test_helper.o

test_bellmanford.o: test_bellmanford.cpp test_helper.hpp  algorithms.hpp graph.hpp

test_dijkstras.o:   test_dijkstras.cpp   test_helper.hpp  algorithms.hpp graph.hpp

test_helper.o:      test_helper.hpp      graph_helper.hpp

clean:
	rm -f *~ a.out core $(EXES) $(OBJS)

all: clean main
