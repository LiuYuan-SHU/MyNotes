#include<iostream>
#include<iterator>

//copy funciton in STL
/*
template<class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
{
    for( ; first != last; ++result, ++ first)
        *result = *first;
    return result;
}
*/ 

//ostream_iterator in STL
/*
template<class T>
class ostream_iterator
{
private:
    ostream* os;
    const char* string;
public:
    ostream_iterator(ostream& s,const char* c = 0) : os(&s), string(c) {}
    ostream_iteratpr(const ostream_iterator& i) : os(i.os), string(i.string) {}
    ostream_iterator& operator=(const ostream_iterator& i)
    {
        os = i.os;
        string = i.string;
        return *this;
    }
    ostream_iterator<T>& operator=(const T& value)
    {
        *os << value;
        if (string) *os << string;
        return *this;
    }
    
    ostream_iterator<T>& operator*() { return *this; }
    ostream_iterator<T>& operator++() { return *this; }
    ostream_iterator<T>& operator++(int) { return *this; }
}
*/ 

using namespace std;

#define N 10

int main()
{
	int A[N];
	for(int i = 0; i < N; i++)
	{
		A[i] = (i + 1) * (i + 1);
	}
	copy(A, A + N, ostream_iterator<int>(cout," "));	

	return 0;
}
