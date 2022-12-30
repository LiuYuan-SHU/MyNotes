#include <iostream>
#include <thread>
#include <future>

using namespace std;

class Test
{
public:
	int entry_function(int val)
	{
		cout << __func__ << " execute, thread id: " << this_thread::get_id() << endl;

		return val;
	}
};

int main()
{
	Test test;
	future<int> result = async(launch::deferred, &Test::entry_function, &test, 5);
	
	cout << __func__ << " continues, thread id: " << this_thread::get_id() << endl;
	cout << "Got child thread return value: " << result.get() << endl;
}
