#ifndef __ALGORITHMS_HPP__
#define __ALGORITHMS_HPP__
/*
 * Filename: algorithms.hpp
 * Authors:  Sean Garvey, Minh Truong, Sammy Tbeile
 * UNIs:     sjg2174,     mt3077,      st2918
 */

#include <algorithm>
#include <exception>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

#include "graph.hpp"

/* Algorithms_Exception ----------------------------------------------------- */

class Algorithms_Exception : public std::exception {
private:
  const char* message;
public:
  Algorithms_Exception(const char* msg) { message = msg; }
  virtual const char* what() const throw() { return message; }
};

/* Algorithms --------------------------------------------------------------- */

class Algorithms {
  private:
    /* Private Member Functions */
    static void validate_start_vertex(Graph graph, unsigned long start_vertex);

		static void dfs(Graph& graph, int& count, unsigned long vertex,
      std::vector<bool>& visited, std::vector<std::pair<unsigned long,
      std::vector<unsigned long>>>& tree,
      std::vector<std::vector<unsigned long>>& backedge);

    static unsigned long lo(unsigned long vertex, 
      std::vector<std::pair<unsigned long,std::vector<unsigned long>>> tree, 
      std::vector<std::vector<unsigned long>> backedge);

  public:
    /* Public Member Functions */
    static std::vector<std::pair<unsigned long, double>>
      Dijkstras(Graph graph, unsigned long start_vertex, unsigned long end_vertex);
    static std::vector<std::pair<unsigned long, double>>
      Prims(Graph graph, unsigned long start_vertex);

		static std::vector<std::pair<unsigned long, double>> BellFord(Graph graph, unsigned long start_vertex, unsigned long end_vertex);

			static std::vector<unsigned long> Tarjan(Graph graph);	
/*
		static std::vector<std::pair<unsigned long, double>> 
			traveling_salesman(Graph graph);*/

		static bool is_undirected(Graph graph);

		static std::vector<std::vector<std::vector<std::pair<unsigned long, double>>>>
 Johnsons(Graph graph);

};



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
    predecessor[i] = -1; 
		visited[i] = false;
  }
	distance[start_vertex] = 0;

	using pdl = std::pair<double,unsigned long>;
	std::priority_queue<pdl,std::vector<pdl>,CompareDist> que;
	que.push(std::pair<double,unsigned long>(0,start_vertex));

	//compute optimal path
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

	if(predecessor[end_vertex] == -1){
		throw Algorithms_Exception("No Path");
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
=======
  int num = graph.get_num_vertices();
  std::vector<unsigned long> parents = std::vector<unsigned long>(num); //store MST
  std::vector<double> keys = std::vector<double>(num) ; //store minWeights
  std::vector<bool> mstVector = std::vector<bool>(num);  //represent vertexes not yet in the MST

  //initalize values
  for(int i=0;i<num;i++){
    keys[i] = std::numeric_limits<double>::infinity();
    mstVector[i] = false;
  }

  keys[0] = 0;
  parents[0] = start_vertex;

  for(int index =0; index<num-1;index++){
    //get the minimum key
    double min = std::numeric_limits<double>::infinity();
    int minIndex;
    for(int i=0;i< num;i++){
      if(mstVector[i] ==false && keys[i] < min){
        min = keys[i];
        minIndex = i;
      }
    }

    //add the min to the MST
    mstVector[minIndex] = true;

    //update key and parent of adjacent vertexes not included in the MST
    for(int j = 0; j< num;j++){

      //graph.matrix[minIndex][j] is not zero only for adjacent vertexes of minIndex
      //mstVector is false only for vertexes not yet in the MST
      if(graph.matrix[minIndex][j] !=0 && mstVector[j] ==false && graph.matrix[minIndex][j] < keys[j]){
        parents[j] = minIndex;
        keys[j] = graph.matrix[minIndex][j];
      }
    }
  }

  //print the tree
  std::vector<std::list<std::pair<unsigned long, double>>> returnVector;
  for( unsigned long i=0;i< num;i++){
    std::list<std::pair<unsigned long, double>> innerList;
    auto newpair = std::pair<unsigned long, double>(i,keys[i]);
    innerList.push_back(newpair);
    //auto current = i;
    for(auto j = 1; j< num; j++){
      if(parents[j] == newpair.first){
        innerList.push_back(std::pair<unsigned long, double>(j, keys[j]));
      }
>>>>>>> 2170e8545ba12855ee904d3686d93039afa04da9
    }
    returnVector.push_back(innerList);
  }
<<<<<<< HEAD
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
  for(int i = 1; i< num; i++) {
    distance[i] = std::numeric_limits<double>::infinity();
    predecessor[i] = -1; 
  }
  distance[start_vertex] = 0;

  //compute optimal path
  for(int index = 0; index < num; index++) {
    for(int i = 0; i< num; i++) {
    	std::vector<std::pair<unsigned long, double>> row = graph.list[i]; 
      for(auto& pair: row) {
        if(distance[i] + pair.second < distance[pair.first]) {
          distance[pair.first] = distance[i] + pair.second;
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

	if(predecessor[end_vertex] == -1){
		throw Algorithms_Exception("NOO PATH");
	}

  //construct path
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

  return path;
}
// dfs - create spaning tree for bellmanford
>>>>>>> 2170e8545ba12855ee904d3686d93039afa04da9
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

// lo - compute low numbers for BellmanFord
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
	if(is_undirected(graph)==false){
		 throw Algorithms_Exception("Graph is not undirected");
	}

	//initlize values
  int size = graph.get_num_vertices();
  auto visited = std::vector<bool>(size);
  auto tree = std::vector<std::pair<unsigned long,std::vector<unsigned long>>>(size);
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
}

std::vector<std::vector<std::vector<std::pair<unsigned long, double>>>>
 Algorithms::Johnsons(Graph graph){
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
          distance[pair.first] = distance[i] + pair.second;
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

	//construct graph with with new weights
	auto newgraph = graph.list;
	for(int i = 0 ; i< newgraph.size(); i++){
		auto temp = newgraph[i];
		auto newedges = std::vector<std::pair<unsigned long, double>>(); 
		for(int j = 0; j < temp.size(); j++){
			std::pair<unsigned long, double> temppair = temp[j];
			double value = (temppair.second + h[i] - h[temppair.first]);
			newedges.push_back(std::pair<unsigned long, double>(temppair.first,value));
		}
		newgraph[i] = newedges;
	}

	auto finalgraph = Graph(newgraph);
	auto length = finalgraph.get_num_vertices();
	auto final_weight = std::vector<std::vector<std::vector<std::pair<unsigned long, double>>
>>(length);
	for(int i = 0; i < length ; i++){
		final_weight[i] = std::vector<std::vector<std::pair<unsigned long, double>>>(length);
	}

	//compute paths between all nodes
	for(int i = 0; i< length; i++){
		for(int j = 0 ; j< length; j++){
			if(i == j){
				auto tem = std::vector<std::pair<unsigned long, double>>();
				tem.push_back(std::pair<unsigned long, double>(0,0));
				final_weight[i][j] = tem;
			}else if(i>j){
				final_weight[i][j] = final_weight[j][i];
			}else{
				try{
					final_weight[i][j] = Dijkstras(finalgraph,i,j);
				}catch(Algorithms_Exception){
					final_weight[i][j] = std::vector<std::pair<unsigned long, double>>();
				}
			}
		}
	}

	return final_weight;
}
#endif
