#include <iostream>
#include <future>
#include <thread>

using namespace std;

int main()
{
	cout << __func__ << " thread id: " << this_thread::get_id() << endl;
	// 创建一个packaged_task对象，封装一个lambda函数
	packaged_task<int(int, int)> pt([](int a, int b) -> int
			{
				cout << "a: " << a << "\tb: " << b << endl;
				cout << "lambda thread id: " << this_thread::get_id() << endl;
				return 15;
			});
	
	// 创建线程，其可执行对象为packaged_task，在后面跟上参数
	thread t(ref(pt), 1, 2);
	t.join();

	future<int> result = pt.get_future();
	cout << "result get: " << result.get() << endl;

	return 0;
}
