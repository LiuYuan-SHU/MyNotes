#include <condition_variable>
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

			_my_condition.notify_one();
			guard.unlock();
			// ...其他处理代码
        }
    }

	// 把数据从消息队列中取出的线程
	void outMsgRecvQueue()
	{
		int command = 0;
		for (int i = 0; i < 100000; i++)
		{
			// 在wait之前，首先我们现需要获得锁
			unique_lock<mutex> lock(_my_mutex);
			// 调用wait，
			_my_condition.wait(lock, [this]() -> bool
					{
						return !(this->_msgRecvQueue.empty());
					});	
			command = _msgRecvQueue.front();
			_msgRecvQueue.pop_front();
			
			lock.unlock();
			cout << __func__ << " got command " << i << endl;
		}
		cout << "end" << endl;
	}

private:
	list<int>			_msgRecvQueue;
	mutex				_my_mutex;
	condition_variable	_my_condition;
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
