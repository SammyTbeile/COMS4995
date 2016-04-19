/*
 * Filename: algorithms.cpp
 * Authors:  Sean Garvey, Sammy Tbeile
 * UNIs:     sjg2174,     st2918
 */

#include <algorithm>
#include <limits>
#include <vector>

#include "algorithms.hpp"

// validate_start_vertex
void Algorithms::validate_start_vertex(Graph graph, unsigned long
start_vertex) {
  if(start_vertex >= graph.get_num_vertices()) {
    throw Algorithms_Exception("Starting vertex is out of range");
  }
}

// Dijkstras
std::vector<std::pair<unsigned long, double>> Algorithms::Dijkstras(Graph
graph, unsigned long start_vertex) {
  validate_start_vertex(graph, start_vertex);
  return std::vector<std::pair<unsigned long, double>>(); // TODO remove
}

// Prim's
std::vector<std::pair<unsigned long, double>> Algorithms::Prims(Graph
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
  return std::vector<std::pair<unsigned long, double>>(); // TODO remove
}
	std::vector<std::pair<unsigned long, double>> Algorithms::BellFord(Graph graph,
	unsigned long start_vertex, unsigned long end_vertex){
		validate_start_vertex(graph, start_vertex);
		
		int num = graph.get_num_vertices();
		std::vector<double> distance = std::vector<double>(num);
		std::vector<unsigned long> predecessor = std::vector<unsigned long>(num);
		
		//initalize values
		for(int i = 0; i< num; i++){
			distance[i] = std::numeric_limits<double>::infinity();
			predecessor[i] = 0; // TODO, NULL was giving a compiler error
		}
		distance[start_vertex] = 0;

		//compute optimal path
		for(int index = 0; index < num; index++){
			for(int i = 0; i< num; i++){
			std::vector<std::pair<unsigned long, double>> row = graph.list[i]; 
				for(auto& pair: row){
					if(distance[i] + pair.second < distance[pair.first]){
						distance[pair.first] = distance[index] + pair.second;
						predecessor[pair.first] = i;
					}
				}
			}
		}
		//check for negative cycles
		for(int i = 0; i < num; i++){
			std::vector<std::pair<unsigned long, double>> rows = graph.list[i];
			for(auto& pairs: rows){
				if(distance[i] + pairs.second < distance[pairs.first]){
					throw Algorithms_Exception("Contains Negative Cycles");
			}
		}
	}
	
	//construct path
	std::vector<std::pair<unsigned long, double>> path;
	unsigned long current = end_vertex;
	do{
		std::pair<unsigned long, double> newpair = std::pair<unsigned long, double>(current, distance[current]);
		path.push_back(newpair);
		current = predecessor[current];
	}while(current != start_vertex);

	std::reverse(path.begin(), path.end());
	return path;

}
