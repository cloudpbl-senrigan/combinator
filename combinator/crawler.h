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

#include "database.h"

namespace senrigan
{

class Crawler
{
public:
  Crawler(std::shared_ptr<Database> database);
  void crawl();
  bool isArrivedNewData();

private:
  std::shared_ptr<Database> database_;
};

}
