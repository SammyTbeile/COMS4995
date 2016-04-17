#ifndef __CREATE_TUPLE_HPP__
#define __CREATE_TUPLE_HPP__
/*
 * Filename: create_tuple.hpp
 * Author:   Sean Garvey
 * UNI:      sjg2174
 */

#include <string>
#include <tuple>
#include <vector>
#include <unordered_map>
#include <utility>

#include "graph_helper.hpp"

std::tuple<Graph_Helper<std::string>, std::unordered_map<std::string,
  std::pair<double, double>>> create_matrix_graph_helper_code_gps_map_tuple();

std::tuple<Graph_Helper<std::string>, std::unordered_map<std::string,
  std::pair<double, double>>> create_list_graph_helper_code_gps_map_tuple();

#endif
