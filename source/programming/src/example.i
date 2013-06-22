%module example
%{
#include "example.h"
%}

class caller{
public:
  caller();
  ~caller();
  int run();
};
