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
  virtual std::string getString(std::string &key) { return ""; }
  virtual int32_t getInt(std::string &key) { return 0; }
  virtual bool getBoolean(std::string &key) { return true; }
};

} // namespace senrigan
