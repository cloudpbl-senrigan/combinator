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
  virtual bool next() { return false; }
  virtual std::string getString(const std::string &key) { return ""; }
  std::string getString(const char *key) { return getString(key); }
  virtual int32_t getInt(const std::string &key) { return 0; }
  int32_t getInt(const char *key) { return getInt(std::string(key)); }
  virtual bool getBoolean(const std::string &key) { return true; }
  bool getBoolean(const char *key) { return getBoolean(key); }
};

} // namespace senrigan
