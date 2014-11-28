//! g++ -o main.bin main.cpp -W -Wall -std=c++0x

#include "combinator.h"

int main(int argc, char* argv[])
{
  senrigan::Combinator combinator;
  return combinator.run(argc, argv);
}
