/* 
 * imageprocessor.cpp
 * 
 * Author:   Makoto Shimazu <makoto.shimaz@gmail.com>
 * URL:      https://amiq11.tumblr.com               
 * License:  MIT License                             
 * Created:  2014-12-22                                  
 *  
 */

#include "imageprocessor.h"

#include "image.h"

using namespace senrigan;
using namespace std;


static string basename(const string& path) {
    return path.substr(path.find_last_of('/') + 1);
}

// static
map<ImageProcessor::Direction, shared_ptr<Image>> ImageProcessor::process(
    const map<ImageProcessor::Direction, shared_ptr<Image>> input_nesw_image)
{
  map<ImageProcessor::Direction, shared_ptr<Image>> output_nesw_image;

  // Copy to '/tmp'
  for (auto image_pair : input_nesw_image) {
    auto image = image_pair.second;
    string filename = basename(image->path());
    string out_path = string("/tmp/") + filename;
    auto out_image = image->copyTo(out_path);
    output_nesw_image[image_pair.first] = out_image;
  }

  return output_nesw_image;
}
