#include <chrono>
#include <iostream>
#include <future>
#include <thread>

using namespace std;

int my_thread(int val)
{
	cout << __func__ << " starts, thread id: " << this_thread::get_id() << endl;
	this_thread::sleep_for(chrono::seconds(2));
	return 2;
}
