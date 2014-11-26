/* 
 * combinator.cpp
 * 
 * Author:   Makoto Shimazu <makoto.shimaz@gmail.com>
 * URL:      https://amiq11.tumblr.com               
 * License:  MIT License                             
 * Created:  2014-11-26                                  
 *  
 */

#include "combinator.h"

#include <iostream>
#include <memory>

#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <mysql_connection.h>
#include <mysql_driver.h>

const std::string Combinator::DBNAME = "testdb";

void printResponse(sql::ResultSet *raw_results)
{
  std::shared_ptr<sql::ResultSet> results(raw_results);
  while (results->next()) {
    std::cout << "id: " << results->getString("id") << ", "
              << "label: " << results->getString("label")
              << std::endl;
  }
}

void Combinator::run(int argc, char *argv[])
{
  auto driver = sql::mysql::get_mysql_driver_instance();
  std::shared_ptr<sql::Connection> con(
    driver->connect("tcp://127.0.0.1:3306", "root", "hogehoge"));
  std::shared_ptr<sql::Statement> statement(con->createStatement());

  statement->execute(std::string("use ") + DBNAME);
  statement->execute("insert into test (id, label) values (1, 'x')");

  printResponse(statement->executeQuery("select * from test"));
}
