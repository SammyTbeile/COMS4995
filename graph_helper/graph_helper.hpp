#ifndef __GRAPH_HELPER_HPP__
#define __GRAPH_HELPER_HPP__
/*
 * Filename: graph_helper.hpp
 * Author:   Sean Garvey
 * UNI:      sjg2174
 */

#include <vector>
#include <unordered_map>
#include "graph.hpp"
#include "graph_helper_exception.hpp"

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
      std::vector<std::pair<unsigned long, Node>>> get_matrix_tuple();
    std::tuple<std::vector<std::vector<std::pair<unsigned long, double>>>,
      std::vector<std::pair<unsigned long, Node>>> get_list_tuple();

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
      matrix.push_back(std::vector<std::vector<double>>());
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

// get_matrix_tuple
template<typename Node>
std::tuple<std::vector<std::vector<double>>,
  std::vector<std::pair<unsigned long, Node>>>
  Graph_Helper<Node>::get_matrix_tuple() {
    return std::make_tuple(matrix, vertex_node_vector);
}

// get_list_tuple
template<typename Node>
std::tuple<std::vector<std::vector<std::pair<unsigned long, double>>>,
  std::vector<std::pair<unsigned long, Node>>>
  Graph_Helper<Node>::get_list_tuple() {
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
