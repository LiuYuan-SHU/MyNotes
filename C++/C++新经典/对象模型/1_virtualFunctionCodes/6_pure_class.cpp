#include <iostream>
#include <cstring>

using namespace std;

class X
{
public:
    int x;
    int y;
    int z;
    X()
    {
        memset(this, 0, sizeof(X));
        cout << "Constructor" << endl;
    }

    // X(const X& x) : x(x.x), y(x.y), z(x.z) { cout << "Copy Constructor" << endl; }

    X(const X& x)
    {
        memcpy(this, &x, sizeof(X));
        cout << "Copy Constructor" << endl;
    }

    virtual ~X()
    {
        cout << "Destructor" << endl;
    }

    virtual void vir_func()
    {
        cout << "virtual function" << endl;
    }

    void normal_func()
    {
        cout << "Normal function" << endl;
    }

    friend ostream& operator<<(ostream& os, const X& x);
};

ostream& operator<<(ostream& os, const X& x)
{
    os << x.x << ",\t" << x.y << ",\t" << x.z << endl;
    return os;
}

int main()
{
    X x1;
    x1.x = 100; x1.y = 200; x1.y = 300;
    X x2(x1);
    cout << "X1: " << x1;
    cout << "X2: " << x2;

    x1.vir_func();

    cout << "====================" << endl;

    X* ptr_x = new X();
    ptr_x->normal_func();
    ptr_x->vir_func();
    delete ptr_x;
}