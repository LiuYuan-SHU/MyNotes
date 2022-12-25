#include <iostream>

using namespace std;

class A
{
	public:
		void func() {}
		void func_1() {}
		void func_2() {}
};

int main()
{
	cout << "size of object of class A: " << sizeof(A) << endl;
}
