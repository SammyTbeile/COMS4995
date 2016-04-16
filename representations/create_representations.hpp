#ifndef __CREATE_REPRESENTATIONS_HPP__
#define __CREATE_REPRESENTATIONS_HPP__
/*
 * Filename: create_representations.hpp
 * Author:   Sean Garvey
 * UNI:      sjg2174
 */

#include <tuple>
#include <vector>
#include <unordered_map>

std::tuple<
  std::vector<std::vector<double>>,
  std::unordered_map<unsigned long, std::string>,
  std::unordered_map<std::string, std::pair<double, double>>
>
create_matrix_representation();
//void create_list_representation();

#endif
