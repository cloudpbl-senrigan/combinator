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

#include <memory>
#include <vector>


namespace senrigan
{

class Database;
class Image;

class ImageProcessor
{
public:
  ImageProcessor() {};
  std::vector<std::shared_ptr<Image>> process(
      const std::vector<std::shared_ptr<Image>>& input_nwes_image);
};

}; // namespace senrigan
