#pragma once

class Hoge
{
public:
  Hoge(int n) { n_ = n; }
  int number() { return n_; }
private:
  int n_;
};
