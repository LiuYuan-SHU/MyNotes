#include <iostream>
#include <mutex>
#include <list>
#include <thread>

using namespace std;

class A
{
public:
	// 把接收到的消息(玩家的命令)放入到一个队列的线程
    void inMsgRecvQueue()
    {
        for (int i = 0; i < 100000; i++)
        {
            cout << __func__ << " 执行,插入元素 " << i << endl;

			unique_lock<mutex> guard(_my_mutex);
			_msgRecvQueue.push_back(i);	// 假设数字就是接收到的命令

			// ...其他处理代码
        }
    }

	bool outMsgLULProc(int& command)
	{
		unique_lock<mutex> guard(_my_mutex);

		if(!_msgRecvQueue.empty())
		{
			// 消息不为空
			command = _msgRecvQueue.front();
			_msgRecvQueue.pop_front();
			return true;
		}
		return false;
	}

	// 把数据从消息队列中取出的线程
	void outMsgRecvQueue()
	{
		int command = 0;
		for (int i = 0; i < 100000; i++)
		{
			bool result = outMsgLULProc(command);
			if (result)
			{
				cout << __func__ << " 执行,从容器中取出一个元素 " << i << endl;
				// ...其他处理代码
			}
			else
			{
				// 消息队列为空
				cout << __func__ << " 执行，但是目前消息队列中没有元素" << i << endl;
			}
		}
		cout << "endl" << endl;
	}

private:
	list<int>	_msgRecvQueue;
	mutex		_my_mutex;
};

int main()
{
	A a;
	thread out_msg_thread(&A::outMsgRecvQueue, &a);
	thread in_msg_thread(&A::inMsgRecvQueue, &a);

	out_msg_thread.join();
	in_msg_thread.join();

	cout << __func__ << " ends" << endl;

	return 0;
}
