CC       = clang++
CXX      = clang++
CFLAGS   = -g -Wall -Werror
CXXFLAGS = -g -Wall -Werror -std=c++11
LDLIBS   = -lmysqlcppconn
EXES     = test_bellmanford   test_dijkstras   test_johnsons	test_prims
OBJS     = test_bellmanford.o test_dijkstras.o test_johnsons.o stopwatch.o test_helper.o test_prims.o

main:               test_bellmanford     test_dijkstras     test_johnsons	test_prims

test_bellmanford:   stopwatch.o          test_bellmanford.o test_helper.o

test_dijkstras:     stopwatch.o          test_dijkstras.o   test_helper.o

test_johnsons:      stopwatch.o          test_johnsons.o    test_helper.o

test_prims:      	stopwatch.o          test_prims.o    	test_helper.o

stopwatch.o:        stopwatch.cpp        stopwatch.hpp

test_bellmanford.o: test_bellmanford.cpp test_helper.hpp    algorithms.hpp graph.hpp

test_dijkstras.o:   test_dijkstras.cpp   test_helper.hpp    algorithms.hpp graph.hpp

test_johnsons.o:    test_johnsons.cpp    test_helper.hpp    algorithms.hpp graph.hpp

test_prims.o:    	test_prims.cpp   	 test_helper.hpp    algorithms.hpp graph.hpp

test_helper.o:      test_helper.hpp      graph_helper.hpp

clean:
	rm -f *~ a.out core $(EXES) $(OBJS)

all: clean main
