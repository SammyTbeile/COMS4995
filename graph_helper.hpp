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

template<typename Node>
class Graph_Helper {
  private:
    /* Variables */
    std::vector<std::vector<std::pair<unsigned long, double>>> list;
    std::vector<std::vector<double>> matrix;
    std::vector<Node> vertex_node_vector;
    std::unordered_map<Node, unsigned long> node_vertex_map;
    graph_t graph;
    unsigned long index;

    /* Private Member Functions */
    void try_add_node(Node n);

  public:
    /* Constructors */
    Graph_Helper(graph_t g);
    Graph_Helper(const Graph_Helper& gh);

    /* Public Member Functions */
    void add_edge(Node origin, Node destin, double dist);
    std::tuple<std::vector<std::vector<double>>,
      std::vector<Node>> get_adjacency_matrix_associative_vector_tuple();
    std::tuple<std::vector<std::vector<std::pair<unsigned long, double>>>,
      std::vector<Node>> get_adjacency_list_associative_vector_tuple();

    /* Operators */
    Graph_Helper& operator=(const Graph_Helper& gh);
};

/* Private Member Functions ------------------------------------------------- */

// try_add_node
template<typename Node>
void Graph_Helper<Node>::try_add_node(Node n) {
  try {
    node_vertex_map.at(n);
  } catch(std::out_of_range& e) {
    node_vertex_map[n] = index++;
    vertex_node_vector.push_back(n);
    if(graph == LIST) {
      list.push_back(std::vector<std::pair<unsigned long, double>>());
    } else if(graph == MATRIX) {
      matrix.push_back(std::vector<double>());
    } else {
      throw Graph_Helper_Exception("Undefined representation\n");
    }
  }
}

/* Constructors ------------------------------------------------------------- */

// Constructor
template<typename Node>
Graph_Helper<Node>::Graph_Helper(graph_t g) {
  if(g == LIST) {
    list = std::vector<std::vector<std::pair<unsigned long, double>>>();
  } else if(g == MATRIX) {
    matrix = std::vector<std::vector<double>>();
  } else {
    throw Graph_Helper_Exception("Undefined representation\n");
  }
  vertex_node_vector = std::vector<Node>();
  node_vertex_map = std::unordered_map<Node, unsigned long>();
  index = 0;
  graph = g;
}

// Copy Constructor
template<typename Node>
Graph_Helper<Node>::Graph_Helper(const Graph_Helper& gh) {
  if(gh.graph == LIST) {
    list = gh.list;
  } else if(gh.graph == MATRIX) {
    matrix = gh.matrix;
  } else {
    throw Graph_Helper_Exception("Undefined representation\n");
  }
  vertex_node_vector = gh.vertex_node_vector;
  node_vertex_map = gh.node_vertex_map;
  index = gh.index;
  graph = gh.graph;
}

/* Public Member Functions -------------------------------------------------- */

// add_edge
template<typename Node>
void Graph_Helper<Node>::add_edge(Node origin, Node destin, double dist) {
  try_add_node(origin);
  try_add_node(destin);
  unsigned long origin_vertex = node_vertex_map[origin];
  unsigned long destin_vertex = node_vertex_map[destin];
  if(graph == LIST) {
    list[origin_vertex].push_back(std::make_pair(destin_vertex, dist));
  } else if(graph == MATRIX) {
    if(matrix[origin_vertex].size() <= destin_vertex) {
      matrix[origin_vertex].resize(destin_vertex + 1);
    }
    matrix[origin_vertex][destin_vertex] = dist;
  }
}

// get_adjacency_matrix_associative_vector_tuple
template<typename Node>
std::tuple<std::vector<std::vector<double>>, std::vector<Node>>
Graph_Helper<Node>::get_adjacency_matrix_associative_vector_tuple() {
  unsigned long num_vertices = matrix.size();
  for(unsigned long i = 0; i < num_vertices; ++i) {
    if(matrix[i].size() < num_vertices) {
      matrix[i].resize(num_vertices);
    } else if(matrix[i].size() > num_vertices) {
      throw Graph_Helper_Exception("Internal Error");
    }
  }
  return std::make_tuple(matrix, vertex_node_vector);
}

// get_adjacency_list_associative_vector_tuple
template<typename Node>
std::tuple<std::vector<std::vector<std::pair<unsigned long, double>>>, std::vector<Node>>
Graph_Helper<Node>::get_adjacency_list_associative_vector_tuple() {
  return std::make_tuple(list, vertex_node_vector);
}

/* Operators ---------------------------------------------------------------- */

// =
template<typename Node>
Graph_Helper<Node>& Graph_Helper<Node>::operator=(const Graph_Helper& gh) {
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
  vertex_node_vector = gh.vertex_node_vector;
  node_vertex_map = gh.node_vertex_map;
  index = gh.index;
  graph = gh.graph;
  return *this;
}

#endif
