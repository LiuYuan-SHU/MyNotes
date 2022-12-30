#include <cstdio>
#include <functional>
#include <iostream>
#include <thread>
#include <future>

using namespace std;

void thread_1(promise<int> &result, int val)
{
	cout << __func__ << " start, thread id: " << this_thread::get_id() << endl;
	
	val++;
	val *= 10;

	result.set_value(val);
	cout << __func__ << " ends" << endl;
}

void thread_2(future<int> &ftr)
{
	int result = ftr.get();
	cout << __func__ << " get result: " << result << endl;
}

int main()
{
	cout << __func__ << " start, thread id: " << this_thread::get_id() << endl;

	promise<int> prom;
	thread t1(thread_1, ref(prom), 180);

	future<int> result = prom.get_future();
	thread t2(thread_2, ref(result));

	t1.join();
	t2.join();

	cout << __func__ << " ends" << endl;
}
