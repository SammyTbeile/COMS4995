#ifndef __TEST_HELPER_HPP__
#define __TEST_HELPER_HPP__
/*
 * Filename: test_helper.hpp
 * Author:   Sean Garvey
 * UNI:      sjg2174
 */

#include <string>
#include <unordered_map>
#include <utility>

#include "graph_helper.hpp"

void connect_database();

void disconnect_database();

std::unordered_map<std::string, std::pair<double, double>> make_code_gps_map();

Graph_Helper<std::string> make_graph_helper(graph_t g);

#endif
