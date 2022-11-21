#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

// 返回一个保存int的vector的指针
inline vector<int>* func_getVec();

// 从标准输入获得数字，保存在vec中
inline void func_inputInt(vector<int>* vec);

// 打印vector中的元素
inline void func_printVec(vector<int>* vec);

int main()
{
	vector<int>* vec = func_getVec();
	func_inputInt(vec);
	func_printVec(vec);

	delete vec;
}

vector<int>* func_getVec()
{
	return new vector<int>();
}

void func_inputInt(vector<int>* vec)
{
	istream_iterator<int> is_cin(cin), eof;
	vec->insert(vec->end(), is_cin, eof);
}

void func_printVec(vector<int>* vec)
{
	copy(vec->cbegin(), vec->cend(), ostream_iterator<int>(cout, " "));
	cout << endl;
}
