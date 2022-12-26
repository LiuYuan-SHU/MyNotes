#include <thread>
#include <iostream>

using namespace std;

class TA
{
public:
    void operator()()
    {
        cout << "TA::operator() start" << endl;

        cout << "TA::operator() end" << endl;
    }
};

int main()
{
    TA ta;  
    thread t(ta);

    t.join();
}