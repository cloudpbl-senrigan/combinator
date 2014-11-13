//! g++ -o main.bin main.cpp -W -Wall -std=c++0x

#include <iostream>

#include <hoge.h>

int main(int argc, char* argv[])
{
  Hoge h(100);
  for (int i = 0; i < argc; i++) {
    std::cout << i << ": " << argv[i] << std::endl;
  }
  std::cout << h.number() << std::endl;
  return 0;
}
