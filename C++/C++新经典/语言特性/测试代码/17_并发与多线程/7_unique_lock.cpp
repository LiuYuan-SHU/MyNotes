#include <iostream>
#include <thread>
#include <mutex>
#include <list>

using namespace std;

class A
{
public:
	void inMsgRecvQueue()
	{
        unique_lock<mutex> lock(my_mutex, std::defer_lock);
		for (int i = 0; i < 100000; i++)
		{
			cout << __func__ << " execute, append element " << i << endl;

			if (lock.try_lock())
            {
                msgRecvQueue.push_back(i);
				lock.unlock();
            }
            else
            {
                cout << __func__ << " lock failed, NOP" << endl;
            }

			// ...
		}
		return;
	}

	bool outMsgLULProc(int& command)
	{
		static unique_lock<mutex> lock(my_mutex, defer_lock);

		if (!msgRecvQueue.empty() && lock.try_lock())
		{
			command = msgRecvQueue.front();
			msgRecvQueue.pop_front();

			lock.unlock();
			return true;
		}
        else
        {
            cout << __func__ << " get mutex failed, NOP" << endl;
        }
		return false;
	}

	void outMsgRecvQueue()
	{
		int command = 0;
		for (int i = 0; i < 100000; i++)
		{
			bool result = outMsgLULProc(command);
			if (result)
			{
				cout << __func__ << " execute, get element of value " << command << endl;
				// ...
			}
			else
			{
				cout << __func__ << " execute, queue empty" << endl;
			}
		}
	}
private:
	list<int> msgRecvQueue;
	mutex my_mutex;
};

int main()
{
	A a;
	thread out_msg(&A::outMsgRecvQueue, ref(a));
	thread in_msg(&A::inMsgRecvQueue, ref(a));

	out_msg.join();
	in_msg.join();

	cout << "Main exit" << endl;
}