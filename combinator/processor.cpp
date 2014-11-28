/* 
 * processor.cpp
 * 
 * Author:   Makoto Shimazu <makoto.shimaz@gmail.com>
 * URL:      https://amiq11.tumblr.com               
 * License:  MIT License                             
 * Created:  2014-11-28                                  
 *  
 */

#include "processor.h"

using namespace senrigan;
using namespace std;

Processor::Processor(std::shared_ptr<Database> database) : database_(database)
{
}

vector<Image> Processor::process(vector<Image> images)
{
  // TODO: Implement here
  database_->open();
  database_->execute("select * from test");
  database_->close();
  return images;
}
