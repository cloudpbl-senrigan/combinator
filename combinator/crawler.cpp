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

#include <iostream>
#include <unistd.h>

using namespace senrigan;
using namespace std;

// TODO: Implement here
Crawler::Crawler(shared_ptr<Database> database) : database_(database)
{
}

vector<shared_ptr<Position>> Crawler::waitUntilNewPlace()
{
  cout << "waiting new data...." << endl;

  cout << "wait for 10s..." << endl;
  sleep(10);
  shared_ptr<Position> position(
      new Position((int64_t)0, (int64_t)0, (int64_t)0, (double)0.0));
  vector<shared_ptr<Position>> positions;
  positions.push_back(position);

  cout << "generated!" << endl;
  return positions;
}
