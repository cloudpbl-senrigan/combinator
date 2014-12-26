/* 
 * combinator.cpp
 * 
 * Author:   Makoto Shimazu <makoto.shimaz@gmail.com>
 * URL:      https://amiq11.tumblr.com               
 * License:  MIT License                             
 * Created:  2014-11-26                                  
 *  
 */

#include "combinator.h"

#include <iostream>
#include <memory>
#include <vector>

#include <glog/logging.h>
#include <yaml-cpp/yaml.h>

#include "cell.h"
#include "cmdline.h"
#include "crawler.h"
#include "image.h"
#include "mysqldatabase.h"
#include "imageprocessor.h"

using namespace senrigan;
using namespace std;

int Combinator::run(int argc, const char * const argv[])
{
  google::InitGoogleLogging(argv[0]);
  cmdline::parser parser;
  parser.add<string>(
      "config", 'c',
      "path to configurations in yaml",
      false,
      string("config/config.yml"));
  parser.add("help", 'h', "print help");
  
  if (!parser.parse(argc, argv) || parser.exist("help")) {
    cerr << parser.error_full() << parser.usage();
    return 1;
  }

  // Parse configuration file
  string yaml_path = parser.get<string>("config");
  LOG(INFO) << "yaml: " << yaml_path << endl;
  YAML::Node config = YAML::LoadFile(yaml_path);
  if (!config["database"] || !config["cell"])
    throw "Config file must set the parameters: {database: {...}, cell: {...}}";

  // Configure each components
  shared_ptr<Database> database(new MySQLDatabase(config["database"]));
  shared_ptr<Crawler> crawler(new Crawler(database));
  shared_ptr<ImageProcessor> processor(new ImageProcessor());

  // Main Loop
  // TODO: Move to another thread
  while (1) {
    LOG(INFO) << "Crawler::waitUntilNewPlace()" << endl;
    auto positions = crawler->waitUntilNewPlace();
    for (auto position : positions) {
      LOG(INFO) << "Cell::create()" << endl;
      auto cell = Cell::create(database, position, config["cell"]);
      LOG(INFO) << "Cell::update()" << endl;
      cell->update(processor);
    }
  }

  return 0;
}
