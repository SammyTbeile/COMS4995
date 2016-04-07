#include <array>
#include <iostream>
#include <vector>
#include "adjacency_matrix.h"

using namespace std;

vector<vector<double>> make_user_rep(int n, int k) {
  auto user_rep = vector<vector<double>>();
  for(int i = 0; i < n; ++i) {
    user_rep.push_back(vector<double>());
    for(int j = 0; j < n; ++j) {
      user_rep[i].push_back((i + j) * k);
    }
  }
  return user_rep;
}

int main() {
  auto user_rep_0 = make_user_rep(3, 0);
  auto am0 = Adjacency_Matrix(user_rep_0);
  cout << "am0:\n" << am0 << endl;

  // Testing copy assignment
  {
    auto user_rep_1 = make_user_rep(3, 1);
    auto am1 = Adjacency_Matrix(user_rep_1);
    cout << "am1:\n" << am1 << endl;
    cout << ">>>> Testing: am0 = am1\n\n";
    am0 = am1;
    cout << "Inside block am1:\n" << am1 << endl;
  }
  cout << "Outside block am0:\n" << am0 << endl;

  // Testing copy constructor
  {
    cout << ">>>> Testing: am2(am0)\n\n";
    auto am2 = Adjacency_Matrix(am0);
    cout << "Inside block am2:\n" << am2 << endl;
  }
  cout << "Outside block am0:\n" << am0 << endl;
  
  // Test valid
  cout << ">>>> Testing: n != m user graph representation\n\n";
  auto user_rep_3 = vector<vector<double>>();
  user_rep_3.push_back(vector<double>());
  user_rep_3[0].push_back(0);
  user_rep_3[0].push_back(1);
  user_rep_3.push_back(vector<double>());
  user_rep_3[1].push_back(2);
  try {
    auto am3 = Adjacency_Matrix(user_rep_3);
  } catch (Adjacency_Matrix_Exception& e) {
    cout << e.what();
  }
  
  return 0;
}
