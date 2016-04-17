/*
 * Filename: algorithms.cpp
 * Authors:  Sean Garvey, Sammy Tbeile
 * UNIs:     sjg2174,     st2918
 */
#include "algorithms.hpp"
#include "algorithms_exception.hpp"

// validate_start_vertex
void Algorithms::validate_start_vertex(Graph graph, unsigned long
start_vertex) {
  if(start_vertex >= graph.get_num_vertices()) {
    throw Algorithms_Exception("Starting vertex is out of range");
  }
}

// Dijkstras
std::vector<std::pair<unsigned long, unsigned long>> Algorithms::Dijkstras(Graph
graph, unsigned long start_vertex) {
  validate_start_vertex(graph, start_vertex);
  return std::vector<std::pair<unsigned long, unsigned long>>(); // TODO remove
}

// Prim's
std::vector<std::pair<unsigned long, unsigned long>> Algorithms::Prims(Graph
graph, unsigned long start_vertex) {
  validate_start_vertex(graph, start_vertex);
  /*
  // Commenting this out so I can compile the algorithms header

  auto starting_vertex = start_pair.first;
  //Set the starting vertex as visited
  am.set_visited(pair.first, pair.second);
  //get its neighbors
  auto neighbors_list = am.get_neighbors(start_pair.first);
  int minWeightSoFar = neighbors_list[0];
  while(!neighbors_list.empty) {
    for( auto neighbor : neighbors_list) {
      if (am.get_weight(neighbor) <am.get_weight(minWeightSoFar));
        minWeightSoFar = neighbor;
    }
  }
  */
  return std::vector<std::pair<unsigned long, unsigned long>>(); // TODO remove
}
