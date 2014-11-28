/* 
 * database.h
 * 
 * Author:   Makoto Shimazu <makoto.shimaz@gmail.com>
 * URL:      https://amiq11.tumblr.com               
 * License:  MIT License                             
 * Created:  2014-11-26                                  
 *  
 */

#pragma once

#include <string>

#include "resultset.h"

namespace senrigan
{

class Database
{
public:
  virtual bool open() = 0;
  virtual void close() = 0;
  virtual ResultSet execute(const std::string &sql) = 0;
};

};
