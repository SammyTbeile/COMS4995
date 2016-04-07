#include <array>
#include <iostream>
#include <vector>
#include <list>
//#include "adjacency_matrix.h"
#include "adjacency_list.h"

//#include "combine.h"

using namespace std;


int main() {

  vector<vector<double>> vvd = vector<vector<double>>();
	vector<list<pair<int,double>>> vld = vector<list<pair<int,double>>>();

	
  int n = 10;
  for(int i = 0; i < n; ++i) {
		vld.push_back(list<pair<int,double>>());
    vvd.push_back(vector<double>());
    for(int j = 0; j < n; ++j) {
      vvd[i].push_back(j);
			vld[i].push_back(pair<int,double>(j,3.0));
		}
	}

  //Adjacency_Matrix<vector<vector<double>>> am = Adjacency_Matrix<vector<vector<double>>>(vvd);

	Adjacency_List<vector<list<pair<int,double>>>> amw = Adjacency_List<vector<list<pair<int,double>>>>(vld);
	Adjacency_List<vector<list<pair<int,double>>>> amw2 = Adjacency_List<vector<list<pair<int,double>>>>(amw);


	cout << amw.get_num_vertices() << endl;
	
	cout << amw.get_num_edges() << endl;

	cout << amw2.get_num_vertices() << endl;
	
	cout << amw2.get_num_edges() << endl;

	
	cout << amw2 <<endl;

	cout << amw << endl;
  return 0;
}
