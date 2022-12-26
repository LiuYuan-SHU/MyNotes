#include <iostream>
#include <thread>

using namespace std;

struct Test
{
	Test(int val) : _val(val)
	{
		cout << "Test::Test(), thread id: " << this_thread::get_id() << endl;
	}
	Test(const Test& other) : _val(other._val)
	{
		cout << "Test::Test(const Test&), thread ID: " << this_thread::get_id() << endl;
	}
	~Test()
	{
		cout << "Test::~Test(), thread id: " << this_thread::get_id() << endl;
	}

	int _val;
};

void myPrint(const Test& test)
{
	cout << __func__ << ": &test: " << &test << ", thread id: " << this_thread::get_id() << endl;
}

int main()
{
	cout << "Main thread id: " << this_thread::get_id() << endl;
	int val = 1;
	// thread my_thread(myPrint, val);
	thread my_thread(myPrint, Test(val));
	

	my_thread.join();
	cout << "Main is finished" << endl;
}