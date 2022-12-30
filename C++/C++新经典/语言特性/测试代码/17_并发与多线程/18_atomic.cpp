#include <algorithm>
#include <chrono>
#include <iostream>
#include <atomic>
#include <mutex>
#include <ratio>
#include <thread>
#include <vector>

using namespace std;

mutex ordinary_mutex;

long ORDINARY_SUM = 0;
atomic<long> ATOMIC_SUM(0);

void func_add_ordinary()
{
	for (int i = 0; i < 10000000; i++)
	{
		lock_guard<mutex> lock(ordinary_mutex);
		ORDINARY_SUM ++;
	}
}


void func_add_atomic()
{
	for (int i = 0; i < 1000000; i++)
	{
		ATOMIC_SUM ++;
	}
}

int main()
{
	vector<thread> ordinary_vec, atomic_vec;

	auto ordinary_start = chrono::high_resolution_clock::now();
	for(int i = 0; i < 10; i++)
	{
		ordinary_vec.emplace_back(func_add_ordinary);	
	}

	for_each(ordinary_vec.begin(), ordinary_vec.end(), [](thread& t) -> void
			{
				t.join();
			});	
	auto ordinary_end = chrono::high_resolution_clock::now();

	auto atomic_start = chrono::high_resolution_clock::now();
	for(int i = 0; i < 10; i++)
	{
		atomic_vec.emplace_back(func_add_atomic);
	}

	for_each(atomic_vec.begin(), atomic_vec.end(), [](thread& t) -> void
			{
				t.join();
			});
	auto atomic_end = chrono::high_resolution_clock::now();

	cout << "ORDINARY_SUM: " << ORDINARY_SUM << endl;
	cout << "ATOMIC_SUM: " << ATOMIC_SUM << endl;

	cout << "Ordinary time cost:\t" << (chrono::duration_cast<chrono::microseconds>(ordinary_end - ordinary_start).count()) << " microseconds" << endl;
	cout << "Atomic time cost:\t" << (chrono::duration_cast<chrono::microseconds>(atomic_end - atomic_start).count()) << " microseconds" << endl;
}
