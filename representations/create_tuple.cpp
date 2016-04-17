/*
 * Filename: create_tuple.cpp
 * Author:   Sean Garvey
 * UNI:      sjg2174
 */

#include <string>
#include <tuple>
#include <vector>
#include <unordered_map>
#include <utility>

#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>

#include "create_tuple.hpp"

const static char *url_env_var      = "DATABASE_CONNECTOR_URL";
const static char *username_env_var = "DATABASE_CONNECTOR_USERNAME";
const static char *password_env_var = "DATABASE_CONNECTOR_PASSWORD";
const static char *database_env_var = "DATABASE_CONNECTOR_DATABASE";

std::vector<std::string> load_env_vars() {
  auto env_vars = std::vector<std::string>();
  auto errs     = std::vector<std::string>();

  char *url      = getenv(url_env_var);
  char *username = getenv(username_env_var);
  char *password = getenv(password_env_var);
  char *database = getenv(database_env_var);

  if(!url)      errs.push_back(url_env_var);
  if(!username) errs.push_back(username_env_var);
  if(!password) errs.push_back(password_env_var);
  if(!database) errs.push_back(database_env_var);

  if(errs.size() != 0) {
    std::string msg;
    for(std::string s : errs) {
      msg += s + '\n';
    }
    throw std::logic_error("\nMissing Environment Variables:\n" + msg);
  }

  env_vars.push_back(std::string(url));
  env_vars.push_back(std::string(username));
  env_vars.push_back(std::string(password));
  env_vars.push_back(std::string(database));
  return env_vars;
}

/*
std::tuple<
  std::vector<std::vector<double>>,
  std::unordered_map<unsigned long, std::string>,
  std::unordered_map<std::string, std::pair<double, double>>
>
create_matrix_representation() {
  auto env_vars = load_env_vars();
  auto url      = env_vars[0];
  auto username = env_vars[1];
  auto password = env_vars[2];
  auto database = env_vars[3];

  std::vector<std::vector<double>> matrix;
  std::unordered_map<std::string, std::pair<double, double>> code_gps_map;
  std::unordered_map<std::string, unsigned long> code_vertex_map;
  std::unordered_map<unsigned long, std::string> vertex_code_map;

  try {
    auto driver = get_driver_instance();
    auto connection = driver->connect(url, username, password);
    connection->setAutoCommit(0);
    connection->setSchema(database);
    auto statement = connection->createStatement();

    auto result_set = statement->executeQuery("SELECT * FROM Airports");
    auto code_gps_map = std::unordered_map<std::string, std::pair<double, double>>();
    while(result_set->next()) {
      std::string code = result_set->getString("code");
      double lat = result_set->getDouble("lat");
      double lng = result_set->getDouble("lng");
      try {
        code_gps_map.at(code);
        throw std::logic_error("Airport code: " + code + " already exists in code_gps_map");
      } catch (std::out_of_range& e) {
        code_gps_map[code] = std::make_pair(lat, lng);
      }
    }
    delete result_set;

    unsigned long num_codes = code_gps_map.size();
    matrix.resize(num_codes);
    unsigned long index = 0;
  
    result_set = statement->executeQuery("SELECT * FROM Paths");
    code_vertex_map = std::unordered_map<std::string, unsigned long>();
    vertex_code_map = std::unordered_map<unsigned long, std::string>();
    while(result_set->next()) {
      std::string origin = result_set->getString("origin");
      std::string destin = result_set->getString("destin");
      double dist = result_set->getInt("dist");
      try {
        code_vertex_map.at(origin);
      } catch (std::out_of_range& e) {
        code_vertex_map[origin] = index;
        (matrix[index] = std::vector<double>()).resize(num_codes);
        vertex_code_map[index] = origin;
        ++index;
      }
      try {
        code_vertex_map.at(destin);
      } catch (std::out_of_range& e) {
        code_vertex_map[destin] = index;
        (matrix[index] = std::vector<double>()).resize(num_codes);
        vertex_code_map[index] = destin;
        ++index;
      }
      matrix[code_vertex_map[origin]][code_vertex_map[destin]] = dist;
    }
    delete result_set;
    for(unsigned long i = 0; i < index; ++i) {
      matrix[i].resize(index);
      matrix[i].shrink_to_fit();
    }
    matrix.resize(index);
    matrix.shrink_to_fit();

    delete statement;
    connection->close();
    delete connection;
  } catch (sql::SQLException &e) {
    std::cout << "SQL Exception: " << e.what() << '\n' <<
      e.getErrorCode() << '\n' <<
      e.getSQLState() << std::endl;
  }

  std::tuple<
    std::vector<std::vector<double>>,
    std::unordered_map<unsigned long, std::string>,
    std::unordered_map<std::string, std::pair<double, double>>
  > rtn_tuple (matrix, vertex_code_map, code_gps_map);
  return rtn_tuple;
}
*/










// create_tuple
std::tuple<Graph_Helper<std::string>, std::unordered_map<std::string,
  std::pair<double, double>>> create_tuple(graph_t g) {

  // Load Environment Variables
  auto env_vars = load_env_vars();
  auto url      = env_vars[0];
  auto username = env_vars[1];
  auto password = env_vars[2];
  auto database = env_vars[3];

  // Return Variables
  auto graph_helper = Graph_Helper<std::string>(g);
  auto code_gps_map = std::unordered_map<std::string, std::pair<double, double>>();

  try {
    // Setup Database Connection
    auto driver = get_driver_instance();
    auto connection = driver->connect(url, username, password);
    connection->setAutoCommit(0);
    connection->setSchema(database);
    auto statement = connection->createStatement();

    // Query - Construct code_gps_map
    auto result_set = statement->executeQuery("SELECT * FROM Airports");
    while(result_set->next()) {
      std::string code = result_set->getString("code");
      double lat = result_set->getDouble("lat");
      double lng = result_set->getDouble("lng");
      try {
        code_gps_map.at(code);
        throw std::logic_error("Airport code: " + code + " already exists in code_gps_map");
      } catch (std::out_of_range& e) {
        code_gps_map[code] = std::make_pair(lat, lng);
      }
    }

    // Clean Up
    delete result_set;
  
    // Query - Construct graph_helper
    result_set = statement->executeQuery("SELECT * FROM Paths");
    while(result_set->next()) {
      std::string origin = result_set->getString("origin"); // TODO
      std::string destin = result_set->getString("destin");
      double dist = result_set->getInt("dist");
      graph_helper.add_edge(origin, destin, dist);
    }

    // Clean Up
    delete result_set;
    delete statement;
    connection->close();
    delete connection;

  } catch (sql::SQLException &e) {
    std::cout << "SQL Exception: " << e.what() << '\n' << e.getErrorCode() <<
      '\n' << e.getSQLState() << std::endl;
  }

  return std::make_tuple(graph_helper, code_gps_map);
}

// create_list_tuple
std::tuple<Graph_Helper<std::string>, std::unordered_map<std::string,
  std::pair<double, double>>> create_list_tuple() {
  return create_tuple(LIST);
}

// create_matrix_tuple
std::tuple<Graph_Helper<std::string>, std::unordered_map<std::string,
  std::pair<double, double>>> create_matrix_tuple() {
  return create_tuple(MATRIX);
}
