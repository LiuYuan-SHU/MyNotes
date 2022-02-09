#include<iostream>
#include<iterator>

using namespace std;
/*
template<class InputIterator,class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
{
	for( ; first != last; result++, first++)
		*result = *first;
	return result;
}
*/
/*
template<class T>
class ostream_iterator
{
private:
	ostream* os;
	const char* string;
public:
	ostream_iterator(ostream& s, const char *c = 0) : os(&s), string(c) {}
	ostream_iterator(const ostream_iterator& i) : os(i.os),string(i.string) {}
	ostream_iterator& operator=(const ostream_iterator& i)
	{
		os = i.os;
		string = i.string;
		return *this;
	}
	ostream_iterator<T>& operator=(const T& value)
	{
		*os << value;
		if(string) *os << string;
		return *this;
	}
	ostream_iterator<T>& operator*() { return *this;  }
	ostream_iterator<T>& operator++() { return *this;  }
	ostream_iterator<T>& operator++(int) { return *this;}
};
*/
int main()
{
	int a[10];
	for(int i = 0;i<10;i++)
	{
		a[i] = (i + 1) * (i + 1);
	}
	copy(a,a+10,ostream_iterator<int>(cout," "));

	return 0;
}
