/* 
 * crawler.cpp
 * 
 * Author:   Makoto Shimazu <makoto.shimaz@gmail.com>
 * URL:      https://amiq11.tumblr.com               
 * License:  MIT License                             
 * Created:  2014-11-28                                  
 *  
 */

#include "crawler.h"

#include <glog/logging.h>
#include <unistd.h>

#include "database.h"
#include "position.h"

using namespace senrigan;
using namespace std;

Crawler::Crawler(shared_ptr<Database> database) : database_(database)
{
}

vector<shared_ptr<Position>> Crawler::waitUntilNewPlace()
{
  LOG(INFO) << "waiting new data...." << endl;
  vector<shared_ptr<Position>> positions;

  // TODO: yaw will be changed
  const string target_position_sql =
      "select latitude, longitude, height "
      "from image_master_table where converted = False "
      "group by latitude, longitude, height";

  database_->open();

  auto result = database_->execute(target_position_sql);
  int64_t n_rows = result->rowsCount();
  LOG(INFO) << "n_rows: " << n_rows << endl;

  // When nothing was found
  while (n_rows == 0) {
    LOG(INFO) << "wait for 10s..." << endl;
    sleep(10);
    // Search
    result = database_->execute(target_position_sql);
    n_rows = result->rowsCount();
    LOG(INFO) << "n_rows: " << n_rows << endl;
  }

  // When some updates were found
  while (result->next()) {
    double longitude = result->getDouble("longitude");
    double latitude = result->getDouble("latitude");
    double height = result->getDouble("height");
    shared_ptr<Position> position(new Position(longitude, latitude, height));
    positions.push_back(position);
  }

  database_->close();
  LOG(INFO) << "generated!: num = " << positions.size() << endl;
  return positions;
}
