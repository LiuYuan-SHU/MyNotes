/*
 * Copyright 1.17.2023 Liu Yuan
 */
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

#define PRINT_VAR                                                              \
  cout << "tv1: " << tv1 << "\ttv2: " << tv2 << endl;                          \
  cout << string(40, '=') << endl;

template <typename T, typename U> void tfunc(T &tv1, U &tv2) {
  cout << "template <typename T, typename U>" << endl;
  cout << "void tfunc(T& tv1, U& tv2)" << endl;
  PRINT_VAR;
}

template <> void tfunc(double &tv1, int &tv2) {
  cout << "template <>" << endl;
  cout << "void tfunc(int& tv1, double tv2)" << endl;
  PRINT_VAR;
}

template <typename T, typename U> void tfunc(const T &tv1, U &tv2) {
  cout << "template <typename T, typename U>" << endl;
  cout << "void tfunc(const T& tv1, U& tv2)" << endl;
  PRINT_VAR;
}

template <typename U> void tfunc(int &tv1, U &tv2) {
  cout << "template <typename U>" << endl;
  cout << "void tfunc(int& tv1, U& tv2)" << endl;
  PRINT_VAR;
}

int main() {
  int i1 = {3};
  string str1 = {"hello world!"};
  double d1 = {3.14};
  const int ci1 = 5;

  tfunc(str1, d1);
  tfunc(d1, i1);
  tfunc(ci1, d1);
  tfunc(i1, str1);
}
