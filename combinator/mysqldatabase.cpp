/* 
 * mysqldatabase.cpp
 * 
 * Author:   Makoto Shimazu <makoto.shimaz@gmail.com>
 * URL:      https://amiq11.tumblr.com               
 * License:  MIT License                             
 * Created:  2014-11-27                                  
 *  
 */

#include "mysqldatabase.h"

#include <iostream>

#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <yaml-cpp/yaml.h>

#include "mysqlresultset.h"

using namespace senrigan;
using namespace std;

MySQLDatabase::MySQLDatabase(const std::string &yaml_path)
{
  // Load yaml
  YAML::Node config = YAML::LoadFile(yaml_path);

  // Validate settings
  if (!(config["database"] &&
        config["database"]["user"] &&
        config["database"]["password"] &&
        config["database"]["host"] &&
        config["database"]["dbname"])) {
    throw "Config file must set the parameters: "
          "{database: {user:, password:, host:, dbname:}}";
  }

  const YAML::Node &dbconfig = config["database"];

  // Connect to mysql
  auto driver = sql::mysql::get_mysql_driver_instance();
  shared_ptr<sql::Connection> connection(
      driver->connect(dbconfig["host"].as<string>(),
                      dbconfig["user"].as<string>(),
                      dbconfig["password"].as<string>()));

  // Set member variables
  dbname_ = dbconfig["dbname"].as<string>();
  connection_ = connection;
}

bool MySQLDatabase::open()
{
  // TODO: Check if this is succeeded
  shared_ptr<sql::Statement> statement(connection_->createStatement());
  statement_ = statement;
  statement_->execute(string("use ") + dbname_);
  return true;
}

void MySQLDatabase::close()
{
}

shared_ptr<ResultSet> MySQLDatabase::execute(const std::string &sql)
{
  return shared_ptr<ResultSet> (
      new MySQLResultSet(statement_->executeQuery(sql)));
}
