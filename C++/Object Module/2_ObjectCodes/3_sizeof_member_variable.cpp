#pragma pack(2)

#include <iostream>

using namespace std;

class A
{
public:
	char c1;
	int d;
	char c2;
};

int main()
{
	cout << "size of object of class A: " << sizeof(A);
}
