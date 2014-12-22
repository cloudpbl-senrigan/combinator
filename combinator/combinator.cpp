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
  cmdline::parser parser;
  parser.add<string>(
      "database", 'd',
      "path to database settings in yaml",
      false,
      string("config/database.yml"));
  parser.add("help", 'h', "print help");
  
  if (!parser.parse(argc, argv) || parser.exist("help")) {
    cout << parser.error_full() << parser.usage();
    return 1;
  }

  string yaml_path = parser.get<string>("database");
  cout << "yaml: " << yaml_path << endl;

  // Configure each components
  shared_ptr<Database> database(new MySQLDatabase(yaml_path));
  shared_ptr<Crawler> crawler(new Crawler(database));
  shared_ptr<ImageProcessor> processor(new ImageProcessor());

  // Main Loop
  // Todo: Move to another thread
  while (1) {
    auto positions = crawler->waitUntilNewPlace();
    for (auto position : positions) {
      auto cell = Cell::create(database, position);
      cell->update(processor);
      cout << "updated!" << endl;
    }
  }

  return 0;
}
