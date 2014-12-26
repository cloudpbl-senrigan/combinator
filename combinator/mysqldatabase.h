/* 
 * mysqldatabase.h
 * 
 * Author:   Makoto Shimazu <makoto.shimaz@gmail.com>
 * URL:      https://amiq11.tumblr.com               
 * License:  MIT License                             
 * Created:  2014-11-27                                  
 *  
 */

#pragma once

#include "database.h"

#include <memory>

#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <yaml-cpp/yaml.h>

namespace senrigan
{

class MySQLDatabase : public Database
{
public:
  MySQLDatabase(const YAML::Node& config);
  bool open() override;
  void close() override;
  std::shared_ptr<ResultSet> execute(const std::string& sql) override;
  int executeUpdate(const std::string& sql) override;
private:
  std::string dbname_;
  std::shared_ptr<sql::Connection> connection_;
  std::shared_ptr<sql::Statement> statement_;

};

} // namespace senrigan
