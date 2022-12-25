#include <cstdio>
#include <iostream>

using namespace std;

#define BASE_CALL	cout << "Base::" << __func__ << endl; 
#define DERI_CALL	cout << "Derived::" << __func__ << endl;
#define DIVISION    cout << "============================================================" << endl;

typedef long* vptr;

class Base
{
public:
	virtual void func_1() { BASE_CALL; }
	virtual void func_2() { BASE_CALL; }
	virtual void func_3() { BASE_CALL; }
};

class Derived : public Base
{
public:
	void func_2() { DERI_CALL; }
};

int main()
{
	printf("size of class Base: %zu\n", sizeof(Base));
	printf("size of class Derived: %zu\n", sizeof(Derived));

    DIVISION;

	vptr vptr_base = reinterpret_cast<vptr>(new Base());
    vptr vptr_derived = reinterpret_cast<vptr>(new Derived());

    vptr virtual_table_base = reinterpret_cast<vptr>(*vptr_base);
    vptr virtual_table_derived = reinterpret_cast<vptr>(*vptr_derived);

    cout << "The first 5 items in the virtual function table in class Base:" << endl;
    for (int i = 0; i < 5; i++)
    {
        printf("table[%d]: %p\n", i, virtual_table_base[i]);
    }

    cout << "The first 5 items in the virtual function table in class Derived:" << endl;
    for (int i = 0; i < 5; i++)
    {
        printf("table[%d]: %p\n", i, virtual_table_derived[i]);
    }

    DIVISION;

    cout << "Try to call virtual functions in class Base:" << endl;
    for (int i = 0; i < 3; i++)
    {
        (reinterpret_cast<void(*)()>(virtual_table_base[i]))();
    }

    cout << "Try to call virtual functions in class Derived:" << endl;
    for (int i = 0; i < 3; i++)
    {
        (reinterpret_cast<void(*)()>(virtual_table_derived[i]))();
    }
}
