#include <cstdio>
#include <iostream>

using namespace std;

#define BASE_CALL	cout << "Base::" << __func__ << endl;
#define DERI_CALL	cout << "Derived::" << __func__ << endl;
#define DIVISION    cout << "============================================================" << endl;

typedef long* vptr;
typedef long* virtual_table_ptr;

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
    vptr d1 = reinterpret_cast<vptr>(new Derived());
    vptr d2 = reinterpret_cast<vptr>(new Derived());

    virtual_table_ptr vtptr_derived_1 = reinterpret_cast<virtual_table_ptr>(*d1);
    virtual_table_ptr vtptr_derived_2 = reinterpret_cast<virtual_table_ptr>(*d2);

    cout << "The address of virtual function table of derived1: " << vtptr_derived_1 << endl;
    cout << "The address of virtual function table of derived2: " << vtptr_derived_2 << endl;

    DIVISION;

    Derived derived;
    Base base = derived;
    Base* ptr_base = &derived;

    printf("The address of virtual function table of derived: %p\n", (*((long*)&derived)));
    printf("In OO, the address of virtual function table of base: %p\n", (*((long*)ptr_base)));
    printf("In OB, the address of virtual function table of base: %p\n", (*((long*)&base)));
}