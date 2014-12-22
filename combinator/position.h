/* 
 * position.h
 * 
 * Author:   Makoto Shimazu <makoto.shimaz@gmail.com>
 * URL:      https://amiq11.tumblr.com               
 * License:  MIT License                             
 * Created:  2014-12-12                                  
 *  
 */

#pragma once


namespace senrigan {

class Position {
public:
  // TODO: Implement me
  Position(int64_t _x, int64_t _y, int64_t _z, double _theta) :
    longtitude_(_x), latitude_(_y), height_(_z), theta_(_theta) {};
  Position(
      double _longtitude, double _latitude, double _height, double _theta) :
    longtitude_(_longtitude),
    latitude_(_latitude),
    height_(_height),
    theta_(_theta) {};

  // TODO: Implement me
  int64_t x() { return (int64_t)longtitude_; };
  int64_t y() { return (int64_t)latitude_; };
  int64_t z() { return (int64_t)height_; };
  double longtitude() { return longtitude_; };
  double latitude() { return latitude_; };
  double height() { return height_; };
  double theta() { return theta_; };

private:
  double longtitude_, latitude_, height_, theta_;
};

}; // namespace senrigan
