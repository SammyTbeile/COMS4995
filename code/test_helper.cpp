/*
 * Filename: test_helper.cpp
 * Author:   Sean Garvey
 * UNI:      sjg2174
 */

#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>

#include <exception>

#include "test_helper.hpp"

using namespace std;
using namespace sql;

// Globals
const static char *url_env_var      = "DATABASE_CONNECTOR_URL";
const static char *username_env_var = "DATABASE_CONNECTOR_USERNAME";
const static char *password_env_var = "DATABASE_CONNECTOR_PASSWORD";
const static char *database_env_var = "DATABASE_CONNECTOR_DATABASE";
static Driver     *driver;
static Connection *connection;
static Statement  *statement;

/* connect_database */
void connect_database() {

  // Get Environment Variables
  char *url      = getenv(url_env_var);
  char *username = getenv(username_env_var);
  char *password = getenv(password_env_var);
  char *database = getenv(database_env_var);

  // Check Missing Variables
  auto errs     = vector<string>();
  if(!url)      errs.push_back(url_env_var);
  if(!username) errs.push_back(username_env_var);
  if(!password) errs.push_back(password_env_var);
  if(!database) errs.push_back(database_env_var);

  // If Missing, Throw Exception
  if(errs.size() != 0) {
    string msg;
    for(string s : errs) {
      msg += s + '\n';
    }
    throw logic_error("\nMissing Environment Variables:\n" + msg);
  }

  // Setup Database Connection
  try {
    driver = get_driver_instance();
    connection = driver->connect(url, username, password);
    connection->setAutoCommit(0);
    connection->setSchema(database);
    statement = connection->createStatement();
  } catch (SQLException& e) {
    // Termiante
    cout << "SQL Exception: " << e.what() << '\n' << e.getErrorCode() <<
      '\n' << e.getSQLState() << endl;
    terminate();
  }
}

/* disconnect_database */
void disconnect_database() {
  try {
    delete statement;
    connection->close();
    delete connection;
  } catch (SQLException& e) {
    // Termiante
    cout << "SQL Exception: " << e.what() << '\n' << e.getErrorCode() <<
      '\n' << e.getSQLState() << endl;
    terminate();
  }
}

/* make_code_gps_map */
unordered_map<string, pair<double, double>> make_code_gps_map() {
  auto code_gps_map = unordered_map<string, pair<double, double>>();
  try {
    // Query
    auto result_set = statement->executeQuery("SELECT * FROM WorldAirports"); // WorldAirports or Airports
    while(result_set->next()) {
      auto code  = result_set->getString("FAA");
      double lat = result_set->getDouble("Lat");
      double lng = result_set->getDouble("Lng");
      try {
        code_gps_map.at(code);
        throw logic_error("Airport code: " + code + " already exists in code_gps_map");
      } catch (out_of_range& e) {
        code_gps_map[code] = make_pair(lat, lng);
      }
    }
    delete result_set;
  } catch (SQLException& e) {
    // Termiante
    cout << "SQL Exception: " << e.what() << '\n' << e.getErrorCode() <<
      '\n' << e.getSQLState() << endl;
    terminate();
  }
  return code_gps_map;
}

/* make_graph_helper */
Graph_Helper<string> make_graph_helper(graph_t g) {
  auto graph_helper = Graph_Helper<string>(g);
  try {
    auto result_set = statement->executeQuery("SELECT * FROM WorldPaths"); // WorldPaths or Paths
    int counter =0;
    while(result_set->next()&& counter <1000) {
      counter++;
      auto origin = result_set->getString("Origin");
      auto destin = result_set->getString("Destin");
      double dist = result_set->getInt("Distance");
      graph_helper.add_edge(origin, destin, dist);
    }
    delete result_set;
  } catch (SQLException& e) {
    // Termiante
    cout << "SQL Exception: " << e.what() << '\n' << e.getErrorCode() <<
      '\n' << e.getSQLState() << endl;
    terminate();
  }
  return graph_helper;
}
