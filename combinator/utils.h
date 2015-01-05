/* 
 * utils.h
 * 
 * Author:   Makoto Shimazu <makoto.shimaz@gmail.com>
 * URL:      https://amiq11.tumblr.com               
 * License:  MIT License                             
 * Created:  2015-01-05                                  
 *  
 */

#pragma once

#include <string>

namespace senrigan
{

// Default: 2014-01-05 23:00:01
std::string current_datetime(std::string format = "%F %H:%M:%S");

};
