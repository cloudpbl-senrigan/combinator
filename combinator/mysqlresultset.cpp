/* 
 * mysqlresultset.cpp
 * 
 * Author:   Makoto Shimazu <makoto.shimaz@gmail.com>
 * URL:      https://amiq11.tumblr.com               
 * License:  MIT License                             
 * Created:  2014-11-26                                  
 *  
 */

#include "mysqlresultset.h"

#include "debug.h"

using namespace senrigan;

MySQLResultSet::MySQLResultSet(sql::ResultSet *raw_results) :
  results_(raw_results)
{
  DCHECK(raw_results != nullptr);
}
