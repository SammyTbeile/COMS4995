

#include "algorithms.hpp"
#include "algorithms.cpp"
#include <iostream>
#include <vector>
#include <list>
#include "graph.hpp"

using namespace std;

int main () {

	//constructed graph from this http://algs4.cs.princeton.edu/lectures/44DemoBellmanFord.pdf. has answers to shortest path

	vector<list<pair<unsigned long, double>>> tempg = vector<list<pair<unsigned long, double>>>();
	list<pair<unsigned long, double>> a = list<pair<unsigned long, double>>();
	a.push_back(pair<unsigned long, double>(1,5));
	a.push_back(pair<unsigned long, double>(7,8));
	a.push_back(pair<unsigned long, double>(4,9));
	tempg.push_back(a);

	list<pair<unsigned long, double>> b = list<pair<unsigned long, double>>();
	b.push_back(pair<unsigned long, double>(3,15));
	b.push_back(pair<unsigned long, double>(2,12));
	b.push_back(pair<unsigned long, double>(7,4));
	tempg.push_back(b);

	list<pair<unsigned long, double>> c = list<pair<unsigned long, double>>();
	c.push_back(pair<unsigned long, double>(3,3));
	c.push_back(pair<unsigned long, double>(6,11));
	tempg.push_back(c);

	list<pair<unsigned long, double>> d = list<pair<unsigned long, double>>();
	d.push_back(pair<unsigned long, double>(6,9));
	tempg.push_back(d);

	list<pair<unsigned long, double>> e = list<pair<unsigned long, double>>();
	e.push_back(pair<unsigned long, double>(7,5));
	e.push_back(pair<unsigned long, double>(5,4));
	e.push_back(pair<unsigned long, double>(6,20));
	tempg.push_back(e);

	list<pair<unsigned long, double>> f = list<pair<unsigned long, double>>();
	f.push_back(pair<unsigned long, double>(2,1));
	f.push_back(pair<unsigned long, double>(6,13));
	tempg.push_back(f);

	list<pair<unsigned long, double>> g = list<pair<unsigned long, double>>();
	tempg.push_back(g);

	list<pair<unsigned long, double>> h = list<pair<unsigned long, double>>();
	h.push_back(pair<unsigned long, double>(2,7));
	h.push_back(pair<unsigned long, double>(5,6));
	tempg.push_back(h);

	cout << tempg << endl;

	auto graph = Graph(tempg);

  cout << "hello world" << endl;


	auto values = Algorithms::BellFord(graph,0,6);
	cout << "here" << endl;
	for(auto& edge: values){
		cout << edge.first << " " << edge.second << endl;
	}

  return 0;
}
