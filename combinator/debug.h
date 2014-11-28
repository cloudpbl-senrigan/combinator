/* 
 * debug.h
 * 
 * Author:   Makoto Shimazu <makoto.shimaz@gmail.com>
 * URL:      https://amiq11.tumblr.com               
 * License:  MIT License                             
 * Created:  2014-11-26                                  
 *  
 */

#pragma once

#ifdef DEBUG
#  include <cassert>
#  define DCHECK(expr) assert(expr)
#else
#  define DCHECK(expr)
#endif
