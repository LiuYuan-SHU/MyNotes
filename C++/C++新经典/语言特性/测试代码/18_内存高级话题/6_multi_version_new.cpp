/*
 * Copyright 2022 Yuan Liu
 */

#include <cstddef>
#include <cstdlib>

using std::malloc;

class Test {
private:
  int i;

public:
  void *operator new(size_t size, int val1, int val2) {
    return malloc(sizeof(Test));
  }
};

int main() { Test *pTest = new (1, 2) Test; }
