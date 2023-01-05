/*
 * Copyright 2022 Yuan Liu
 */

#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

#define TO_STRING(str) #str

void *operator new(size_t size) {
  cout << "global new" << endl;
  return malloc(size);
}

void *operator new[](size_t size) {
  cout << "global new[]" << endl;
  return malloc(size);
}

void operator delete(void *phead) {
  cout << "global delete" << endl;
  free(phead);
}

void operator delete[](void *phead) {
  cout << "global delete[]" << endl;
  free(phead);
}

class Test {
public:
  Test() { cout << TO_STRING(Test::) << __func__ << endl; }

  ~Test() { cout << TO_STRING(Test::) << __func__ << endl; }
};

int main() {
  int *pint = new int(12);
  delete pint;

  char *parr = new char[10];
  delete[] parr;

  Test *p = new Test();
  delete p;

  Test *pTest = new Test[3]();
  delete[] pTest;
}
