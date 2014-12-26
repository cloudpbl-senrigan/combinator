/* 
 * cell.h
 * 
 * Author:   Makoto Shimazu <makoto.shimaz@gmail.com>
 * URL:      https://amiq11.tumblr.com               
 * License:  MIT License                             
 * Created:  2014-12-18                                  
 *  
 */

#pragma once

#include <memory>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "position.h"

namespace senrigan {

class Database;
class Image;
class ImageProcessor;

class Cell {
public:
  void update(std::shared_ptr<ImageProcessor> processor);

  static std::shared_ptr<Cell> create(std::shared_ptr<Database> database,
                                      std::shared_ptr<Position> position,
                                      const YAML::Node& config);

private:
  Cell(std::shared_ptr<Database> database,
       std::shared_ptr<Position> position,
       const YAML::Node& config);

  // TODO: Change the type of container to make it faster to search a image
  std::vector<std::shared_ptr<Image>> images_;
  std::shared_ptr<Database> database_;
  Position position_;
  std::string dest_dir_;
};

};
