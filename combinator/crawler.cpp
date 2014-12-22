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

#include <iostream>
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
  cout << "waiting new data...." << endl;
  vector<shared_ptr<Position>> positions;

  // TODO: yaw will be changed
  const string target_position_sql =
      "select latitude, longitude, height "
      "from image_master_table where converted = False "
      "group by latitude, longitude, height";

  database_->open();

  int64_t n_rows = 0;
  while (n_rows == 0) {
    // Search
    auto result = database_->execute(target_position_sql);
    n_rows = result->rowsCount();
    cout << "n_rows: " << n_rows << endl;
    // When nothing is found
    if (n_rows == 0) {
      cout << "wait for 10s..." << endl;
      sleep(10);
      continue;
    }

    // When some updates are found
    while (result->next()) {
      int64_t latitude = result->getInt("latitude");
      int64_t longitude = result->getInt("longitude");
      int64_t height = result->getInt("height");
      shared_ptr<Position> position(new Position(latitude, longitude, height));
      positions.push_back(position);
    }
  }

  database_->close();
  cout << "generated!: num = " << positions.size() << endl;
  return positions;
}
