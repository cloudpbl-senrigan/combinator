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

#include <map>

#include <glog/logging.h>

#include "database.h"
#include "position.h"
#include "image.h"
#include "imageprocessor.h"
#include "utils.h"

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

  // Retrieve images related to this position
  // TODO: yaw will be renamed to theta or direction
  const string pickup_sql =
    string("select image_id, path, latitude, longitude, "
           "height, yaw, converted, created_date "
           "from image_master_table where ") +
    position->toSQLCondition(Position::LATITUDE |
                             Position::LONGITUDE |
                             Position::HEIGHT);
  LOG(INFO) << pickup_sql << endl;
  // TODO: pick images up which are related to this cell and store to
  // [[images_]]
  database_->open();
  shared_ptr<ResultSet> result = database_->execute(pickup_sql);
  database_->close();

  // Store each image information into [[Image]] container
  while(result->next()) {
    int32_t image_id = result->getInt("image_id");
    string path = result->getString("path");
    double theta = result->getDouble("yaw");
    string created_at = result->getString("created_date");
    LOG(INFO) << "---- Query Result ----" << endl
              << "image_id: " << image_id << endl
              << "path: " << path << endl
              << "latitude: "  << result->getDouble("latitude") << endl
              << "longitude: "  << result->getDouble("longitude") << endl
              << "height: "  << result->getDouble("height") << endl
              << "theta: "  << theta << endl
              << "created_at: "  << created_at << endl;
    auto image = Image::create(image_id, path, position_, theta,
                               result->getBoolean("converted"), created_at);
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

  // Search the latest four images
  map<ImageProcessor::Direction, shared_ptr<Image>> nesw_images;
  for (auto image : images_) {
    ImageProcessor::Direction key;
    if (image->theta() > 315 || image->theta() < 45)
      key = ImageProcessor::NORTH;
    else if (image->theta() < 135)
      key = ImageProcessor::EAST;
    else if (image->theta() < 225)
      key = ImageProcessor::SOUTH;
    else
      key = ImageProcessor::WEST;
    if (!nesw_images[key] ||
        nesw_images[key]->created_at() < image->created_at())
      nesw_images[key] = image;
  }

  LOG(INFO) << "start processing!";
  auto processed_images = processor->process(nesw_images);
  LOG(INFO) << "processed!";

  // Update Database
  database_->open();
  database_->executeUpdate("start transaction");

  // Mark as processed
  for (auto image_pair : nesw_images) {
    auto image = image_pair.second;
    if (!image->is_processed()) {
      stringstream sql;
      sql << "update image_master_table set converted = True where image_id = "
          << image->id();
      LOG(INFO) << sql.str() << endl;
      database_->executeUpdate(sql.str());
      LOG(INFO) << "image_id = " << image->id() << endl;
    }
  }

  // Insert information of new images
  for (auto image_pair : processed_images) {
    stringstream sql;
    sql << "insert into image_processed_tables "
           "(path, x, y, z, create_date, taken_date, "
           "theta, height, width, source_image_ids) "
           "values ";
    auto image = image_pair.second;
    LOG(INFO) << "id: " << image->id() << ", "
              << "path: " << image->path();
    sql << "("
        << "\"" << image->path() << "\", "
        << image->position().x() << ", "
        << image->position().y() << ", "
        << image->position().z() << ", "
        << "\"" << current_datetime() << "\", "
        << "\"" << image->created_at() << "\", "
        << image->theta() << ", "
        << 0 << ", "
        << 0 << ", ";
    // TODO: source_image_ids should be an array of integer
    int64_t src_id = -1;
    if (!image->src_ids().empty()) {
      src_id = image->src_ids()[0];
      // sql << "(";
      // for (auto id : image->src_ids()) {
      //   sql << id << ", ";
      // }
      // sql << ")";
    }
    if (src_id > 0)
      sql << src_id;
    else
      sql << "null";

    sql << ")";
    sql << "on duplicate key update "
        << "path = \"" << image->path() << "\", "
        << "create_date = \"" << current_datetime() << "\", "
        << "source_image_ids = ";
    if (src_id > 0)
      sql << src_id;
    else
      sql << "null";

    // Execute SQL
    database_->executeUpdate(sql.str());
  }

  // Finalize Database
  database_->executeUpdate("commit");
  database_->close();

  LOG(INFO) << "Cell::update(): finished!" << endl;
}
