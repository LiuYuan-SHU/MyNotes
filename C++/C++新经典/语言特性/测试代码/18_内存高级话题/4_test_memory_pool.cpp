/*
 * Copyright 2023.1.3 Yuan Liu
 */
#include <chrono>
#include <cstddef>
#include <iostream>

using hClock = std::chrono::time_point<std::chrono::high_resolution_clock>;
using std::cout;
using std::endl;
using std::chrono::high_resolution_clock;

class Test {
public:
  static void *operator new(size_t size);
  static void operator delete(void *phead);
  // 用于分配计数统计，每new一次+1
  static int _count;
  // 用于统计malloc的次数，每malloc一次+1
  static int _mallocCount;

private:
  Test *_next;
  // 总是指向一块可以分配出去的内存的首地址
  static Test *_freePos;
  // 一次可以分配多少倍该类的内存
  static int _trunkCount;
};

void *Test::operator new(size_t size) {
  Test *tmp;
  if (_freePos == nullptr) {
    // 如果为空，为我们需要申请很大的一块内存
    size_t real_size = _trunkCount * size;
    _freePos = reinterpret_cast<Test *>(::new char[real_size]);

    tmp = _freePos;

    for (; tmp != &_freePos[_trunkCount - 1]; tmp++) {
      tmp->_next = tmp + 1;
    }
    tmp->_next = nullptr;
    _mallocCount++;
  }

  tmp = _freePos;
  _freePos = _freePos->_next;
  _count++;

  return tmp;
}

void Test::operator delete(void *phead) {
  (static_cast<Test *>(phead))->_next = _freePos;
  _freePos = static_cast<Test *>(phead);
}

int Test::_count = 0;
int Test::_mallocCount = 0;
Test *Test::_freePos = nullptr;
int Test::_trunkCount = 5;

struct Ordinary {
  Ordinary *_next;
};

int main() {
  hClock start = high_resolution_clock::now();
  for (int i = 0; i < 500000; i++) {
    new Test();
  }
  hClock end = high_resolution_clock::now();
  std::chrono::duration<double> time_cost = end - start;

  cout << "Time cost: " << time_cost.count() << "s" << endl;

  start = high_resolution_clock::now();
  for (int i = 0; i < 500000; i++) {
    new Ordinary;
  }
  end = high_resolution_clock::now();
  time_cost = end - start;

  cout << "Ordinary time cost: " << time_cost.count() << "s" << endl;
}
