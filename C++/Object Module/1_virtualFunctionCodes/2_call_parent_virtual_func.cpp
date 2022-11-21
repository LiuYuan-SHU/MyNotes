#include <cstdio>
#include <iostream>

using namespace std;

#define BASE_CALL	cout << "Base::" << __func__ << endl; 
#define DERI_CALL	cout << "Derived::" << __func__ << endl;
typedef long* vptr;

class Base
{
public:
	virtual void func_1() { BASE_CALL; }
	virtual void func_2() { BASE_CALL; }
	virtual void func_3() { BASE_CALL; }
};

class Derived
{
public:
	virtual void func_2() { DERI_CALL; }
};

int main()
{
	printf("size of Base: %zu\n", sizeof(Base));
	printf("size of Derived: %zu\n", sizeof(Derived));

	vptr ptr_base = reinterpret_cast<vptr>(new Base());
	vptr ptr_derived = reinterpret_cast<vptr>(new Derived());

	printf("Printf the following 5 function address of class Base\n");
	for(size_t index = 0; index < 5; index++)
	{
		printf("vptr[%zu] = %p\n", index, reinterpret_cast<long*>(ptr_base[index]));
	}

	printf("Printf the following 5 function address of class Derived\n");
	for(size_t index = 0; index < 5; index++)
	{
		printf("vptr[%zu] = %p\n", index, reinterpret_cast<long*>(ptr_derived[index]));
	}
}
