/* 
 * cell.cpp
 * 
 * Author:   Makoto Shimazu <makoto.shimaz@gmail.com>
 * URL:      https://amiq11.tumblr.com               
 * License:  MIT License                             
 * Created:  2014-12-18                                  
 *  
 */

#include "cell.h"

#include <glog/logging.h>

#include "database.h"
#include "position.h"
#include "image.h"
#include "imageprocessor.h"

using namespace senrigan;
using namespace std;


// TODO: position should wrap in the center of each cell
Cell::Cell(shared_ptr<Database> database,
           shared_ptr<Position> position,
           const YAML::Node& config) :
  database_(database),
  position_(*position)
{

  // Check if configuration is set
  if (!config["dest_dir"])
    throw "Config file msut set the parameter: {cell: {dest_dir:}}";

  // Set a destination path
  dest_dir_ = config["dest_dir"].as<string>();

  LOG(INFO) << position->toString() << endl;

  // TODO: yaw will be renamed to theta or direction
  const string pickup_sql =
    string("select image_id, path, latitude, longitude, "
           "height, yaw, converted from image_master_table where ") +
    position->toSQLCondition(Position::LATITUDE |
                             Position::LONGITUDE |
                             Position::HEIGHT);
  LOG(INFO) << pickup_sql << endl;
  // TODO: pick images up which are related to this cell and store to
  // [[images_]]
  database_->open();
  shared_ptr<ResultSet> result = database_->execute(pickup_sql);
  database_->close();

  while(result->next()) {
    int32_t image_id = result->getInt("image_id");
    string path = result->getString("path");
    double theta = result->getDouble("yaw");
    LOG(INFO) << "---- Query Result ----" << endl
              << "image_id: " << image_id << endl
              << "path: " << path << endl
              << "latitude: "  << result->getDouble("latitude") << endl
              << "longitude: "  << result->getDouble("longitude") << endl
              << "height: "  << result->getDouble("height") << endl
              << "theta: "  << theta << endl;
    auto image = Image::create(
        image_id, path, position_, theta, result->getBoolean("converted"));
    images_.push_back(image);
  }
}

// static
shared_ptr<Cell> Cell::create(shared_ptr<Database> database,
                              shared_ptr<Position> position,
                              const YAML::Node& config)
{
  shared_ptr<Cell> cell(new Cell(database, position, config));
  return cell;
}

void Cell::update(shared_ptr<ImageProcessor> processor)
{
  // TODO: implement here
  LOG(INFO) << "Cell::update(): started!" << endl;
  database_->open();
  for (auto image : images_) {
    if (!image->is_processed()) {
      stringstream sql;
      sql << "update image_master_table set converted = True where image_id = "
          << image->id();
      LOG(INFO) << sql.str() << endl;
      database_->executeUpdate(sql.str());
      LOG(INFO) << "image_id = " << image->id() << endl;
    }
    database_->close();
  }
  LOG(INFO) << "Cell::update(): finished!" << endl;;
}
