#ifndef __ALGORITHMS_HPP__
#define __ALGORITHMS_HPP__
/*
 * Filename: algorithms.hpp
 * Authors:  Sean Garvey, Minh Truong, Sammy Tbeile
 * UNIs:     sjg2174,     mt3077,      st2918
 */

#include <exception>
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
      Dijkstras(Graph graph, unsigned long start_vertex);
    static std::vector<std::pair<unsigned long, double>>
      Prims(Graph graph, unsigned long start_vertex);

		static std::vector<std::pair<unsigned long, double>> BellFord(Graph graph, unsigned long start_vertex, unsigned long end_vertex);

			static std::vector<unsigned long> Tarjan(Graph graph);	
/*
		static std::vector<std::pair<unsigned long, double>> 
			traveling_salesman(Graph graph);*/

		static bool is_undirected(Graph graph);

		static std::vector<std::vector<std::vector<std::pair<unsigned long, double>>>>
 johnson(Graph graph);

};

#endif
