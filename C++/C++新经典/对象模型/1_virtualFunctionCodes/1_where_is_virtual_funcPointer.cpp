#include <cstdio>
#include <iostream>

using namespace std;

class Normal
{
	long data;
};

class Virtual
{
public:
	long data;
	virtual void func() { cout << "I'm virtual class" << endl; }
};

int main()
{
	printf("size of class Normal: %zu\n", sizeof(Normal));
	printf("size of class Virtual: %zu\n", sizeof(Virtual));
	Virtual v;
	printf("Offset of member data: %zu\n", reinterpret_cast<char*>(&(v.data)) - reinterpret_cast<char*>(&v));
}
