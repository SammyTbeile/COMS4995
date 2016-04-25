/*
 * Filename: algorithms.cpp
 * Authors:  Sean Garvey, Minh Truong, Sammy Tbeile
 * UNIs:     sjg2174,     mt3077,      st2918
 */

#include <algorithm>
#include <limits>
#include <stack>
#include <vector>
#include <iostream>
#include <queue>
#include <functional>

#include "algorithms.hpp"
#include "graph.hpp"

// validate_start_vertex
void Algorithms::validate_start_vertex(Graph graph, unsigned long
start_vertex) {
  if(start_vertex >= graph.get_num_vertices()) {
    throw Algorithms_Exception("Starting vertex is out of range");
  }
}

// associate_vertex_node
/*
template<typename Node>
std::vector<std::pair<Node, double>> associate_vertex_node(std::vector<
std::pair<unsigned long, double>> path, std::vector<Node> associative_vector) {
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
}*/

class CompareDist
{
public:
    bool operator()(std::pair<double,unsigned long> n1,std::pair<double,unsigned long> n2) {
        return n1.first>n2.first;
    }
};

// Dijkstras
std::vector<std::pair<unsigned long, double>> Algorithms::Dijkstras(Graph
graph, unsigned long start_vertex, unsigned long end_vertex) {

  validate_start_vertex(graph, start_vertex);
	int num = graph.get_num_vertices();
  std::vector<double> distance = std::vector<double>(num);
  std::vector<unsigned long> predecessor = std::vector<unsigned long>(num);
	std::vector<bool> visited = std::vector<bool>(num);
  //initalize values
  for(int i = 0; i< num; i++) {
    distance[i] = std::numeric_limits<double>::infinity();
    predecessor[i] = 0; 
		visited[i] = false;
  }
	distance[start_vertex] = 0;

	using pdl = std::pair<double,unsigned long>;
	std::priority_queue<pdl,std::vector<pdl>,CompareDist> que;
	que.push(std::pair<double,unsigned long>(0,start_vertex));
	while(!que.empty()){
		std::pair<double,unsigned long> temp = que.top();
		que.pop();

		if(!visited[temp.second]){
			visited[temp.second] = true;
			for(auto& pair: graph.list[temp.second]){
			
				if(visited[pair.first]== false){
					if(temp.first + pair.second < distance[pair.first]){
						distance[pair.first] = distance[temp.second] + pair.second;
						predecessor[pair.first] = temp.second;

						que.push(std::pair<double,unsigned long>(distance[pair.first],pair.first));
					}
				}	
			}
		}
	}

	std::vector<std::pair<unsigned long, double>> path;
  unsigned long current = end_vertex;
  path.push_back(std::pair<unsigned long, double>(current, distance[current]));
	auto visited_check = std::vector<bool>(num); //make sure this is correct
	visited_check[current] = true;
  do {
    current = predecessor[current];
		if(visited_check[current] == true){
			 throw Algorithms_Exception("No Path");
		}
    auto newpair = std::pair<unsigned long, double>(current, distance[current]);
    path.push_back(newpair);
		visited_check[current] = true;
  } while(current != start_vertex);

  std::reverse(path.begin(), path.end());

	double track = 0;
	for(int i = 0 ; i < path.size(); i++){
		auto pair = path[i];
		auto editvalue = pair.second - track;
		track = pair.second;
		path[i] = std::pair<unsigned long, double>(pair.first,editvalue);
	}

  return path; // TODO remove
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
std::vector<unsigned long> Algorithms::Tarjan(Graph graph) {
/*	if(is_undirected(graph)==false){
		 throw Algorithms_Exception("Graph is not undirected");
	}*/

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
	
  auto points = std::vector<unsigned long>();

	if(tree[0].second.size()>1){
		points.push_back(0);
	}
  for(int i = 1; i< size; i++){
    for(auto& vert: tree[i].second){
      if(low[vert] >= tree[i].first){
        points.push_back(i);
        break;
      }
    }
  }
  return points;
}

bool Algorithms::is_undirected(Graph graph){
	for(int i = 0; i< graph.get_num_vertices(); i++){
		for(int j = 0; j< graph.get_num_vertices(); j++){
			if(graph.matrix[i][j] != graph.matrix[j][i]){
				return false;
			}
		}
	}
	return true;
}/*

static std::vector<std::pair<unsigned long, double>> 
traveling_salesman(Graph graph){
		return std::vector<std::pair<unsigned long, double>>();

}*/

std::vector<std::vector<std::vector<std::pair<unsigned long, double>>>>
 Algorithms::johnson(Graph graph){
	auto graphx = std::vector<std::vector<std::pair<unsigned long, double>>>();
	auto num = graph.get_num_vertices();
	auto vert = std::vector<std::pair<unsigned long, double>>();
	for(auto& lis: graph.list){
		graphx.push_back(lis);
	}
	for(int i = 0; i< num; i++){
		vert.push_back(std::pair<unsigned long, double>(i,0));
	}
	graphx.push_back(vert);
	
	auto tempg = Graph(graphx);
	unsigned long start_vertex = num;

	num = num + 1;
  std::vector<double> distance = std::vector<double>(num);
  std::vector<unsigned long> predecessor = std::vector<unsigned long>(num);
  //initalize values
  for(int i = 0; i< num; i++) {
    distance[i] = std::numeric_limits<double>::infinity();
    predecessor[i] = 0; // 
		
		}

  distance[start_vertex] = 0;
  //compute optimal path
  for(int index = 0; index < num; index++) {
    for(int i = 0; i< num; i++) {
    std::vector<std::pair<unsigned long, double>> row = tempg.list[i]; 
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
    std::vector<std::pair<unsigned long, double>> rows = tempg.list[i];
    for(auto& pairs: rows) {
      if(distance[i] + pairs.second < distance[pairs.first]) {
        throw Algorithms_Exception("Contains Negative Cycles");
      }
    }
  }

	auto h = std::vector<double>(num);
	//compute h[] distances
	h[num-1] = 0;
	for(int i = 0 ; i < num-1 ; i++){
		std::vector<std::pair<unsigned long, double>> path;
  	unsigned long current = i;
  	path.push_back(std::pair<unsigned long, double>(current, distance[current]));
  	do {
    	current = predecessor[current];
    	auto newpair = std::pair<unsigned long, double>(current, distance[current]);
    	path.push_back(newpair);
  	} while(current != num-1);

  	std::reverse(path.begin(), path.end());

		double total = 0;
		for(auto& edge: path){
			total += edge.second;
		}
		h[i] = total;
	}

	auto newgraph = graph.list;
	for(int i = 0 ; i< newgraph.size(); i++){
		auto temp = newgraph[i];
	//	std::vector<std::pair<unsigned long, double>>
		auto z = std::vector<std::pair<unsigned long, double>>(); 
		for(int j = 0; j < temp.size(); j++){
			std::pair<unsigned long, double> temppair = temp[j];
			double value = (temppair.second + h[i] - h[temppair.first]);
			z.push_back(std::pair<unsigned long, double>(temppair.first,value));
		}
		newgraph[i] = z;
	}

	auto xyz = Graph(newgraph);
	auto length = xyz.get_num_vertices();
	auto final_weight = std::vector<std::vector<std::vector<std::pair<unsigned long, double>>
>>(length);
	for(int i = 0; i < length ; i++){
		final_weight[i] = std::vector<std::vector<std::pair<unsigned long, double>>>(length);
	}
	
	for(int i = 0; i< length; i++){
		for(int j = 0 ; j< length; j++){
			final_weight[i][j] = Dijkstras(xyz,i,j);
		}
	}

	return final_weight;


}
