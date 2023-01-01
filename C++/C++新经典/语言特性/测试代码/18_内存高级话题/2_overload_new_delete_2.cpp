/*
 * Copyright 2022 Yuan Liu
 */
#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

class Test {
public:
  Test() : _val(0) { cout << "Test::" << __func__ << endl; }
  ~Test() { cout << "Test::" << __func__ << endl; }

  static void *operator new(size_t size) {
    cout << "Test::" << __func__ << endl;

    return malloc(size);
  }

  static void operator delete(void *p) {
    cout << "Test::" << __func__ << endl;

    free(p);
  }

  static void *operator new[](size_t size) {
    cout << "Test::" << __func__ << endl;
    Test *tmp = reinterpret_cast<Test *>(malloc(size));
    return tmp;
  }

  static void operator delete[](void *p) {
    cout << "Test::" << __func__ << endl;
    free(p);
  }

private:
  int _val;
};

int main() {
  // call overloaded new/delete
  Test *test1 = new Test[3];
  delete[] test1;

  // call global new/delete
  Test *test2 = ::new Test[3];
  ::delete[] test2;
}
