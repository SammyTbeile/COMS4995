#ifndef __ALGORITHMS_HPP__
#define __ALGORITHMS_HPP__
/*
 * Filename: algorithms.hpp
 * Authors:  Sean Garvey, Minh Truong, Sammy Tbeile
 * UNIs:     sjg2174,     mt3077,      st2918
 */

#include <algorithm>
#include <limits>
#include <queue>
#include <random>
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
    static void validate_start_index(Graph& graph, unsigned long start_index);

    static void dfs(Graph& graph, int& count, unsigned long index,
      std::vector<bool>& visited, std::vector<std::pair<unsigned long,
      std::vector<unsigned long>>>& tree,
      std::vector<std::vector<unsigned long>>& backedge);

    static unsigned long lo(unsigned long index, 
      std::vector<std::pair<unsigned long,std::vector<unsigned long>>> tree, 
      std::vector<std::vector<unsigned long>> backedge);

  public:
    /* Public Member Functions */
    static bool is_undirected(Graph& graph);

    static std::vector<std::pair<unsigned long, double>>
      Dijkstras(Graph& graph, unsigned long start_index, unsigned long
      end_index);

    static std::vector<std::vector<std::pair<unsigned long, double>>>
      Prims(Graph& graph);

    static std::vector<std::pair<unsigned long, double>> BellFord(Graph& graph,
      unsigned long start_index, unsigned long end_index);

    static std::vector<unsigned long> Tarjans(Graph& graph);  

    static std::vector<std::vector<std::vector<std::pair<unsigned long, 
      double>>>> Johnsons(Graph& graph);

};

/* Private Member Functions ------------------------------------------------- */

// validate_start_index
void Algorithms::validate_start_index(Graph& graph, unsigned long
start_index) {
  if(start_index >= graph.get_num_vertices()) {
    throw Algorithms_Exception("Starting index is out of range");
  }
}

// dfs - create spaning tree for BellFord
void Algorithms::dfs(Graph& graph, int& count, unsigned long index, std::
vector<bool>& visited, std::vector<std::pair<unsigned long, std::vector<unsigned
long>>>& tree, std::vector<std::vector<unsigned long>>& backedge) {
  visited[index] = true;
  auto temp = std::pair<unsigned long,std::vector<unsigned long>>(count,
    std::vector<unsigned long>());

  tree[index] = temp;
  auto neighbors = graph.get_neighbors(index);
  for(auto& pair: neighbors) {
    if(!visited[pair.first]) {  
      auto p = tree[index];
      auto list = p.second;
      list.push_back(pair.first);
      tree[index] = std::pair<unsigned long,std::vector<unsigned long>>(p.first,list);
      count++;
      dfs(graph, count,pair.first, visited, tree, backedge);
    } else if(tree[index].first > tree[pair.first].first) {
      auto back = backedge[index];
      back.push_back(pair.first);
      backedge[index] = back;
    }
  }
}

// lo - compute low numbers for BellFord
unsigned long Algorithms::lo(unsigned long index, std::vector<std::pair<
unsigned long, std::vector<unsigned long>>> tree, std::vector<std::vector<
unsigned long>> backedge) {
  auto value = std::numeric_limits<double>::infinity();
  auto que = std::queue<unsigned long>();
  auto visited = std::vector<bool>(tree.size());
  visited[index] = true;
  que.push(index);
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

/* Helper Class ------------------------------------------------------------- */
class CompareDist {
public:
    bool operator() (std::pair<double, unsigned long> n1, std::pair<double,
      unsigned long> n2) {
        return n1.first>n2.first;
    }
};

/* Public Member Functions -------------------------------------------------- */

// is_undirected
bool Algorithms::is_undirected(Graph& graph){
  for(int i = 0; i< graph.get_num_vertices(); i++){
    for(int j = 0; j< graph.get_num_vertices(); j++){
      if(graph.matrix[i][j] != graph.matrix[j][i]){
        return false;
      }
    }
  }
  return true;
}

// BellFord
std::vector<std::pair<unsigned long, double>> Algorithms::BellFord(Graph& graph,
unsigned long start_index, unsigned long end_index) {
  validate_start_index(graph, start_index);

  int num = graph.get_num_vertices();
  std::vector<double> distance = std::vector<double>(num);
  std::vector<unsigned long> predecessor = std::vector<unsigned long>(num);

  //initalize values
  for(int i = 0; i< num; i++) {
    distance[i] = std::numeric_limits<double>::infinity();
    predecessor[i] = -1; 
  }
  distance[start_index] = 0;

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

  if(predecessor[end_index] == -1){
    throw Algorithms_Exception("NOO PATH");
  }


  //construct path
  std::vector<std::pair<unsigned long, double>> path;
  unsigned long current = end_index;
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
  } while(current != start_index);

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

// Dijkstra's
std::vector<std::pair<unsigned long, double>> Algorithms::Dijkstras(Graph&
graph, unsigned long start_index, unsigned long end_index) {

  validate_start_index(graph, start_index);
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
  distance[start_index] = 0;

  using pdl = std::pair<double,unsigned long>;
  std::priority_queue<pdl,std::vector<pdl>,CompareDist> que;
  que.push(std::pair<double,unsigned long>(0,start_index));

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

  if(predecessor[end_index] == -1){
    throw Algorithms_Exception("No Path");
  }

  //construct path

  std::vector<std::pair<unsigned long, double>> path;
  unsigned long current = end_index;
  path.push_back(std::pair<unsigned long, double>(current, distance[current]));
  do {
    current = predecessor[current];
    auto newpair = std::pair<unsigned long, double>(current, distance[current]);
    path.push_back(newpair);
  } while(current != start_index);

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

// Johnson's
std::vector<std::vector<std::vector<std::pair<unsigned long, double>>>>
 Algorithms::Johnsons(Graph& graph){
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
  unsigned long start_index = num;

  num = num + 1;
  std::vector<double> distance = std::vector<double>(num);
  std::vector<unsigned long> predecessor = std::vector<unsigned long>(num);
  //initalize values
  for(int i = 0; i< num; i++) {
    distance[i] = std::numeric_limits<double>::infinity();
    predecessor[i] = 0; // 
    
    }

  distance[start_index] = 0;
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
  auto final_weight = std::vector<std::vector<std::vector<std::pair<unsigned
    long, double>>>>(length);
  for(int i = 0; i < length ; i++){
    final_weight[i] = std::vector<std::vector<std::pair<unsigned long,
      double>>>(length);
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

// Prim's
std::vector<std::vector<std::pair<unsigned long, double>>> Algorithms::Prims(
Graph& graph) {
  // validate_start_index(graph, start_index);
  //Initalize variables and containers
  int num = graph.get_num_vertices();
  std::vector<double> distances = std::vector<double>(num);
  std::vector<unsigned long> predecessor = std::vector<unsigned long>(num);
  std::vector<bool> known = std::vector<bool>(num);
  std::vector<unsigned long> vertices = std::vector<unsigned long>(num);

  //Initialize vertices for algorithms
  for(int i=0;i<num;i++){
    distances[i]=std::numeric_limits<double>::infinity();
    predecessor[i] = -1;
    known[i] = false;
  }
  // Get random starting index
  std::random_device rd;
  unsigned long starting_index = rd() % graph.get_num_vertices();

  // Get start value
  distances[starting_index] = 0;
  std::priority_queue<std::pair<double,unsigned long>,std::vector<std::pair<
    double,unsigned long>>,CompareDist> queue;
  queue.push(std::pair<double,unsigned long>(distances[starting_index],starting_index));

  //Perform Dijkstra's with the relaxed distance update
  while(!queue.empty()){
    //Get the smallest index
    std::pair<double,unsigned long> temp = queue.top();
    queue.pop();

    //Check to make sure that the index hasn't already been declared known
    if(!known[temp.second]){
       known[temp.second]=true;
       for(auto& index : graph.list[temp.second]){
          vertices[index.first]=index.first;
          if(!known[index.first]){
            if(index.second < distances[index.first]){
              distances[index.first] = index.second;
              predecessor[index.first] = temp.second;
              queue.push(std::pair<double,unsigned long>(
                distances[index.first],index.first));
            }
          }
       }
    }
  }
  //Construct the MST
  std::vector<std::vector<std::pair<unsigned long,double>>> returnVector =
    std::vector<std::vector<std::pair<unsigned long,double>>>();

    for(auto i =0; i<vertices.size();i++ ){
      std::vector<std::pair<unsigned long, double>> innerList = std::vector<std::pair<unsigned long, double>>();
      innerList.push_back(std::pair<unsigned long, double>(vertices[i],distances[i]));
      if(predecessor[i]!=-1){
        innerList.push_back(std::pair<unsigned long, double>(predecessor[i],distances[predecessor[i]]));}
      returnVector.push_back(innerList);
    }

    return returnVector;
}

// Tarjan's
std::vector<unsigned long> Algorithms::Tarjans(Graph& graph) {

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

#endif
