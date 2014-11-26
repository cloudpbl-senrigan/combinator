//! g++ -o main.bin main.cpp -W -Wall -std=c++0x

#include "combinator.h"

int main(int argc, char* argv[])
{
  Combinator combinator();
  combinator.run(argc, argv);
  return 0;
}
