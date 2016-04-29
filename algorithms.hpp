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
#include <iostream>

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
    static std::vector<std::vector<std::pair<unsigned long, double>>>
      Prims(Graph graph, unsigned long start_vertex);

		static std::vector<std::pair<unsigned long, double>> BellFord(Graph graph, unsigned long start_vertex, unsigned long end_vertex);

			static std::vector<unsigned long> Tarjans(Graph graph);	

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

/*
	Dijkstra's algorithm to find the shortest path between two vertices in a graph.
	Time complexity => O(|E| + |V|log|V|), this is asymtotically the fastest single
	source shortest-path finding algorithm. The algorithm cannot take graphs that
	have negative weights. 

	Dijkstras(Graph graph, start_vertex, end_vertex) = path = vector<pair<unsigned long, double>>

	path = { pair<v_0,w_0> , pair<v_1,w_1> ,..., pair<v_n,w_n> }. 

	the pairs of v_i and w_i represents the the vertex and weight along an edge in the path.

	v_0 is the starting vertex and v_n is the end vertex. the weights w_i, is the weight of 
	the edge from the previous vertex v_{i-1}	to the current vertex v_{i}. The total weight 
	of the path is the sum of w_1 to w_n. w_0 is always 0 since there is no vertex to going
	to the stating vertex.


*/
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
/*
	Prim’s algorithm to compute a minimum spanning tree from a starting vertex in a graph.
	
	Time complexity => O((|V| + |E|) log |V|) = O(|E| log |V|)
	
	The algorithm uses Dikjstra’s algorithm with the distance condition relaxed to dw= min(dw,cv,w)
	
	Prims(Graph graph, start_vertex)= returnVector=vector<list<pair<unsigned long, double>>>
	returnVector = <list<pair<v_0,w_0>,pair<v_1,w_1>,…,pair<v_n,w_n>>,list<pair<v_1,w_1>, pair<v_2,w_2>>> 
	
	Each list in the vector contains a list of pairs which represent a vertex and its adjacent vertices. 
	The pairs of v_i and w_i represent the vertex and the weight along an edge in the path leading to it. 
	The first pair is the starting vertex and the other ones are its connecting vertices.
	The weight is the weight from the previous vertex to the current vertex.
	
*/

// Prim's
std::vector<std::vector<std::pair<unsigned long, double>>> Algorithms::Prims(Graph
graph, unsigned long start_vertex) {
  validate_start_vertex(graph, start_vertex);
  //Initalize variables and containers
  int num = graph.get_num_vertices();
  std::vector<double> distances = std::vector<double>(num);
  std::vector<unsigned long> predecessor = std::vector<unsigned long>(num);
  std::vector<bool> known = std::vector<bool>(num);
  std::vector<unsigned long> vertices = std::vector<unsigned long>(num);

  //Initialize vertices for algorithms
  for(int i=0;i<num;i++){
    distances[i]=std::numeric_limits<double>::infinity();
    predecessor[i] = 0;
    known[i] = false;
  }

  // Get start value
  distances[start_vertex] = 0;
  std::priority_queue<std::pair<double,unsigned long>,std::vector<std::pair<double,unsigned long>>,CompareDist> queue;
  queue.push(std::pair<double,unsigned long>(0,start_vertex));
  //Perform Dijkstra's with the relaxed distance update
  while(!queue.empty()){
    //Get the smallest vertex
    std::pair<double,unsigned long> temp = queue.top();
    vertices.push_back(queue.top().first);
    queue.pop();

    //Check to make sure that the vertex hasn't already been declared known
    if(!known[temp.second]){
       known[temp.second]=true;
       for(auto& vertex : graph.list[temp.second]){
          if(!known[vertex.first]){
            if(vertex.second < distances[vertex.first]){
              distances[vertex.first] = vertex.second;
              predecessor[vertex.first] = temp.second;
              queue.push(std::pair<double,unsigned long>(distances[vertex.first],vertex.first));
            }
          }
       }
    }
  }
  
  //Construct the MST
  std::vector<std::vector<std::pair<unsigned long,double>>> returnVector = std::vector<std::vector<std::pair<unsigned long,double>>>();
  int counter = 0;
  std::vector<unsigned long> added = std::vector<unsigned long>();
  while(counter<200){
  std::vector<std::pair<unsigned long, double>> start_list = std::vector<std::pair<unsigned long, double>>();
  
  start_list.push_back(std::pair<unsigned long, double>(start_vertex,0));
  for(auto& vertex : graph.list[start_vertex]){
    if(predecessor[vertex.first] == start_vertex){
      start_list.push_back(std::pair<unsigned long, double>(vertex.first,distances[vertex.first]));
    }
  }
  added.push_back(start_vertex);
  returnVector.push_back(start_list);
  counter++;
  if(std::find(added.begin(), added.end(), vertices[start_vertex+1]) != added.end()) {
    //do nothing
  }else{
    start_vertex = vertices[start_vertex+1];
  }
}
    return returnVector; // TODO remove
}

/*
	BellFord, is an implementation of Bellman-Ford's algorithm.
	time complexity => O(|E|*|V|)
	Finds the shortest path between two vertices in a graph. Although this algorithm 
	is asymtotically slower than Dijkstras, this algorithm works for graphs 
	with negative weights. 

	BellFord(Graph graph, start_vertex, end_vertex) = path = vector<pair<unsigned long, double>>

	path = { pair<v_0,w_0> , pair<v_1,w_1> ,..., pair<v_n,w_n> }. 

	the pairs of v_i and w_i represents the the vertex and weight along an edge in the path.

	v_0 is the starting vertex and v_n is the end vertex. the weights w_i, is the weight of 
	the edge from the previous vertex v_{i-1}	to the current vertex v_{i}. The total weight 
	of the path is the sum of w_1 to w_n. w_0 is always 0 since there is no vertex to going
	to the stating vertex.

*/

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
    predecessor[i] = -1; 
  }
  distance[start_vertex] = 0;

  //compute optimal path
  for(int index = 1; index < num; index++) {
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

	double track = 0;
	for(int i = 0 ; i < path.size(); i++){
		auto pair = path[i];
		auto editvalue = pair.second - track;
		track = pair.second;
		path[i] = std::pair<unsigned long, double>(pair.first,editvalue);
	}

  return path;
}
// dfs - create spaning tree for bellmanford
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
	
/* 
		Tarjan's algorithm to find articulation points.
		Tarjans(Graph graph) = art_points = vector<unsigned long>

		The algorithm's time complexity is O(|V| + |E|)

		art_points = < v_0, v_1,..., v_n >

		all v_i's of art_points are articulation points of 'graph'.


*/

std::vector<unsigned long> Algorithms::Tarjans(Graph graph) {
	for(int i = 0; i< graph.get_num_vertices(); i++){
		for(int j = 0; j< graph.get_num_vertices(); j++){
			if(graph.matrix[i][j] != graph.matrix[j][i]){
				if(graph.matrix[i][j] == 0){
					graph.matrix[i][j] = graph.matrix[j][i];
				}else if (graph.matrix[j][i]==0){
					graph.matrix[j][i] = graph.matrix[i][j];
				
				}
			}
		}
	}

// =======
// // Tarjan
// std::vector<unsigned long> Algorithms::Tarjan(Graph graph) {
// >>>>>>> Stashed changes
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

/*
		Johnsons(Graph graph) = graph_matrix = vector<vector<pair<unsigned long, double>>>
		Johnson's algorithm to find the shortest path between all pairs of vertices in a graph.
		Johnson's algorithm accounts for graphs that has negative weights.

		its time complexity is O(|V|^2 * log|V| + |V|*|E|). This time is slower than running Dijkstras 
		for every pair of vertices but it is faster than running Bellman-Ford for every pair of vertices.

		graph_matrix[0][100] == Bellman-Ford(graph,0,100)

*/


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
				
				auto xyz = final_weight[j][i];
				std::reverse(xyz.begin(), xyz.end());
				final_weight[i][j] = xyz;

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
