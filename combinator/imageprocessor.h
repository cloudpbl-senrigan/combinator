/* 
 * imageprocessor.h
 * 
 * Author:   Makoto Shimazu <makoto.shimaz@gmail.com>
 * URL:      https://amiq11.tumblr.com               
 * License:  MIT License                             
 * Created:  2014-12-22                                  
 *  
 */

#pragma once

#include <map>
#include <memory>
#include <string>

#include <yaml-cpp/yaml.h>

namespace senrigan
{

class Database;
class Image;

class ImageProcessor
{
public:
  enum Direction {
    NORTH,
    SOUTH,
    WEST,
    EAST
  };

  ImageProcessor(const YAML::Node& config);
  std::map<Direction, std::shared_ptr<Image>> process(
      const std::map<Direction, std::shared_ptr<Image>> input_nesw_image);

private:
  std::string out_dir_;
};

}; // namespace senrigan
