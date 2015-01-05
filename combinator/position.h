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
#define MESH_WIDTH 1
#define LONGI 0.000010966382364
#define LATIT 0.000008983148616

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

  // TODO: Implement me
  /*
    the origin point is on four corners of meshes
   */
    int64_t x() {
        return (int64_t)(longitude_ / (MESH_WIDTH*LONGI)) + 1;
    };
    int64_t y() {
        return (int64_t)(latitude_ / (MESH_WIDTH*LATIT)) + 1;
    };
    int64_t z() {
        return (int64_t)(height_ / MESH_WIDTH) + 1;
    };
  double longitude() { return longitude_; };
  double latitude() { return latitude_; };
  double height() { return height_; };
  double theta() { return theta_; };

  enum Element {
    X = 1 << 1,
    Y = 1 << 2,
    Z = 1 << 3,
    LONGITUDE = 1 << 4,
    LATITUDE = 1 << 5,
    HEIGHT = 1 << 6,
    THETA = 1 << 7
  };

  std::string toSQLCondition(uint32_t flag)
    {
      std::stringstream sql;
      bool is_first = true;
      if (flag & X) {
        if (is_first)
          is_first = false;
        else
          sql << "and ";
        sql << "x = " << x() << " ";
      }
      if (flag & Y) {
        if (is_first)
          is_first = false;
        else
          sql << "and ";
        sql << "y = " << y() << " ";
      }
      if (flag & Z) {
        if (is_first)
          is_first = false;
        else
          sql << "and ";
        sql << "z = " << z() << " ";
      }
      if (flag & LONGITUDE) {
        if (is_first)
          is_first = false;
        else
          sql << "and ";
        sql << "longitude = " << std::setprecision(7) << longitude() << " ";
      }
      if (flag & LATITUDE) {
        if (is_first)
          is_first = false;
        else
          sql << "and ";
        sql << "latitude = " << std::setprecision(7) << latitude() << " ";
      }
      if (flag & HEIGHT) {
        if (is_first)
          is_first = false;
        else
          sql << "and ";
        sql << "height = " << std::setprecision(7) << height() << " ";
      }
      if (flag & THETA) {
        if (is_first)
          is_first = false;
        else
          sql << "and ";
        sql << "theta = " << std::setprecision(7) << theta() << " ";
      }
      return sql.str();
    }
  std::string toString()
    {
      std::stringstream str;
      str << "<Position: "
          << "longitude = " << std::setprecision(7) << longitude_ << ", "
          << "latitude = " << std::setprecision(7) << latitude_ << ", "
          << "height = " << std::setprecision(7) << height_ << ", "
          << "theta = " << std::setprecision(7) << theta_
          << ">";
      return str.str();
    }

private:
  double longitude_, latitude_, height_, theta_;
};

}; // namespace senrigan
