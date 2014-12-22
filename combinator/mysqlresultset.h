/* 
 * mysqlresultset.h
 * 
 * Author:   Makoto Shimazu <makoto.shimaz@gmail.com>
 * URL:      https://amiq11.tumblr.com               
 * License:  MIT License                             
 * Created:  2014-11-26                                  
 *  
 */

#pragma once

#include <memory>
#include <string>

#include <cppconn/resultset.h>

#include "resultset.h"

namespace senrigan
{

class MySQLResultSet : public ResultSet
{
public:
  MySQLResultSet(sql::ResultSet *raw_results);
  bool next() override { return results_->next(); }
  int64_t rowsCount() override
    {
      return results_->rowsCount();
    }
  bool getBoolean(const std::string &key) override
    {
      return results_->getBoolean(key);
   }
  int32_t getInt(const std::string &key) override
    {
      return results_->getInt(key);
    }
  std::string getString(const std::string &key) override
    {
      return results_->getString(key);
    }

private:
  std::shared_ptr<sql::ResultSet> results_;
};

} // namespace senrigan
