#ifndef __ADJACENCY_LIST_HPP__
#define __ADJACENCY_LIST_HPP__
/*
 * Filename: adjacency_list.h
 * Authors:  Sean Garvey, Sammy Tbeile, Minh Truong
 * UNIs:     sjg2174,     st2918,       mt3077
 */

 /* Exception */
class Adjacency_List_Exception : public std::exception {
private:
  const char* message;
public:
  Adjacency_List_Exception(const char* msg) { message = msg; }
  virtual const char* what() const throw() { return message; }
};

template <typename Container>
class Adjacency_List;
template <typename Container>
std::ostream& operator<<(std::ostream& os, const Adjacency_List<Container>& am);

template <typename Container>
class Adjacency_List {

public:
	Adjacency_List();
  Adjacency_List(Container cont);
  Adjacency_List(const Adjacency_List& am);
  Adjacency_List& operator=(const Adjacency_List& am);
  int get_num_vertices() const;
	int get_num_edges() const;
  double get_weight(int row, int col);
	bool check_nxn(Container cont);
  std::vector<double> get_neighbors(int vertex);
 friend std::ostream& operator<< <Container>(std::ostream& os, const Adjacency_List<Container>& am);
  
private:
  std::vector<std::vector<double>> matrix;
  std::vector<std::vector<bool>>   visited;
  int num_edges;
  int num_vertices;
};

template<typename Container>
Adjacency_List<Container>::Adjacency_List(){
	matrix = std::vector<std::vector<double>>();
	num_vertices = 0;
	num_edges = 0;
}

template<typename Container>
Adjacency_List<Container>::Adjacency_List(const Adjacency_List& src){
	matrix = std::vector<std::vector<double>>();

	for(auto i = 0; i< src.matrix.size(); i++){
		std::vector<double> row = src.matrix[i];
		matrix.push_back(row);
	}
	num_vertices = src.get_num_vertices();
	num_edges = src.get_num_edges();
}

template <typename Container>
Adjacency_List<Container>::Adjacency_List(Container cont){

	matrix = std::vector<std::vector<double>>();
	int edgecount = 0;
	int rowcount = 0;

	for(auto i = cont.begin(); i != cont.end(); ++i){

		auto rowvector = *i ;
		std::vector<double> temprow = std::vector<double>(cont.size());

		for(auto j = i->begin(); j != i->end(); ++j){

			std::pair<int,double> tempPair = *j;
			if(tempPair.first==rowcount){
					temprow[tempPair.first] = 0;
			}else if (tempPair.second < 0){
				throw Adjacency_List_Exception("Undefined edge weight\n");
			}else{
				edgecount++;
				temprow[tempPair.first] = tempPair.second;
			}
		}
		matrix.push_back(temprow);
		rowcount++;
	}

	num_vertices = matrix.size();
	num_edges = edgecount;
}

template <typename Container>
bool Adjacency_List<Container>::check_nxn(Container cont){
	int size = cont.size();
  for(auto &row : cont) {
    if(row.size() != size) {
      return false;
    }
  }
  return true;
}

template <typename Container>
Adjacency_List<Container>& Adjacency_List<Container>::operator=(const Adjacency_List& am) {
  if(this == &am) {
    return *this;
  }
  int n = am.get_num_vertices();
  for(auto i = 0; i < n; ++i) {
    matrix[i] = std::vector<double>(n);
    for(auto j = 0; j < n; ++j) {
      matrix[i][j] = am.matrix[i][j];
    }
  }
  num_vertices = n;
	num_edges = am.get_num_edges();
  return *this;
}


template <typename Container>
int Adjacency_List<Container>::get_num_vertices() const {
  return num_vertices;
}

template <typename Container>
int Adjacency_List<Container>::get_num_edges() const {
  return num_edges;
}

template <typename Container>
std::vector<double> Adjacency_List<Container>::get_neighbors(int vertex){
  return matrix[vertex];
}

template <typename Container>
double Adjacency_List<Container>::get_weight(int row, int col) {
  return matrix[row][col];
}


template<typename Container>
std::ostream& operator<<(std::ostream& os, const Adjacency_List<Container>& am) {
  for(auto &row : am.matrix) {
    for(auto &col : row) {
      os << col << " ";
    }
    os << '\n';
  }

  return os;
}

#endif
