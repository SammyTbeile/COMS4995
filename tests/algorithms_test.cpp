/*
 * Filename: algorithms_test.cpp
 * Authors:  Minh Truong
 * UNIs:     mt3077
 */

#include <iostream>
#include <list>

#include "algorithms.hpp"

using namespace std;

int main() {

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

	//cout << tempg << endl;

	auto graph = Graph(tempg);

	auto values = Algorithms::BellFord(graph,0,6);
	for(auto& edge: values){
		cout << edge.first << " " << edge.second << endl;
	}
	/*
	auto tempx = vector<list<pair<unsigned long, double>>>();
	auto x = list<pair<unsigned long, double>>();
	x.push_back(pair<unsigned long, double>(1,15));
	x.push_back(pair<unsigned long, double>(3,12));
	tempx.push_back(x);

	auto q = list<pair<unsigned long, double>>();
	q.push_back(pair<unsigned long, double>(3,15));
	q.push_back(pair<unsigned long, double>(4,12));
	tempx.push_back(q);

	auto w = list<pair<unsigned long, double>>();
	w.push_back(pair<unsigned long, double>(0,15));
	w.push_back(pair<unsigned long, double>(5,12));
	tempx.push_back(w);

	auto t = list<pair<unsigned long, double>>();
	t.push_back(pair<unsigned long, double>(4,15));
	t.push_back(pair<unsigned long, double>(2,12));
	t.push_back(pair<unsigned long, double>(5,12));
	t.push_back(pair<unsigned long, double>(6,12));
	tempx.push_back(t);


	auto y = list<pair<unsigned long, double>>();
	y.push_back(pair<unsigned long, double>(6,15));
	tempx.push_back(y);

	auto v = list<pair<unsigned long,double>>();
	tempx.push_back(v);

	auto r = list<pair<unsigned long, double>>();
	r.push_back(pair<unsigned long, double>(5,15));
	tempx.push_back(r);

	

	auto graphx = Graph(tempx);

	auto values = Algorithms::Tarjan(graphx);*/

  return 0;
}
