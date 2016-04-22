/*
 * Filename: algorithms.cpp
 * Authors:  Sean Garvey, Sammy Tbeile
 * UNIs:     sjg2174,     st2918
 */

#include <algorithm>
#include <limits>
#include <vector>
#include <stack>
#include <iostream>
#include <queue>

#include "algorithms.hpp"

// validate_start_vertex
void Algorithms::validate_start_vertex(Graph graph, unsigned long
start_vertex) {
  if(start_vertex >= graph.get_num_vertices()) {
    throw Algorithms_Exception("Starting vertex is out of range");
  }
}

/*
// associate_vertex_node
template<typename Node, typename Container>
std::vector<std::pair<Node, double>> associate_vertex_node(std::vector<
std::pair<unsigned long, double>> path, Container associative_vector) {
  auto mapped_vector = std::vector<std::pair<Node, double>>();
  mapped_vector.reserve(path.size());
  for(auto& long_double_pair : path) {
    try {
      mapped_vector.push_back(std::make_pair(associative_vector.at(
        long_double_pair.first).first, long_double_pair.second);
    } catch(std::out_of_range& e) {
      throw Algorithm_Exception("Vertex not found in associative vector");
    }
  }
  return mapped_vector;
}
*/
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

// BellFord
std::vector<std::pair<unsigned long, double>> Algorithms::BellFord(Graph graph,
unsigned long start_vertex, unsigned long end_vertex) {
  validate_start_vertex(graph, start_vertex);
  
  int num = graph.get_num_vertices();
  std::vector<double> distance = std::vector<double>(num);
  std::vector<unsigned long> predecessor = std::vector<unsigned long>(num);
  //initalize values
  for(int i = 0; i< num; i++) {
    distance[i] = std::numeric_limits<double>::infinity();
    predecessor[i] = 0; // TODO: vertify 0 is correct, as NULL was giving a compiler error
  }
  distance[start_vertex] = 0;
  //compute optimal path
  for(int index = 0; index < num; index++) {
    for(int i = 0; i< num; i++) {
    std::vector<std::pair<unsigned long, double>> row = graph.list[i]; 
      for(auto& pair: row) {
        if(distance[i] + pair.second < distance[pair.first]) {
          distance[pair.first] = distance[index] + pair.second;
          predecessor[pair.first] = i;
        }
      }
    }
  }
  //check for negative cycles
  for(int i = 0; i < num; i++){
    std::vector<std::pair<unsigned long, double>> rows = graph.list[i];
    for(auto& pairs: rows) {
      if(distance[i] + pairs.second < distance[pairs.first]) {
        throw Algorithms_Exception("Contains Negative Cycles");
      }
    }
  }
  //construct path
  std::vector<std::pair<unsigned long, double>> path;
  unsigned long current = end_vertex;
  path.push_back(std::pair<unsigned long, double>(current, distance[current]));
  do {
    current = predecessor[current];
    auto newpair = std::pair<unsigned long, double>(current, distance[current]);
    path.push_back(newpair);
  } while(current != start_vertex);

  std::reverse(path.begin(), path.end());

  return path;
}
/*
// Bellford, map
template<typename Node, typename Container>
std::vector<std::pair<Node, double>> Algorithms::BellFord(Graph& graph,
unsigned long start_vertex, unsigned long end_vertex, Container container) {
  Node n = container[0].first;
  return associate_vertex_node(BellFord(graph, start_vertex, end_vertex),
    container);
}
*/

// dfs
void Algorithms::dfs(Graph& graph, int& count, unsigned long vertex, std::
vector<bool>& visited, std::vector<std::pair<unsigned long, std::vector<unsigned
long>>>& tree, std::vector<std::vector<unsigned long>>& backedge) {
  visited[vertex] = true;
  auto temp = std::pair<unsigned long,std::vector<unsigned long>>(count,
    std::vector<unsigned long>());

  tree[vertex] = temp;
  auto neighbors = graph.get_neighbors(vertex);
  for(auto& pair: neighbors) {
    if(!visited[pair.first]) {	
      auto p = tree[vertex];
      auto list = p.second;
      list.push_back(pair.first);
      tree[vertex] = std::pair<unsigned long,std::vector<unsigned long>>(p.first,list);
      count++;
      dfs(graph, count,pair.first, visited, tree, backedge);
    } else if(tree[vertex].first > tree[pair.first].first) {
      auto back = backedge[vertex];
      back.push_back(pair.first);
      backedge[vertex] = back;
    }
  }
}

// lo
unsigned long Algorithms::lo(unsigned long vertex, std::vector<std::pair<
unsigned long, std::vector<unsigned long>>> tree, std::vector<std::vector<
unsigned long>> backedge) {
  auto value = std::numeric_limits<double>::infinity();
  auto que = std::queue<unsigned long>();
  auto visited = std::vector<bool>(tree.size());
  visited[vertex] = true;
  que.push(vertex);
  //bool back = false; // TODO commented out because compiler said it was unused
  while(!que.empty()) {
    unsigned long vert = que.front();
    que.pop();
    if(tree[vert].first < value) {
      value = tree[vert].first;
    }
    for(auto& edge : tree[vert].second) {
      if(!visited[edge]) {
        visited[edge] = true;
        que.push(edge);
      }
    }
    for(auto& edge: backedge[vert]) {
      if(tree[edge].first < value) {
        value = tree[edge].first;
      }
    }
  }
  return (unsigned long) value;
}
	
// Tarjan
std::vector<std::pair<unsigned long, unsigned long>> Algorithms::Tarjan(
Graph graph) {
  int size = graph.get_num_vertices();
  auto visited = std::vector<bool>(size);
  auto tree = std::vector<std::pair<unsigned long,std::vector<unsigned long>>>
    (size);
  auto backedge = std::vector<std::vector<unsigned long>>(size);

  int count = 0;
  dfs(graph, count, 0, visited, tree, backedge);
  auto low = std::vector<unsigned long>(size);

  low[0] = 0;
  for(int i = 1; i < size; i++) {
    low[i] = lo(i, tree, backedge);
  }

  for(auto& x: tree) {
    std::cout << x.first << std::endl;
  }
  std::cout << " " << std::endl;

  for(auto& x: low) {
    std::cout << x << std::endl;
  }/*

  auto points = std::vector<unsigned long>();
  for(int i = 1; i< size; i++){
    for(auto& vert: tree[i].second){
      if(low[vert] >= tree[i].first){
        points.push_back(i);
        break;
      }
    }
  }

  for(auto& x: points){
    std::cout << x << std::endl;
  }*/
  return std::vector<std::pair<unsigned long, unsigned long>>();
}
