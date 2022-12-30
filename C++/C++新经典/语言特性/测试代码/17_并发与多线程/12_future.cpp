#include <chrono>
#include <iostream>
#include <thread>
#include <future>

using namespace std;

int entry_function()
{
    cout << __func__ << " execute, thread id: " << this_thread::get_id() << endl;
	this_thread::sleep_for(chrono::milliseconds(2000));
	cout << __func__ << " finished, return 5" << endl;

	return 5;
}

int main()
{
	cout << __func__ << " start" << endl;
	future<int> result = async(entry_function);
 
	cout << __func__ << " continues..." << endl;
	cout << "entry_function return value: " << result.get() << endl;

	cout << __func__ << " finished" << endl;

	return 0;
}
