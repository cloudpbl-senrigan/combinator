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

#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <utility>

namespace senrigan {

class Position {
public:
  // TODO: Implement me
  // Position(int64_t _x, int64_t _y, int64_t _z, double _theta = 0.0) :
  //   longitude_(_x), latitude_(_y), height_(_z), theta_(_theta) {};
  Position(double _longitude,
           double _latitude,
           double _height,
           double _theta = 0.) :
    longitude_(_longitude),
    latitude_(_latitude),
    height_(_height),
    theta_(_theta) {};

  /*
    the origin point is on four corners of meshes
   */
  int64_t x() const { return to_x(longitude_); }
  int64_t y() const { return to_y(latitude_); }
  int64_t z() const { return to_z(height_); }
  double longitude() const { return longitude_; }
  double latitude() const { return latitude_; }
  double height() const { return height_; }
  double theta() const { return theta_; }

  // Utilities
  // Return a pair of (lower bound, higher bound)
  std::pair<double, double> range_longitude() const;
  std::pair<double, double> range_latitude() const;
  std::pair<double, double> range_height() const;

  // 
  enum Element {
    X = 1 << 1,
    Y = 1 << 2,
    Z = 1 << 3,
    LONGITUDE = 1 << 4,
    LATITUDE = 1 << 5,
    HEIGHT = 1 << 6,
    THETA = 1 << 7
  };

  // [[flag]] is OR-ed [[Element]] enum
  std::string toSQLCondition(uint32_t flag) const;
  std::string toString() const;

private:
  double longitude_, latitude_, height_, theta_;


  // Converters
  static int64_t to_x(double longitude);
  static int64_t to_y(double latitude);
  static int64_t to_z(double height);

  static double to_longitude(int64_t x); // calculate the lower bound of x
  static double to_latitude(int64_t y); // calculate the lower bound of y
  static double to_height(int64_t z); // calculate the lower bound of z

  // Constants
  static const double mesh_scale_;
  static const double longitude_unit_size_; // Unit: [deg/m]
  static const double latitude_unit_size_; // Unit: [deg/m]
  static const double height_unit_size_; // Unit: [m/m]
};

}; // namespace senrigan


