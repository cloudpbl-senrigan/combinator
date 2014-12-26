/* 
 * resultset.h
 * 
 * Author:   Makoto Shimazu <makoto.shimaz@gmail.com>
 * URL:      https://amiq11.tumblr.com               
 * License:  MIT License                             
 * Created:  2014-11-26                                  
 *  
 */

#pragma once

#include <string>

namespace senrigan
{

class ResultSet
{
public:
  virtual bool next() = 0;
  virtual int64_t rowsCount() = 0;
  virtual bool getBoolean(const std::string &key) = 0;
  bool getBoolean(const char *key) { return getBoolean(std::string(key)); }
  virtual double getDouble(const std::string &key) = 0;
  double getDouble(const char *key) { return getDouble(std::string(key)); }
  virtual int32_t getInt(const std::string &key) = 0;
  int32_t getInt(const char *key) { return getInt(std::string(key)); }
  virtual std::string getString(const std::string &key) = 0;
  std::string getString(const char *key) { return getString(std::string(key)); }
};

} // namespace senrigan
