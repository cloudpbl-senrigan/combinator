/* 
 * utils.cpp
 * 
 * Author:   Makoto Shimazu <makoto.shimaz@gmail.com>
 * URL:      https://amiq11.tumblr.com               
 * License:  MIT License                             
 * Created:  2015-01-05                                  
 *  
 */

#include "utils.h"

#include <time.h>

using namespace senrigan;
using namespace std;

string senrigan::current_datetime(string format)
{
  time_t now = time(nullptr);
  const struct tm* tstruct = localtime(&now);
  char buf[80];
  strftime(buf, sizeof(buf), format.c_str(), tstruct);

  return string(buf);
}
