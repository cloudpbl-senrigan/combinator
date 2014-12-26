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

namespace senrigan
{

class Database;
class Image;

class ImageProcessor
{
public:
  ImageProcessor() {};
  std::map<std::string, std::shared_ptr<Image>> process(
      const std::map<std::string, std::shared_ptr<Image>> input_nesw_image);
};

}; // namespace senrigan
