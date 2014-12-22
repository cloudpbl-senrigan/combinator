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

#include <iostream>

#include "database.h"
#include "position.h"
#include "image.h"
#include "imageprocessor.h"

using namespace senrigan;
using namespace std;


// TODO: position should wrap in the center of each cell
Cell::Cell(shared_ptr<Database> database, shared_ptr<Position> position) :
  database_(database),
  position_(*position)
{
  // TODO: pick images up which are related to this cell and store to
  // [[images_]]
}

// static
shared_ptr<Cell> Cell::create(
    shared_ptr<Database> database, shared_ptr<Position> position)
{
  shared_ptr<Cell> cell(new Cell(database, position));
  return cell;
}

void Cell::update(shared_ptr<ImageProcessor> processor)
{
  // TODO: implement here
  cout << "Cell::update!!!!!" << endl;
}
