/* 
 * image.cpp
 * 
 * Author:   Makoto Shimazu <makoto.shimaz@gmail.com>
 * URL:      https://amiq11.tumblr.com               
 * License:  MIT License                             
 * Created:  2014-12-22                                  
 *  
 */

#include "image.h"

#include <fstream>

#include <glog/logging.h>

using namespace senrigan;
using namespace std;


Image::Image(int64_t id,
             string path,
             const Position& position,
             double theta,
             vector<int> src_ids,
             bool is_processed,
             string created_at) :
  id_(id),
  path_(path),
  position_(position),
  theta_(theta),
  src_ids_(src_ids),
  is_processed_(is_processed),
  created_at_(created_at)
{
}

shared_ptr<Image> Image::create(int64_t id,
                                string path,
                                const Position& position,
                                double theta,
                                bool is_processed,
                                string created_at)
{
  shared_ptr<Image> image(
      new Image(
          id, path, position, theta, vector<int> (), is_processed, created_at));
  return image;
}

shared_ptr<Image> Image::create(string path,
                                const Position& position,
                                double theta,
                                vector<int> src_ids,
                                string created_at)
{
  shared_ptr<Image> image(
      new Image(-1, path, position, theta, src_ids, false, created_at));
  return image;
}

shared_ptr<Image> Image::copyTo(string path)
{
  LOG(INFO) << "copyTo: " << path;

  // Copy image file
  ifstream src(path_, ios::binary);
  ofstream dst(path, ios::trunc | ios::binary);
  dst << src.rdbuf();

  // Create [[Image]] object
  // TODO: not created_at but current time
  shared_ptr<Image> dst_image(
      new Image(
          id_, path, position_, theta_, src_ids_, is_processed_, created_at_));
  return dst_image;
}

