#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__
/*
 * Filename: graph.hpp
 * Author:   Sean Garvey
 * UNI:      sjg2174
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include "graph_exception.hpp"

class Algorithms;
enum graph_t { LIST, MATRIX };

/* Graph -------------------------------------------------------------------- */

class Graph {
  friend class Algorithms;
  private:
    /* Variables */
    std::vector<std::vector<std::pair<unsigned long, double>>> list;
    std::vector<std::vector<double>> matrix;
    std::vector<std::vector<bool>> visited;
    unsigned long num_edges;
    unsigned long num_vertices;

    /* Private Member Functions */
    void construct_list();
    void construct_matrix();  
    template<typename Container>
    void copy_list(Container container);
    template<typename Container>
    void copy_matrix(Container container);
    std::vector<std::pair<unsigned long, double>>& get_neighbors(unsigned long
      row);
    void set_visited(unsigned long row, unsigned long col, bool b);

  public:
    /* Constructors */
    template<typename Container>
    Graph(Container container, graph_t g);
    Graph(const Graph& g);

    /* Public Member Functions */
    unsigned long get_num_edges();
    unsigned long get_num_vertices();
    bool get_visited(unsigned long row, unsigned long col);
    double get_weight(unsigned long row, unsigned long col);

    /* Operators */
    Graph& operator=(const Graph& g);
    friend std::ostream& operator<<(std::ostream& os, const Graph& g);
};

/* Private Member Functions ------------------------------------------------- */

// construct_list
void Graph::construct_list() {
  list = std::vector<std::vector<std::pair<unsigned long, double>>>();
  list.resize(num_vertices);
  double dist;
  for(unsigned long i = 0; i < num_vertices; ++i) {
    list[i].reserve(num_vertices);
    for(unsigned long j = 0; j < num_vertices; ++j) {
      if((dist = matrix[i][j]) > 0) {
        list[i].push_back(std::make_pair(j, dist));
      }
    }
    list[i].shrink_to_fit();
  }
}

// construct_matrix
void Graph::construct_matrix() {
  matrix = std::vector<std::vector<double>>();
  matrix.resize(num_vertices);
  for(unsigned long i = 0; i < num_vertices; ++i) {
    matrix[i].resize(num_vertices);
    unsigned long adjacent_vertices = list[i].size();
    for(unsigned long j = 0; j < adjacent_vertices; ++j) {
      auto pair = list[i][j];
      matrix[i][pair.first] = pair.second;
    }
  }
}

// copy_list
template<typename Container>
void Graph::copy_list(Container container) {
  list = std::vector<std::vector<std::pair<unsigned long, double>>>();
  num_vertices = container.size();
  list.reserve(num_vertices);
  unsigned long index = 0;
  for(auto it = container.begin(); it != container.end(); ++it, ++index) {
    list.push_back(std::vector<std::pair<unsigned long, double>>(it->begin(),
        it->end()));
    auto set = std::unordered_set<unsigned long>();
    auto row = list[index];        
    for(auto& e : row) {
      if(set.insert(e.first).second == false) {
        throw Graph_Exception("List representation has more than one edge in "
            "the same direction between two nodes");
      } else if(e.second <= 0) {
        throw Graph_Exception("List representation has non positive edges\n");
      }
      ++num_edges;
    }
  }
}

// copy_matrix
template<typename Container>
void Graph::copy_matrix(Container container) {
  matrix = std::vector<std::vector<double>>();
  num_vertices = container.size();
  matrix.reserve(num_vertices);
  unsigned int index = 0;
  for(auto it = container.begin(); it != container.end(); ++it, ++index) {
    matrix.push_back(std::vector<double>(it->begin(), it->end()));
    auto row = matrix[index];
    if(row.size() != num_vertices) {
      throw Graph_Exception("Matrix representation is not square\n");
    }
    for(auto& e : row) {
      if(e > 0) {
        ++num_edges;
      } else if(e < 0) {
        throw Graph_Exception("Matrix representation has negative edges\n");
      }
    }
  }
}

// get_neighbors
std::vector<std::pair<unsigned long, double>>& Graph::get_neighbors(unsigned
    long row) {
  if(row >= num_vertices) {
    throw Graph_Exception("get_neighbors out of range access\n");
  }
  return list[row];
}

// set_visited
void Graph::set_visited(unsigned long row, unsigned long col, bool b) {
  if(row >= num_vertices || col >= num_vertices) {
    throw Graph_Exception("set_visited out of range access\n");
  }
  visited[row][col] = b;
}

/* Constructors ------------------------------------------------------------- */

// Constructor
template<typename Container>
Graph::Graph(Container container, graph_t g) {
  if(g == LIST) {
    copy_list(container);
    construct_matrix();
  } else if(g == MATRIX) {
    copy_matrix(container);
    construct_list();
  } else {
    throw Graph_Exception("Undefined representation\n");
  }
  visited = std::vector<std::vector<bool>>();
  visited.reserve(num_vertices);
  for(auto it = visited.begin(); it != visited.end(); ++it) {
    *it = std::vector<bool>(num_vertices);
  }
}

// Copy Constructor
Graph::Graph(const Graph& g) {
  list = g.list;
  matrix = g.matrix;
  num_edges = g.num_edges;
  num_vertices = g.num_vertices;
}

/* Public Member Functions -------------------------------------------------- */

// get_num_edges
unsigned long Graph::get_num_edges() {
  return num_edges;
}

// get_num_vertices
unsigned long Graph::get_num_vertices() {
  return num_vertices;
}

// get_visited
bool Graph::get_visited(unsigned long row, unsigned long col) {
  if(row >= num_vertices || col >= num_vertices) {
    throw Graph_Exception("get_visited out of range access\n");
  }
  return visited[row][col];
}

// get_weight
double Graph::get_weight(unsigned long row, unsigned long col) {
  if(row >= num_vertices || col >= num_vertices) {
    throw Graph_Exception("get_weight out of range access\n");
  }
  return matrix[row][col];
}

/* Operators ---------------------------------------------------------------- */

// =
Graph& Graph::operator=(const Graph& g) {
  if(this == &g) {
    return *this;
  }
  list = g.list;
  matrix = g.matrix;
  num_edges = g.num_edges;
  num_vertices = g.num_vertices;
  return *this;
}

// <<
std::ostream& operator<<(std::ostream& os, const Graph& g) { 
  for(auto& row : g.matrix) {
    bool first = true;
    for(auto& col : row) {
      if(first) {
        os << col;
      } else {
        os << ',' << col;
      }
    }
    os << '\n';
  } 
  return os;
}

#endif
