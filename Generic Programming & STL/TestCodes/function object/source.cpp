#include<iostream>
#include<iterator>
#include<cmath>

#define READ true					//before compile, set READ as false.

using namespace std;

/* This file is a test to test function object and its adapter
 * class `even` is the function object itself, with operator(). The most important part is the `const` key word 
 * class `unary_negate` is the funcion object adapter itself. It use `even` to do the oppsite thing.
 * inline function `not1` is the STL function, which provides a easier way to call function object adapter.
 */

//function object class
template<class Number>
struct even
{
	typedef Number argument_type;
	typedef Number result_type;
	bool operator()(const Number& num) const { return num % 2 == 0; }
};

//function object adapter declared in STL
//use Function Object `even` to judge odd number
//for a Function Object Adapter, the Function Object is the Predicate 
#if READ

template<class AdaptablePredicate>
class unary_negate
{
private:
	AdaptablePredicate pred;
public:
	typedef typename AdaptablePredicate::argument_type	argument_type;
	typedef typename AdaptablePredicate::result_type	result_type;
	unary_negate(const AdaptablePredicate& x) : pred(x) {}				//constructor
	bool operator()(const argument_type& x) const
	{
		return !pred(x);
	}
};

#endif

//not1, which has been declared in STL, provides a easier way to call unary_negate
#if READ

template<class AdaptablePredicate>
inline unary_negate<AdaptablePredicate>
not1(const AdaptablePredicate& pred)
{
	return unary_negate<AdaptablePredicate>(pred);
}

#endif


//find_if in STL
//traverse in the range until *first satisfies the condition
template<class InputIterator, class Predicate>
InputIterator find_if(InputIterator first, InputIterator last, Predicate pred)
{
	while(first != last && !pred(*first))
	{
		++first;
	}
	return first;
}

//------------------------------------------------------------------------------------------------------
//in the following part, it shows how to transfer a function pointer to function object adapter

//the basic function
bool is_even(int num)
{
	return (num % 2 == 0);
}


//declared in STL
//transfer the function  to function object adapter
#if READ

template<class Arg, class Result>
class pointer_to_unary_function : public unary_function<Arg, Result>
{
private:
    Result (*ptr)(Arg);											//define function pointer
public:
    pointer_to_unary_function() {}								//constructor
    pointer_to_unary_function(Result (*x)(Arg)) : ptr(x) {}		//construct a function into a function object
    Result operator()(Arg x) const { return ptr(x); }			//predicate
};

//a easier way to use adapter
template<class Arg, class Result>
inline pointer_to_unary_function<Arg, Result>
ptr_fun(Result (*x)(Arg))
{
    return pointer_to_unary_function<Arg, Result>(x);
}

#endif

int main()
{
	int array[10];
	for(int i = 0; i < 10; i++)
	{
		array[i] = pow((i + 1),2);
	}
	
    //use function object
    cout << "-----Use function object-----" << endl;
	cout << *(find_if(array, array + 10, even<int>()))<<endl;
    
    //use function object adapter
	//the first way to use function object adapter
    /*
    unary_negate<even<int>>(even<int>()), here, the first even<int> is F
    the second `even<int>()` is constructor, which is f
    */
    cout << "-----Use function object adapter-----" << endl;
    cout << "The first way: " << *(find_if(array, array + 10, unary_negate<even<int>>(even<int>()))) << endl;
	//the second way to use funcion object adapter
	cout << "The second way: " << *(find_if(array, array + 10, not1(even<int>()))) << endl;
	
    //use function pointer
	cout << "-----Use function pointer-----" << endl;
    cout << "The first way: " <<*(find_if(array, array + 10, pointer_to_unary_function<int, bool>(is_even))) << endl;
    cout << "The second way: " <<*(find_if(array, array + 10, ptr_fun<int, bool>(is_even))) << endl;
	return 0;
}
