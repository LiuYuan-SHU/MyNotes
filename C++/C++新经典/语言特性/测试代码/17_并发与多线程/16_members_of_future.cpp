#include <chrono>
#include <future>
#include <iostream>
#include <thread>

using namespace std;

int my_thread()
{
	cout << __func__ << " starts, thread id: " << this_thread::get_id() << endl;

	this_thread::sleep_for(chrono::milliseconds(5000));
	cout << __func__ << " ends" << endl;
	return 5;
}

int main()
{
	cout << __func__ << " starts, thread id: " << this_thread::get_id() << endl;
	future<int> result = async(my_thread);

	cout << "continue..." << endl;
	
	future_status result_status = result.wait_for(chrono::seconds(1));

	if (result_status == future_status::timeout)
	{
		cout << "timeout" << endl;
		cout << result.get() << endl;
	}
	else if (result_status == future_status::ready)
	{
		cout << "ready" << endl;
		cout << result.get() << endl;
	}
	else if (result_status == future_status::deferred)
	{
		cout << "deferred" << endl;
		cout << result.get() << endl;
	}

	cout << __func__ << " ends" << endl;
}
