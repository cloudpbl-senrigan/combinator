/* 
 * image.h
 * 
 * Author:   Makoto Shimazu <makoto.shimaz@gmail.com>
 * URL:      https://amiq11.tumblr.com               
 * License:  MIT License                             
 * Created:  2014-11-28                                  
 *  
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

namespace senrigan
{

class Position;

class Image
{
public:
  std::shared_ptr<Image> copyTo(std::string path);
  // void toCvMat();
  
  std::shared_ptr<Image> create(int id,
        std::string path,
        std::shared_ptr<Position> position,
        double theta,
        bool is_processed);
  std::shared_ptr<Image> create(std::string path,
        std::shared_ptr<Position> position,
        double theta,
        std::vector<int> src_ids);

  std::string path() { return path_; }
  
private:
  Image(int id,
        std::string path,
        std::shared_ptr<Position> position,
        double theta,
        std::vector<int> src_ids,
        bool is_processed);

  int id_;
  std::string path_;
  double theta_;
  std::shared_ptr<Position> position_;
  std::vector<int> src_ids_;
  bool is_processed_;
};

}
