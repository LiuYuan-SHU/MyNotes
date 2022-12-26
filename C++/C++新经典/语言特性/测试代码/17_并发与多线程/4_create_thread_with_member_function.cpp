#include <iostream>
#include <thread>

using namespace std;

class Test
{
public:
    void _thread() 
    {
        cout << __func__ << ": thread ID: " << this_thread::get_id() << endl;
    }
};

int main()
{
    Test test;

    thread my_thread(&Test::_thread, &test);

    my_thread.join();

    cout << "Main thread ID: " << this_thread::get_id() << " is finished" << endl;
}