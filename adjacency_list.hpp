#ifndef __ADJACENCY_LIST_HPP__
#define __ADJACENCY_LIST_HPP__
/*
 * Filename: adjacency_list.hpp
 * Author:   Sean Garvey
 * UNI:      sjg2174
 */

#include <iostream>
#include <list>
#include <vector>
#include "algorithms.hpp"
#include "adjacency_list_exception.hpp"

/* Adjacency_List ----------------------------------------------------------- */

class Adjacency_List {
  friend class Algorithms;
  private:
    /* Variables */
    std::vector<std::list<double>> list;
    std::vector<std::vector<bool>> visited;
    unsigned long num_edges;
    unsigned long num_vertices;

    /* Private Member Functions */
    void count_edges();
    std::list<double>& get_neighbors(unsigned long row);
    bool has_negative_edges();
    void set_visited(unsigned long row, unsigned long col, bool b);

  public:
    /* Constructors */
    template<typename Container>
    Adjacency_List(Container container);
    Adjacency_List(const Adjacency_List& al);

    /* Public Member Functions */
    unsigned long get_num_edges();
    unsigned long get_num_vertices();
    bool get_visited(unsigned long row, unsigned long col);
    double get_weight(unsigned long row, unsigned long col);

    /* Operators */
    Adjacency_List& operator=(const Adjacency_List& al);
    friend std::ostream& operator<<(std::ostream& os, const Adjacency_List& al);
};

/* Private Member Functions ------------------------------------------------- */

// count_edges
void Adjacency_List::count_edges() {
  for(auto& row : list) {
    for(auto& col : row) {
      ++num_edges;
    }
  }
}

// get_neighbors
std::list<double>& Adjacency_List::get_neighbors(unsigned long row) {
  return list[row];
}

// has_negative_edges
bool Adjacency_List::has_negative_edges() {
  for(auto& row : list) {
    for(auto& col : row) {
      if(col.second < 0) {
        return true;
      }
    }
  }
  return false;
}

// set_visited
void Adjacency_List::set_visited(unsigned long row, unsigned long col, bool b) {
  visited[row][col] = b;
}

/* Constructors ------------------------------------------------------------- */

// Constructor
template<typename Container>
Adjacency_List::Adjacency_List(Container container) {
  list = std::vector<std::list<double>>();
  for(auto it = container.begin(); it != container.end(); ++it) {
    list.push_back(std::list<double>(it->begin(), it->end()));
  }
  if(has_negative_edges()) {
    throw Adjacency_List_Exception("Graph representation has negative edges\n");
  } else {
    count_edges();
    num_vertices = list.size();
    visited = std::vector<std::vector<bool>>();
    for(int i = 0; i < num_edges; ++i) {
      visited.push_back(std::vector<bool>());
    }
  }
}

// Copy Constructor
Adjacency_List::Adjacency_List(const Adjacency_List& al) {
  list = al.list;
  num_edges = al.num_edges;
  num_vertices = al.num_vertices;
}

/* Public Member Functions -------------------------------------------------- */

// get_num_edges
unsigned long Adjacency_List::get_num_edges() {
  return num_edges;
}

// get_num_vertices
unsigned long Adjacency_List::get_num_vertices() {
  return num_vertices;
}

// get_visited
bool Adjacency_List::get_visited(unsigned long row, unsigned long col) {
  return visited[row][col];
}

// get_weight
double Adjacency_List::get_weight(unsigned long row, unsigned long col) {
  auto row_list = list[row];
  for(auto& node : row_list) {
    if(node.first == col) {
      return node.second;
    }
  }
  return 0;
}

/* Operators ---------------------------------------------------------------- */

// =
Adjacency_List& Adjacency_List::operator=(const Adjacency_List& al) {
  if(this == &al) {
    return *this;
  }
  list = al.list;
  num_edges = al.num_edges;
  num_vertices = al.num_vertices;
  return *this;
}

// <<
std::ostream& operator<<(std::ostream& os, const Adjacency_List& al) { 
  for(auto &row : al.list) {
    for(auto &col : row) {
      os << col << " ";
    }
    os << '\n';
  } 
  return os;
}

#endif
