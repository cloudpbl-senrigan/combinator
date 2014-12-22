/* 
 * crawler.h
 * 
 * Author:   Makoto Shimazu <makoto.shimaz@gmail.com>
 * URL:      https://amiq11.tumblr.com               
 * License:  MIT License                             
 * Created:  2014-11-28                                  
 *  
 */

#pragma once

#include <memory>
#include <vector>

namespace senrigan
{

class Database;
class Position;
  
class Crawler
{
public:
  Crawler(std::shared_ptr<Database> database);

  std::vector<std::shared_ptr<Position>> waitUntilNewPlace();

private:
  std::shared_ptr<Database> database_;
};

}
