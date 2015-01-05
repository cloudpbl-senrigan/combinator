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
  int64_t id() const { return id_; }
  std::string path() const { return path_; }
  double theta() const { return theta_; }
  const Position& position() const { return position_; }
  const std::vector<int>& src_ids() const { return src_ids_; }
  bool is_processed() const { return is_processed_; }
  const std::string& created_at() const { return created_at_; }

  static std::shared_ptr<Image> create(int64_t id,
                                       std::string path,
                                       const Position& position,
                                       double theta,
                                       bool is_processed,
                                       std::string created_at);
  static std::shared_ptr<Image> create(std::string path,
                                       const Position& position,
                                       double theta,
                                       std::vector<int> src_ids,
                                       std::string created_at);

private:
  Image(int64_t id,
        std::string path,
        const Position& position,
        double theta,
        std::vector<int> src_ids,
        bool is_processed,
        std::string created_at);

  int64_t id_;
  std::string path_;
  double theta_;
  Position position_;
  std::vector<int> src_ids_;
  bool is_processed_;
  std::string created_at_;
};

}
