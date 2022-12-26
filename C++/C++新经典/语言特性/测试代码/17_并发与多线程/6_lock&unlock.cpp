#include <iostream>
#include <thread>
#include <mutex>
#include <list>

using namespace std;

mutex my_mutex;
list<int> global_l;

void producer()
{
    for (int i = 1; i < 100; i++)
    {
        my_mutex.lock();

        if (i != 99)
        {
            global_l.push_back(i);
            cout << "write data " << i << endl;
        }
        else
        {
            global_l.push_back(0);
            cout << "producer quit" << endl;
        }

        this_thread::sleep_for(std::chrono::milliseconds(100));

        my_mutex.unlock();
    }
}

void consumer()
{
    int temp = -1;
    while (temp != 0)
    {
        if (!global_l.empty())
        {
            my_mutex.lock();

            temp = global_l.front();
            global_l.pop_front();
            cout << "consumer read " << temp << endl;

            my_mutex.unlock();
        }
    }
}

int main()
{
    thread thread_producer(producer);
    thread thread_consumer(consumer);

    thread_producer.join();
    thread_consumer.join();

    cout << "Main quit" << endl;
}