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

// Forward Declaration
class Algorithms;

/* Graph_Exception ---------------------------------------------------------- */

class Graph_Exception : public std::exception {
private:
  const char* message;
public:
  Graph_Exception(const char* msg) { message = msg; }
  virtual const char* what() const throw() { return message; }
};

/* Graph -------------------------------------------------------------------- */

class Graph {
  friend class Algorithms;
  private:
    /* Variables */
    std::vector<std::vector<std::pair<unsigned long, double>>> list;
    std::vector<std::vector<double>> matrix;
    unsigned long num_edges;
    unsigned long num_vertices;
    bool has_positive_weights;
    
    /* Private Member Functions */
    void construct_list();
    void construct_matrix();
    template<typename Container>
    void copy_rep(Container container, std::pair<unsigned long, double> unused);
    template<typename Container>
    void copy_rep(Container container, double unused);
    std::vector<std::pair<unsigned long, double>>& get_neighbors(unsigned long
      row);

  public:
    /* Constructors */
    template<typename Container>
    Graph(Container container);
    Graph(const Graph& g);

    /* Public Member Functions */
    unsigned long get_num_edges();
    unsigned long get_num_vertices();
    double get_weight(unsigned long row, unsigned long col);
    bool has_negative_weights();

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

// copy_rep (list)
template<typename Container>
void Graph::copy_rep(Container container, std::pair<unsigned long,
double> unused) {
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
      }
      if(has_positive_weights && e.second < 0) {
        has_positive_weights = false;
      }
      ++num_edges;
    }
  }
  construct_matrix();
}

// copy_rep (matrix)
template<typename Container>
void Graph::copy_rep(Container container, double unused) {
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
      } else if(has_positive_weights && e < 0) {
        has_positive_weights = false;
      }
    }
  }
  construct_list();
}

// get_neighbors
std::vector<std::pair<unsigned long, double>>& Graph::get_neighbors(unsigned
    long row) {
  if(row >= num_vertices) {
    throw Graph_Exception("get_neighbors out of range access\n");
  }
  return list[row];
}

/* Constructors ------------------------------------------------------------- */

// Constructor
template<typename Container>
Graph::Graph(Container container) {
  has_positive_weights = true; // positive edges until otherwise;
  copy_rep(container, *(container.begin()->begin()));
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

// get_weight
double Graph::get_weight(unsigned long row, unsigned long col) {
  if(row >= num_vertices || col >= num_vertices) {
    throw Graph_Exception("get_weight out of range access\n");
  }
  return matrix[row][col];
}

// has_negative_weights
bool Graph::has_negative_weights() {
  return !has_positive_weights;
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
