//! g++ -o main.bin main.cpp -W -Wall -std=c++0x

#include <iostream>
#include <memory>

#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <mysql_connection.h>
#include <mysql_driver.h>

#define EXAMPLE_DB "testdb"

int main(int argc, char* argv[])
{
  sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
  std::shared_ptr<sql::Connection> con(driver->connect("tcp://127.0.0.1:3306", "root", "hogehoge"));
  std::shared_ptr<sql::Statement> statement(con->createStatement());

  statement->execute("use " EXAMPLE_DB);
  statement->execute("insert into test (id, label) values (2, 'b')");
  
  return 0;
}
