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

#include "position.h"

namespace senrigan
{

class Image
{
public:
  std::shared_ptr<Image> copyTo(std::string path);
  // void toCvMat();
  std::string path() { return path_; }
  int64_t id() { return id_; }
  double theta() { return theta_; }
  bool is_processed() { return is_processed_; }

  static std::shared_ptr<Image> create(int64_t id,
        std::string path,
        const Position& position,
        double theta,
        bool is_processed);
  static std::shared_ptr<Image> create(std::string path,
        const Position& position,
        double theta,
        std::vector<int> src_ids);

private:
  Image(int64_t id,
        std::string path,
        const Position& position,
        double theta,
        std::vector<int> src_ids,
        bool is_processed);

  int64_t id_;
  std::string path_;
  double theta_;
  Position position_;
  std::vector<int> src_ids_;
  bool is_processed_;
};

}
