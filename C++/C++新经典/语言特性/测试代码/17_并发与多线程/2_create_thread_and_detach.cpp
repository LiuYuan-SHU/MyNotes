#include <thread>
#include <iostream>

using namespace std;

class TA
{
public:
    TA(int& i) : m_i(i) { }

    void operator()() 
    {
        for (int i = 0; i < 10; i++)
        {
            cout << "value of m_i: " << m_i << endl;
            cout << "Address of m_i: " << (&m_i) << endl;
            cout << "====================================" << endl;
            this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
private:
    int& m_i;
};

void foo()
{
    int my_i = 6;
    TA ta(my_i);
    thread t(ta);
    t.detach();
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << __func__ << " is end" << endl;
}

int main()
{
    foo();

    this_thread::sleep_for(chrono::milliseconds(55000));
}