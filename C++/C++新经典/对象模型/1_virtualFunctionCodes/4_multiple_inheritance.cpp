#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

#define GET_CLASS_NAME(CLASS)  string getClassName() { return #CLASS; }
#define FUNC_CALL   cout << getClassName() << "::" << __func__ << endl;
#define DIVISION    cout << string(60, '=') << endl;

typedef void (*FUNC)();
typedef long* pvptr;
typedef long* vptr;

#define PRINT_FUNC_ADDRESS(INFO, PTR_TABLE)                     \
    cout << INFO << endl;                                       \
    for (int i = 0; i < 2; i++)                                 \
    {                                                           \
        printf("%p\n", reinterpret_cast<FUNC>(PTR_TABLE[i]));   \
    }

#define CALL_VIR_FUNC(INFO, PTR_TABLE)              \
    cout << INFO << endl;                           \
    for (int i = 0; i < 2; i++)                     \
    {                                               \
        (reinterpret_cast<FUNC>(PTR_TABLE[i]))();   \
    }

class Base1
{
    GET_CLASS_NAME(Base1);

public:
    virtual void func_1() { FUNC_CALL; }
    virtual void func_2() { FUNC_CALL; }
};

class Base2
{
    GET_CLASS_NAME(Base2);

public:
    virtual void func_3() { FUNC_CALL; }
    virtual void func_4() { FUNC_CALL; }
};

class Derived : public Base1, public Base2
{
    GET_CLASS_NAME(Derived);

public:
    void func_2() { FUNC_CALL; }
    void func_4() { FUNC_CALL; }
};

int main()
{
    cout << "size of class Base1: " << sizeof(Base1) << endl;
    cout << "size of class Base2: " << sizeof(Base2) << endl;
    cout << "size of class Derived: " << sizeof(Derived) << endl;

    DIVISION;

    pvptr pvptr_base1 = reinterpret_cast<pvptr>(new Base1());
    pvptr pvptr_base2 = reinterpret_cast<pvptr>(new Base2());
    pvptr pvptr_derived = reinterpret_cast<pvptr>(new Derived());

    vptr vptr_base1 = reinterpret_cast<vptr>(*(pvptr_base1));
    vptr vptr_base2 = reinterpret_cast<vptr>(*(pvptr_base2));
    vptr vptr_derived_table_1 = reinterpret_cast<vptr>(*(pvptr_derived));
    vptr vptr_derived_table_2 = reinterpret_cast<vptr>(*(pvptr_derived + 1));

    printf("The address of virtual function table of class Base1: %p\n", vptr_base1);
    printf("The address of virtual function table of class Base2: %p\n", vptr_base2);
    printf("The address of virtual function table 1 of class Derived: %p\n", vptr_derived_table_1);
    printf("The address of virtual function table 2 of class Derived: %p\n", vptr_derived_table_2);

    DIVISION;

    PRINT_FUNC_ADDRESS("Print all addresses of virtual functions in class Base1:", vptr_base1);

    CALL_VIR_FUNC("Call all functions in class Base1:", vptr_base1);

    DIVISION;

    PRINT_FUNC_ADDRESS("Print all addresses of virtual functions in class Base2:", vptr_base2);

    CALL_VIR_FUNC("Call all functions in class Base2:", vptr_base2);

    DIVISION;

    PRINT_FUNC_ADDRESS("Print all addresses of virtual functions in virtual function table 1 of class Derived: ",
                       vptr_derived_table_1);

    PRINT_FUNC_ADDRESS("Print all addresses of virtual functions in virtual function table 2 of class Derived: ",
                       vptr_derived_table_2);

    cout << "Try to call the functions in the virtual function table of class Derived: " << endl;

    CALL_VIR_FUNC("Try to call the functions inherited from class Base1:", vptr_derived_table_1);

    CALL_VIR_FUNC("Try to call the functions inherited from class Base2:", vptr_derived_table_2);
}