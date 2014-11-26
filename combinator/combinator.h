/* 
 * combinator.h
 * 
 * Author:   Makoto Shimazu <makoto.shimaz@gmail.com>
 * URL:      https://amiq11.tumblr.com               
 * License:  MIT License                             
 * Created:  2014-11-26                                  
 *  
 */

#pragma once

#include <string>

class Combinator
{
public:
  void run(int argc, char *argv[]);

private:
  static const std::string DBNAME;
};
