/* 
 * crawler.cpp
 * 
 * Author:   Makoto Shimazu <makoto.shimaz@gmail.com>
 * URL:      https://amiq11.tumblr.com               
 * License:  MIT License                             
 * Created:  2014-11-28                                  
 *  
 */

#include "crawler.h"

using namespace senrigan;
using namespace std;

// TODO: Implement here
Crawler::Crawler(shared_ptr<Database> database) : database_(database)
{
}

void Crawler::crawl()
{
  // TODO: Implement here
}

bool Crawler::isArrivedNewData() {
  // TODO: Implement here
  return false;
}
