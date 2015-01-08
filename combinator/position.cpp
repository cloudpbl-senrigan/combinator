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
  return longitude  / (mesh_scale_ * longitude_unit_size_);
}

// static
int64_t Position::to_y(double latitude) {
  return latitude / (mesh_scale_ * latitude_unit_size_);
};

// static
int64_t Position::to_z(double height) {
  return height / (mesh_scale_ * height_unit_size_);
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

// static
pair<double, double> Position::range_longitude(int64_t x)
{
  double lower = to_longitude(x);
  double higher = to_longitude(x+1);
  return pair<double, double>(lower, higher);
}

// static
pair<double, double> Position::range_latitude(int64_t y)
{
  double lower = to_latitude(y);
  double higher = to_latitude(y+1);
  return pair<double, double>(lower, higher);
}

// static
pair<double, double> Position::range_height(int64_t z)
{
  double lower = to_height(z);
  double higher = to_height(z+1);
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
  std::stringstream sql;
  bool is_first = true;
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
    sql << "longitude = " << std::setprecision(7) << longitude() << " ";
  }
  if (flag & LATITUDE) {
    maybe_append_add_operator(is_first, sql);
    sql << "latitude = " << std::setprecision(7) << latitude() << " ";
  }
  if (flag & HEIGHT) {
    maybe_append_add_operator(is_first, sql);
    sql << "height = " << std::setprecision(7) << height() << " ";
  }
  if (flag & THETA) {
    maybe_append_add_operator(is_first, sql);
    sql << "theta = " << std::setprecision(7) << theta() << " ";
  }
  return sql.str();
}
std::string Position::toString() const
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

