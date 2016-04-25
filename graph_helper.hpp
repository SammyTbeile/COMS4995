#ifndef __GRAPH_HELPER_HPP__
#define __GRAPH_HELPER_HPP__
/*
 * Filename: graph_helper.hpp
 * Author:   Sean Garvey
 * UNI:      sjg2174
 */

#include <exception>
#include <vector>
#include <unordered_map>

/* Graph_Helper_Enum -------------------------------------------------------- */
enum graph_t { LIST, MATRIX };

/* Graph_Helper_Exception --------------------------------------------------- */

class Graph_Helper_Exception : public std::exception {
private:
  const char* message;
public:
  Graph_Helper_Exception(const char* msg) { message = msg; }
  virtual const char* what() const throw() { return message; }
};

/* Graph_Helper ------------------------------------------------------------- */

template<typename Vertex>
class Graph_Helper {
  private:
    /* Variables */
    std::vector<std::vector<std::pair<unsigned long, double>>> list;
    std::vector<std::vector<double>> matrix;
    std::vector<Vertex> index_vertex_vector;
    std::unordered_map<Vertex, unsigned long> vertex_index_map;
    graph_t graph;
    unsigned long index;

    /* Private Member Functions */
    void try_add_vertex(Vertex n);

  public:
    /* Constructors */
    Graph_Helper(graph_t g);
    Graph_Helper(const Graph_Helper& gh);

    /* Public Member Functions */
    void add_edge(Vertex origin, Vertex destin, double dist);

    std::tuple<std::vector<std::vector<double>>, std::vector<Vertex>, std::
    unordered_map<Vertex, unsigned long>> get_matrix_tuple();

    std::tuple<std::vector<std::vector<std::pair<unsigned long, double>>>,
    std::vector<Vertex>, std::unordered_map<Vertex, unsigned long>> get_list_tuple();

    /* Operators */
    Graph_Helper& operator=(const Graph_Helper& gh);
};

/* Private Member Functions ------------------------------------------------- */

// try_add_vertex
template<typename Vertex>
void Graph_Helper<Vertex>::try_add_vertex(Vertex n) {
  try {
    vertex_index_map.at(n);
  } catch(std::out_of_range& e) {
    vertex_index_map[n] = index++;
    index_vertex_vector.push_back(n);
    switch(graph) {
      case LIST:
        list.push_back(std::vector<std::pair<unsigned long, double>>());
        break;
      case MATRIX:
        matrix.push_back(std::vector<double>());
        break;
      default:
        throw Graph_Helper_Exception("Undefined representation\n");
        break;
    }
  }
}

/* Constructors ------------------------------------------------------------- */

// Constructor
template<typename Vertex>
Graph_Helper<Vertex>::Graph_Helper(graph_t g) {
  if(g == LIST) {
    list = std::vector<std::vector<std::pair<unsigned long, double>>>();
  } else if(g == MATRIX) {
    matrix = std::vector<std::vector<double>>();
  } else {
    throw Graph_Helper_Exception("Undefined representation\n");
  }
  index_vertex_vector = std::vector<Vertex>();
  vertex_index_map = std::unordered_map<Vertex, unsigned long>();
  index = 0;
  graph = g;
}

// Copy Constructor
template<typename Vertex>
Graph_Helper<Vertex>::Graph_Helper(const Graph_Helper& gh) {
  if(gh.graph == LIST) {
    list = gh.list;
  } else if(gh.graph == MATRIX) {
    matrix = gh.matrix;
  } else {
    throw Graph_Helper_Exception("Undefined representation\n");
  }
  index_vertex_vector = gh.index_vertex_vector;
  vertex_index_map = gh.vertex_index_map;
  index = gh.index;
  graph = gh.graph;
}

/* Public Member Functions -------------------------------------------------- */

// add_edge
template<typename Vertex>
void Graph_Helper<Vertex>::add_edge(Vertex origin, Vertex destin, double dist) {
  try_add_vertex(origin);
  try_add_vertex(destin);
  unsigned long origin_index = vertex_index_map[origin];
  unsigned long destin_index = vertex_index_map[destin];
  if(graph == LIST) {
    list[origin_index].push_back(std::make_pair(destin_index, dist));
  } else if(graph == MATRIX) {
    if(matrix[origin_index].size() <= destin_index) {
      matrix[origin_index].resize(destin_index + 1);
    }
    matrix[origin_index][destin_index] = dist;
  }
}

// get_matrix_tuple
template<typename Vertex>
std::tuple<std::vector<std::vector<double>>, std::vector<Vertex>, std::
unordered_map<Vertex, unsigned long>> Graph_Helper<Vertex>::get_matrix_tuple() {
  unsigned long num_vertices = matrix.size();
  for(unsigned long i = 0; i < num_vertices; ++i) {
    if(matrix[i].size() < num_vertices) {
      matrix[i].resize(num_vertices);
    } else if(matrix[i].size() > num_vertices) {
      throw Graph_Helper_Exception("Internal Error");
    }
  }
  return std::make_tuple(matrix, index_vertex_vector, vertex_index_map);
}

// get_list_tuple
template<typename Vertex>
std::tuple<std::vector<std::vector<std::pair<unsigned long, double>>>,
std::vector<Vertex>, std::unordered_map<Vertex, unsigned long>>
Graph_Helper<Vertex>::get_list_tuple() {
  return std::make_tuple(list, index_vertex_vector, vertex_index_map);
}

/* Operators ---------------------------------------------------------------- */

// =
template<typename Vertex>
Graph_Helper<Vertex>& Graph_Helper<Vertex>::operator=(const Graph_Helper& gh) {
  if(this == &gh) {
    return *this;
  }
  if(gh.graph == LIST) {
    list = gh.list;
  } else if(gh.graph == MATRIX) {
    matrix = gh.matrix;
  } else {
    throw Graph_Helper_Exception("Undefined representation\n");
  }
  index_vertex_vector = gh.index_vertex_vector;
  vertex_index_map = gh.vertex_index_map;
  index = gh.index;
  graph = gh.graph;
  return *this;
}

#endif
