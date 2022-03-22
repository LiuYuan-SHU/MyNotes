/**********************************************************************
 * 分配512个int
 * https://www.youtube.com/watch?v=84U1Pkegm-M&list=PLTcwR9j5y6W2Bf4S-qi0HBQlHXQVFoJrP&index=11
 * 2022年3月22日14:46:11
 * ==================================================================
 * NOTE
 * ==================================================================
 * g++ -std=c++11 ./1_test_allocator.cpp
 **********************************************************************/

#include <iostream>
#include <scoped_allocator>

using namespace std;

int main()
{
	int* p = allocator<int>().allocate(512, (int*)0);
	allocator<int>().deallocate(p, 512);
}
