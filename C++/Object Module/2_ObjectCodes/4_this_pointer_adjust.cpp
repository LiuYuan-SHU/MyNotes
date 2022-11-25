#include <cstdio>
#include <iostream>

using namespace std;

class A
{
public:
	int a;
	A()
	{
		printf("A::%s, this: %p\n", __func__, this);
	}
	void func_A() { printf("A::%s: this: %p\n", __func__, this);  }
};

class B
{
public:
	int b;
	B()
	{
		printf("B::%s, this: %p\n", __func__, this);
	}
	void func_B() { printf("B::%s: this: %p\n", __func__, this);  }
};

class C : public A, public B
{
public:
	int c;
	C()
	{
		printf("C::%s, this: %p\n", __func__, this);
	}
	void func_C() { printf("C::%s: this: %p\n", __func__, this);  }
};

int main()
{
	cout << sizeof(A) << endl;
	cout << sizeof(B) << endl;
	cout << sizeof(C) << endl;

	C c;
	c.func_A();
	c.func_B();
	c.func_C();
}
