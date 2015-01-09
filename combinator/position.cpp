/* 
 * position.cpp
 * 
 * Author:   Makoto Shimazu <makoto.shimaz@gmail.com>
 * URL:      https://amiq11.tumblr.com               
 * License:  MIT License                             
 * Created:  2015-01-08                                  
 *  
 */

#include "position.h"

#include <math.h>

using namespace senrigan;
using namespace std;

// static
const double Position::mesh_scale_ = 1.0;
// static
const double Position::longitude_unit_size_ = 0.000010966382364;
// static
const double Position::latitude_unit_size_ = 0.000008983148616;
// static
const double Position::height_unit_size_ = 1.0;

// static
int64_t Position::to_x(double longitude) {
  return floor(longitude  / (mesh_scale_ * longitude_unit_size_));
}

// static
int64_t Position::to_y(double latitude) {
  return floor(latitude / (mesh_scale_ * latitude_unit_size_));
};

// static
int64_t Position::to_z(double height) {
  return floor(height / (mesh_scale_ * height_unit_size_));
}

// static
double Position::to_longitude(int64_t x)
{
  return mesh_scale_ * longitude_unit_size_ * x;
}

// static
double Position::to_latitude(int64_t y)
{
  return mesh_scale_ * latitude_unit_size_ * y;
}

// static
double Position::to_height(int64_t z)
{
  return mesh_scale_ * height_unit_size_ * z;
}

pair<double, double> Position::range_longitude() const
{
  double lower = to_longitude(x());
  double higher = to_longitude(x()+1);
  return pair<double, double>(lower, higher);
}

pair<double, double> Position::range_latitude() const
{
  double lower = to_latitude(y());
  double higher = to_latitude(y()+1);
  return pair<double, double>(lower, higher);
}

pair<double, double> Position::range_height() const
{
  double lower = to_height(z());
  double higher = to_height(z()+1);
  return pair<double, double>(lower, higher);
}

static inline void maybe_append_add_operator(bool& is_first, stringstream& sql)
{
  if (is_first)
    is_first = false;
  else
    sql << "and ";
}

string Position::toSQLCondition(uint32_t flag) const
{
  stringstream sql;
  bool is_first = true;

  // Set format
  // sql << setprecision(7);
  
  if (flag & X) {
    maybe_append_add_operator(is_first, sql);
    sql << "x = " << x() << " ";
  }
  if (flag & Y) {
    maybe_append_add_operator(is_first, sql);
    sql << "y = " << y() << " ";
  }
  if (flag & Z) {
    maybe_append_add_operator(is_first, sql);
    sql << "z = " << z() << " ";
  }
  if (flag & LONGITUDE) {
    maybe_append_add_operator(is_first, sql);
    auto range = range_longitude();
    sql << "longitude >= " << range.first << " and ";
    sql << "longitude < " << range.second << " ";
  }
  if (flag & LATITUDE) {
    maybe_append_add_operator(is_first, sql);
    auto range = range_latitude();
    sql << "latitude >= " << range.first << " and ";
    sql << "latitude < " << range.second << " ";
  }
  if (flag & HEIGHT) {
    maybe_append_add_operator(is_first, sql);
    auto range = range_height();
    sql << "height >= " << range.first << " and ";
    sql << "height < " << range.second << " ";
  }
  if (flag & THETA) {
    maybe_append_add_operator(is_first, sql);
    sql << "theta = " << theta() << " ";
  }
  return sql.str();
}

string Position::toString() const
{
  stringstream str;
  // Set format
  str << setprecision(7);
  
  str << "<Position: "
      << "longitude = " << longitude_ << ", "
      << "latitude = " << latitude_ << ", "
      << "height = " << height_ << ", "
      << "theta = " << theta_
      << ">";
  return str.str();
}

