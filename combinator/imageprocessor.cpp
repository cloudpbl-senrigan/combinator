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
vector<shared_ptr<Image>> ImageProcessor::process(
    const vector<shared_ptr<Image>>& input_nwes_image)
{
  vector<shared_ptr<Image>> output_nwes_image;

  // Copy to '/tmp'
  for (auto image : input_nwes_image) {
    string filename = basename(image->path());
    string out_path = string("/tmp/") + filename;
    auto out_image = image->copyTo(out_path);
    output_nwes_image.push_back(out_image);
  }

  return output_nwes_image;
}
