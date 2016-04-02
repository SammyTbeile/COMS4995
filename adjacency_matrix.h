#ifndef __ADJACENCY_MATRIX_H__
#define __ADJACENCY_MATRIX_H__
/*
 * Filename: adjacency_matrix.h
 * Authors:  Sean Garvey, Sammy Tbeile, Minh Truong
 * UNIs:     sjg2174,     st2918,       mt3077
 */

#include <vector>
#include <iostream>
#include <list>
#include <array>

template <typename Container>
class Adjacency_Matrix;
template <typename Container>
std::ostream& operator<<(std::ostream& os, const Adjacency_Matrix<Container>& am);

template <typename Container>
class Adjacency_Matrix {
public:
	Adjacency_Matrix();
  Adjacency_Matrix(Container cont);
  Adjacency_Matrix(const Adjacency_Matrix& am);
  Adjacency_Matrix& operator=(const Adjacency_Matrix& am);
  int get_num_vertices() const;
	int get_num_edges() const;
  double get_weight(int row, int col);
	bool check_nxn(Container cont);
  std::vector<double> get_neighbors(int vertex);
 friend std::ostream& operator<< <Container>(std::ostream& os, const Adjacency_Matrix<Container>& am);
  
private:
  std::vector<std::vector<double>> matrix;
  std::vector<std::vector<bool>>   visited;
  int num_edges;
  int num_vertices;
};

template<typename Container>
Adjacency_Matrix<Container>::Adjacency_Matrix(){
	matrix = std::vector<std::vector<double>>();
	num_vertices = 0;
	num_edges = 0;
}

template<typename Container>
Adjacency_Matrix<Container>::Adjacency_Matrix(const Adjacency_Matrix& src){
	matrix = std::vector<std::vector<double>>();

	for(auto i = 0; i< src.matrix.size(); i++){
		std::vector<double> row = src.matrix[i];
		matrix.push_back(row);
	}
	num_vertices = src.get_num_vertices();
	num_edges = src.get_num_edges();
}
/*
template<>
Adjacency_Matrix<std::vector<std::list<double>>>::Adjacency_Matrix(std::vector<std::list<double>> cont){
	matrix = std::vector<std::vector<double>>();
	num_vertices = 0;
	num_edges = 0;

}

template<>
Adjacency_Matrix<std::array<std::list<std::pair<int,double>>>>::Adjacency_Matrix(std::array<std::list<std::pair<int,double>>> cont){
	matrix = std::vector<std::vector<double>>();
	int rowcount = 0;

	for(auto i = cont.begin(); i!= cont.end(); ++i){
		auto rowvector = *i;
		std::vector<double> temprow;
		int colcount = 0;

		for(auto j = rowvector.begin(); j != rowvector.end(); ++j){
			std::pair <int,double> temppair = *j;
		}

	}

}
*/

template <typename Container>
Adjacency_Matrix<Container>::Adjacency_Matrix(Container cont){

	matrix = std::vector<std::vector<double>>();
	int edgecount = 0;
	int rowcount = 0;

	if(check_nxn(cont)){
		for(auto i = cont.begin(); i != cont.end(); ++i){

			auto rowvector = *i ;
			std::vector<double> temprow;
			int colcount = 0;
			for(auto j = i->begin(); j != i->end(); ++j){

				double weight = *j;
				if( (weight == 0) || (rowcount == colcount) ){
					temprow.push_back(0);
				/*else if  weight < 0 throw bad weight exception*/}else{
					temprow.push_back(weight);
					edgecount++;
				}
				colcount++;
			}
			rowcount++;
			matrix.push_back(temprow);
		}
	}

	num_vertices = matrix.size();
	num_edges = edgecount;
}

template <typename Container>
Adjacency_Matrix<Container>& Adjacency_Matrix<Container>::operator=(const Adjacency_Matrix& am) {
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
  return *this;
}

template <typename Container>
bool Adjacency_Matrix<Container>::check_nxn(Container cont){
	int size = cont.size();
  for(auto &row : cont) {
    if(row.size() != size) {
      return false;
    }
  }
  return true;
}

template <typename Container>
int Adjacency_Matrix<Container>::get_num_vertices() const {
  return num_vertices;
}

template <typename Container>
int Adjacency_Matrix<Container>::get_num_edges() const {
  return num_edges;
}

template <typename Container>
std::vector<double> Adjacency_Matrix<Container>::get_neighbors(int vertex){
  return matrix[vertex];
}

template <typename Container>
double Adjacency_Matrix<Container>::get_weight(int row, int col) {
  return matrix[row][col];
}

template<typename Container>
std::ostream& operator<<(std::ostream& os, const Adjacency_Matrix<Container>& am) {
  for(auto &row : am.matrix) {
    for(auto &col : row) {
      os << col << " ";
    }
    os << '\n';
  }
  return os;
}


#endif
