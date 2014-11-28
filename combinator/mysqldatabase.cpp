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

#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <mysql_connection.h>
#include <mysql_driver.h>

using namespace senrigan;
using namespace std;

const string MySQLDatabase::DBNAME = "testdb";

static string dirname(const string& path)
{
    return path.substr(0, path.find_last_of('/'));
}

static void printResponse(sql::ResultSet *raw_results)
{
  shared_ptr<sql::ResultSet> results(raw_results);
  while (results->next()) {
    cout << "id: " << results->getString("id") << ", "
         << "label: " << results->getString("label")
         << endl;
  }
}

MySQLDatabase::MySQLDatabase(const std::string &yaml_path)
{
  // TODO: Settings must be read from yaml file
  auto driver = sql::mysql::get_mysql_driver_instance();
  shared_ptr<sql::Connection> connection(
    driver->connect("tcp://127.0.0.1:3306", "root", "hogehoge"));
  shared_ptr<sql::Statement> statement(connection->createStatement());
  connection_ = connection;
  statement_ = statement;
}

bool MySQLDatabase::open()
{
  // TODO: Implement here
  return true;
}

void MySQLDatabase::close()
{
  // TODO: Implement here
}

ResultSet MySQLDatabase::execute(const std::string &sql)
{
  // TODO: Implement here; this is just a placeholder
  statement_->execute(string("use ") + DBNAME);
  statement_->execute("insert into test (id, label) values (1, 'x')");
  statement_->executeQuery("select * from test");
  return ResultSet();
}
