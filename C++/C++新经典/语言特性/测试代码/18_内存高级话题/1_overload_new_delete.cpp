#include <cstdlib>
#include <iostream>

using namespace std;

class Test
{
public:
    Test() : _val(0) 
    { 
        cout << "Test::" << __func__ << endl;
    }
    ~Test() 
    {
        cout << "Test::" << __func__ << endl;
    }

    static void* operator new(size_t size)
    {
        cout << "Test::" << __func__ << endl;

        return malloc(size);
    }

    static void operator delete(void* p)
    {
        cout << "Test::" << __func__ << endl;

        free(p);
    }
private:
    int _val;
};

int main()
{
    // call overloaded new/delete
    Test *test1 = new Test();
    delete test1;

    // call global new/delete
    Test *test2 = ::new Test();
    ::delete test2;
}