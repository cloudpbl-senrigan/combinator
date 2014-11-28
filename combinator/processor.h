/* 
 * processor.h
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

#include "database.h"
#include "image.h"

namespace senrigan
{

class Processor
{
public:
  Processor(std::shared_ptr<Database> database);
  std::vector<Image> process(std::vector<Image> images);

private:
  std::shared_ptr<Database> database_;
  static const std::string DBNAME;
};

} // namespace senrigan
