#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void myThread(int index)
{
    cout << "Thread id: " << this_thread::get_id()
         << "\tindex: " << index << endl;
}

int main()
{
    vector<thread> vec;

    for (int i = 0; i < 10; i++)
    {
        vec.emplace_back(myThread, i);
    }

    for (auto& ele : vec)
    {
        ele.join();
    }

    cout << "Main thread finished" << endl;
}