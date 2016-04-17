CC  = clang++
CXX = clang++

CFLAGS   = -g -Wall -Werror
CXXFLAGS = -g -Wall -Werror -std=c++14

LDLIBS = -lmysqlcppconn

EXES = test_representations
OBJS = test_representations.o create_representations.o graph_helper.o graph_helper_exception.o

build: $(EXES)

$(EXES): graph_helper.o graph_helper_exception.o create_representations.o

$(OBJS): graph_helper.hpp graph_helper_exception.hpp create_representations.hpp

clean:
	rm -f *~ a.out core $(EXES) $(OBJS)

all: clean build

run: build
	clear; nice -20 ./test_representations

valgrind: build
	reset; nice -20 valgrind --leak-check=full --show-leak-kinds=all ./test_representations
