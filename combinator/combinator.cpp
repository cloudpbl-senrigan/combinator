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

#include "cmdline.h"
#include "crawler.h"
#include "image.h"
#include "mysqldatabase.h"
#include "processor.h"

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
  Crawler crawler(database);
  Processor processor(database);

  // Crawl
  crawler.crawl();
  cout << "isArrivedNewData: " << crawler.isArrivedNewData() << endl;
  // Process
  vector<Image> images;
  images.push_back(Image());
  images = processor.process(images);

  // Print the number of elements in [[images]] (for test)
  int i = 0;
  for (auto image : images) {
    cout << "image[" << i++ << "]" << endl;
  }

  // Execute query (for test)
  database->open();
  ResultSet results = database->execute("select count(*) as c from test;");
  database->close();
  if (results.next()) {
    cout << "'select count(*) as c from test': " << results.getInt("c") << endl;
  }
  return 0;
}
