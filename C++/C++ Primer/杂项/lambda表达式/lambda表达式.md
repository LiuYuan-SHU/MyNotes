# lambda表达式

# 介绍lambda

## why lamda?

在STL泛型算法中，我们可以传入一个**谓词（predicate）**，来帮助泛型算法更好地进行运算。

例如，我们可以在`find_if`函数中传入第三个参数，这个参数是一个**接受且只接受一个参数的可调用对象**，其能够帮助`find_if`判断是否找到了我们需要的元素：

```cpp
bool getOdd(int numToPredicate) { return numToPredicate == 0; }
int main()
{
	vector<int> vec({1, 2, 3});
	find_if(vec.cbegin(), vec.cend(), getOdd);
}
```

但是，有的时候，我们需要向其中[传递两个参数](lambda表达式.md)才能确定我们是否找到了我们需要的元素。在不进行额外的操作的时候，我们是无法使用的。这个时候，我们就可以使用lambda表达式。

---

我们可以向一个算法传递任何类别的**可调用对象（callable object）。**对于一个对象或一个表达式，如果可以对其使用调用运算符，则称它是可调用的。即，如果`e`是一个可调用的表达式，那么我们可以编写代码`e(args)`。 

有四种方式编写可调用对象：

1. 函数
2. 函数指针
3. 重载函数调用运算符的类
4. lambda表达式

一个lambda表达式表示一个可调用的代码单元。我们可以可以将其理解为一个未命名的内联函数。

- 与函数的相同点：具有返回类型、一个参数列表和一个函数体
- 与函数的不同点：lambda可以定义在函数内部

## lambda表达式的形式

```cpp

[capture list](parameter list) -> return type { function body }
```

- `capture list`：捕获列表，是一个lambda所在函数中定义的局部变量的列表（通常为空）
- `return type`：返回类型
- `parameter list`：参数列表
- `function body`：函数体

在定义lambda表达式的时候，我们可以忽略参数列表和返回类型，但是必须要包含捕获列表和函数体

```cpp
auto f = []  { return 5; }
```

忽略参数列表等价于制定一个空参数列表；忽略返回类型，lambda表达式根据函数体中的代码推断返回类型。

## lambda表达式使用示例

```cpp
// 稳定排序一个vector, 其中存放的元素是string类型
// 1. 常规写法
bool isShorter(const string& str1, const string& str2) { return str1.size() < str2.size(); }
int main()
{
	vector<string> vec({"hello", "world", "!"});
	stable_sort(vec.begin(), vec.end(), isShorter);
}

// 2. lambda
int main()
{
	vector<string> vec({"hello", "world", "!"});
	stable_sort(vec.begin(), vec.end(), 
		[](const string& str1, const string& str2) -> bool { return str1.size() < str2.size(); });
}
```

# 使用lambda表达式

## 向lambda传递参数

传参与别的函数没有太大区别，唯一的区别是**lambda表达式不能有默认参数。**

## 使用捕获列表

- 虽然一个lambda可以出现在一个函数中并使用其局部变量，但它只能使用那些明确指明的变量。
- 如果lambda使用了一个局部变量，而这个局部变量并不在捕获列表中，那么将会报错。
- 但是需要注意的是，定义在头文件中的变量，例如`cout`等，是不需要包含的。

<aside>
📌 捕获列表只作用于局部非static变量，lambda可以直接使用局部static变量和在它所在函数之外声明的名字

</aside>

## 示例

> 编写一个函数，其返回类型为`void`，接受两个参数，第一个参数为`vector<string>& words`，第二个参数为`vector<string>::size_type sz`。vector中的单词有重复，要求：
> 
> 1. 按照从小到大，稳定排序words，并且删除重复的单词；
> 2. 返回一个迭代器，指向排序、删除结束后的第一个长度大于 `sz`的单词
> 3. 计算满足`string.size() >= sz`的字符串个数
> 4. 打印长度大于等于给定值`sz`的单词，并且每个单词后接一个空格

### 代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void func(vector<string>& words, vector<string>::size_type sz);

int main()
{
	vector<string> vec({ "fox", "jumps", "over", "quick", "red", "red", "slow", "the", "the", "turtle" });
	func(vec, 5);
}

void func(vector<string>& words, vector<string>::size_type sz)
{
	cout << "before any operation: " << endl;
	for_each(words.begin(), words.end(), [](const string& str) -> void { cout << str << " "; });
	cout << endl;
	cout << "===============================================" << endl;

	// 稳定排序
	stable_sort(words.begin(), words.end(),
		[](const string& str1, const string& str2) -> bool { return str1.size() < str2.size(); });
	cout << "after stable_sort: " << endl;
	for_each(words.begin(), words.end(), [](const string& str) -> void { cout << str << " "; });
	cout << endl;
	cout << "===============================================" << endl;

	// 将重复内容放到vector末尾
	vector<string>::iterator ite_notUnique =  unique(words.begin(), words.end());
	// 删除重复内容
	words.erase(ite_notUnique, words.end());
	cout << "after unique + erase: " << endl;
	for_each(words.begin(), words.end(), [](const string& str) -> void { cout << str << " "; });
	cout << endl;
	cout << "===============================================" << endl;

	// 找到第一个长度大于sz的单词的迭代器
	vector<string>::iterator firstIte = find_if(words.begin(), words.end(),
		[sz](const string& str) -> bool { return str.size() >= sz; });
	// 计算满足 string.size() >= sz 的字符串个数
	vector<string>::difference_type distance = words.end() - firstIte;
	auto lambda = [distance](const string& word, const string& ending) -> string
		{ return word + (distance > 1 ? ending : ""); };
	cout << distance << " " << lambda("word", "s") << " of length " << sz << " or longer" << endl;
	// 打印每一个长度大于等于sz的单词
	for_each(firstIte, words.end(), [](const string& str) -> void { cout << str << " "; });
	cout << endl;

	return;
}
```

### 运行结果

```
before any operation:
fox jumps over quick red red slow the the turtle
===============================================
after stable_sort:
fox red red the the over slow jumps quick turtle
===============================================
after unique + erase:
fox red the over slow jumps quick turtle
===============================================
3 words of length 5 or longer
jumps quick turtle
```

# lambda捕获和返回

当使用`auto`定义一个用lambda初始化的变量时，定义了一个从lambda生成的类型的变量

```cpp
int main()
{
	auto test = []() -> auto { cout << "hello world!" << endl; };
	test();
}

// 打印hello world!
```

当我们编写一个lambda后，编译器将该表达式翻译成一个未命名类的未命名对象。在这个类中含有一个重载的函数调用运算符。

```cpp
stable_sort(words.begin(), words.end(), 
	[](const string& str1, const string& str2)
		{ return str1.size() < str2.size(); });
```

```cpp
class ShorterString
{
public:
	bool operator()(const string& str1, const string& str2) const
	{
		return str1.size() < str2.size();
  }
};
```

他们两的行为是相似的。默认情况下，从lambda生成的类都包含一个对应该lambda所捕获的变量的数据成员。累死人和普通类的数据成员，lambda的数据成员也在lambda对象创建时被初始化。

## 值捕获

类似参数传递，变量的捕获方式也可以是值或引用。与传值参数类似，**采用值捕获的前提是变量可以拷贝**。**与参数不同，被捕获的变量的值是在lambda创建时拷贝，而不是调用时拷贝。**

<aside>
📌 **示例程序**

由于被捕获变量的值是在lambda创建时拷贝，因此随后对其修改不会影响到lambda内对应的值。

```cpp
void func1()
{
	size_t v1 = 42;
	auto f = [v1] { return v1; };
	v1 = 0;
	auto j = f();    // j = 42; f保存了我们创建它时v1的拷贝
}
```

</aside>

## 引用捕获

> **示例程序**
> 
> 
> ```cpp
> void fnnc2()
> {
> 	size_t v1 = 42;
> 	auto f2 = [&v1] { return v1 };
> 	v1 = 0;
> 	auto j = f2();    // j = 0; f保存的是引用而非拷贝
> }
> ```
> 

**引用捕获和返回引用有着相同的问题和限制。**如果我们采用饮用方式捕获一个变量，就必须确保被引用的对象在lambda执行的时候是存在。我们不能拷贝`ostream`对象，所以捕获其对象的唯一方法就是捕获其引用（或采用其指针，但是引用的本质其实也就是const指针）。

当我们向一个函数传递一个lambda时，其会立即执行。

我们可以从一个函数返回一个lambda。函数可以直接返回一个**可调用对象**，或者返回一个类对象，这个类含有**可调用的**数据成员。如果函数返回一个lambda，则与函数不能返回一个局部变量的引用类似，这个lambda不能包含引用捕获。

<aside>
📌 一般来说，我们应该尽量减少捕获的数据量，来避免潜在的捕获导致的问题。而且，如果可能的话，应该避免捕获指针或引用。

</aside>

## 隐式捕获

**除了我们显式地列出我们希望使用的来自所在函数的变量之外，我们还可以让编译器根据lambda体中的代码来推断我们要使用哪些变量。**为了指示编译器推断捕获列表，应当在捕获列表中写一个`&`或者`=`。`&`告诉编译器采用引用捕获方式，`=`则表示采用值捕获方式。

```cpp
// sz并不在捕获列表中，但是可以用隐式值捕获获取
wc = find_if(words.begin(), words.end(),
	[=](const string& s) { return s.size() >= sz; })
```

如果我们希望对一部分变量采用值捕获，对其他变量采用引用捕获，可以混合使用隐式捕获和显式捕获

```cpp
void biggies(vector<string>& words, vector<string>::size_type sz,
	ostream& os = cout, char c = ' ')
{
	// os隐式引用捕获，c显式值捕获
	for_each(words.begin(), words.end(), [&, c](const string& str) { os << s << c; });
	// os显式引用捕获，c隐式值捕获
	for_each(words.begin(), words.end(), [=, &os](const string& str) { os << s << c; })
}
```

**当我们混合使用隐式捕获和显式捕获时，捕获列表中的第一个元素必须是一个`&`或`=`。这个符号限定了默认捕获方式为引用捕获或值捕获。当混合使用隐式捕获和显式捕获时，显式捕获的变量必须使用与隐式捕获不同的方式。**意即，如果隐式捕获是引用方式，那么显式捕获就必须采用显式捕获。反之相同。

## 可变lambda

默认情况下，对于一个值被拷贝的变量，lambda不会改变其值。如果我们希望能改变一个被捕获的变量的值，就必须在**参数列表首**添加关键字`mutable`。因此，可变lambda能省略参数列表

```cpp
void func3()
{
	size_t v1 = 42;
	auto f = [v1] () mutable { return ++v1; }
	v1 = 0;
	auto j = f();    // j = 43
}
```

如果不设置的话，会有报错：

![Untitled](C++%20Primer/杂项/lambda表达式/Untitled.png)

![Untitled](C++%20Primer/杂项/lambda表达式/Untitled%201.png)

一个引用捕获的变量是否（和往常一样）可以修改依赖于此引用指向的是一个`const`类型还是一个还是一个非`cosnt`类型

```cpp
void func4()
{
	size_t v1 = 42;
	auto f2 = [&v1] { return ++v1; }
	v1 = 0;
	auto j = f2();    // j = 1
}
```

<aside>
📌 也就是说，对于值捕获，需要使用`mutable`来使其可以改变；而对于引用捕获，是否可以改变取决于是否是`const`

</aside>

## 指定lambda返回类型

lambda体是单一的`return`语句，返回一个条件表达式的结果。我们无须指定返回类型，编译器会自己推导。如果没有`return`语句，那么lambda的返回类型就是`void`

但是，当lambda体中有多个`return`语句的时候，编译器无法推导返回类型，会默认返回类型是`void`。如果这个时候我们返回了值，那么就会报错。当然，有的时候编译器做的足够好，也能够判断返回类型。

```cpp
int main()
{
        auto f1 = [](int i) { return (i >= 0) ? i : -i; };
        auto f2 = [](int i) {
                if (i >= 0) return i;
                else return -i;};

        return 0;
}
```

最好的方法是：`[](int i) → int { … }`

## 示例

> 编写一个lambda，捕获一个局部`int`变量，并递减变量值，直至它变为0。一旦变量为0，再调用lambda应该不再递减变量。lambda应该返回一个bool值，指出捕获的变量是否为0
> 

```cpp
int main()
{
        int i = 5;
        auto f = [i]() mutable -> bool { return (--i) > 0; };
        for ( int i = 0; f(); i++ )
        {
                cout << i << endl;
        }
}
```

# 参数绑定

普通函数和lambda表达式的比较：

- 普通函数：可以在多个地方反复使用，并且如果拥有多个语句，可读性更好
- lambda函数：可以捕获局部变量，这是lambda函数最强大的地方

就如同前文所说，我们希望写一个写执行对象，帮助`find_if`在`vector`中找到一个满足长度`sz`，并且我们可以自己设置`sz`的时候，我们就会发现这是无法实现的：

```cpp
// 函数本身很好实现
bool check_size(const string& s, string::size_type sz) { return s.size() >= sz; }
// 但我们无法用于find_if，因为find_if要求这个可执行对象只接受一个参数
find(words.begin(), words.end(), check_size);    // 错误
```

![报错信息](Untitled%202.png)

报错信息

为了使用`check_size`函数，我们必须解决如何传递`sz`，同时不需要传递两个参数的问题

## 标准库函数`bind`

> `#include <functional>`
> 

我们可以将`bind`函数看做一个通用的函数适配器，它接受一个可调用对象，生成一个新的可调用对象来“适应”原对象的参数列表

```cpp
auto newCallable = bind(callable, arg_list);
```

其中，`newCallable`本身是一个可调用对象，`arg_list`是一个逗号分割的参数列表，对应给定的`callable`参数。即，**我们调用`newCallable`的时候，`newCallable`会调用`callable`，并传递给它`arg_list`中的参数**

`arg_list`中的参数可能包含形如`_n`的名字，其中`n`是一个整数。这些参数是“占位符”，表示`newCallable`的参数，它们占据了传递给`newCallable`的参数的“位置”。数值`n`表示生成的可调用对象中参数的位置：`_1`为`newCallable`的第一个参数，`_2`为第二个，以此类推

## 绑定`check_size`中的`sz`参数

```cpp
auto check6 = bind(check_size, _1, 6);
string s = "hello";
bool b1 = check6(s); // check6(s)调用check_size(s, 6);
```

`bind`中只有一个占位符`_1`，这代表着生成的可执行对象`check6`只接受一个参数，而由于其在参数列表的第一个，这个参数用于被绑定对象`check_size`的第一个参数，也就是`const string&`。因此，调用`check6`必须传递一个字符串，而`check6`就会将这个字符串作为传递给`check_size`的第一个参数

那么原本的那个问题也就解决了：

```cpp
// lambda形式
auto wc = find_if(words.begin(),
                  words.end(),
                  [sz](const string& s)
                      { return s.size() >= sz; });
```

```cpp
// 普通函数形式
auto wc = find_if(words.begin(),
                  words.end(),
                  bind(check_size, _1, sz));
```

## placeholders

名字`_n`都定义在一个名为`placeholders`的命名空间中，而这个空间本身定义在`std`命名空间中。与`bind`一样，这个子命名空间被定义在`functional`头文件中

```cpp
using namespace std::placeholders;
```

## `bind`的参数

如前文所述，我们可以用`bind`修正参数的值，更一般的，我们可以用`bind`重排调用对象的参数顺序

```cpp
// 假定有函数f
void f(arg1, arg2, arg3, arg4, arg5);
// 使用bind绑定f
auto g = bind(f, a, b, _2, c, _1);
```

这里生成的新的可调用对象，有两个参数，分别用`_1`和`_2`表示。传递给`g`的两个参数，传给`f`作为第三个参数和第五个参数。

但需要注意的是，传递给`g`的参数按位置绑定到占位符。即，`g`的第一个参数绑定到`_1`，`g`的第二个参数绑定到`_2`。因此，实际调用中，真实的情况是这样的：

```cpp
g(_1, _2);
// 映射为
f(a, b, _2, c, _1);

// 实际调用
g(X, Y);
f(a, b, Y, c, X);
```

## 利用`bind`的参数重排实现额外功能

回顾之前写的函数：

```cpp
bool isShorter(const string& str1, const string& str2) { return str1.size() < str2.size(); }
```

利用这个函数，我们可以实现对一个容器的从小到大排序：

```cpp
sort(words.begin(), words.end(), isShorter);
```

但是，利用`bind`，我们就可以用极小的改动，实现**从大到小**排序：

```cpp
sort(words.begin(), words.end(), bind(isShorter, _2, _1));
```

## 使用`bind`绑定引用参数

默认情况下，`bind`是的那些不是占位符的参数被拷贝到`bind`返回的可调用对象中。但是，与lambda类似，有时对有些绑定的参数我们希望以引用方式传递，或是要绑定参数类型无法拷贝（例如`cout`）。

例如以下这个例子，我们可以用lambda实现对一个`vector`的元素的遍历输出，并添加一个字符：

```cpp
// os是一个局部变量，引用一个输出流
// c是一个局部变量，类型为char
for_each(words.begin(), words.end(), 
    [&os, c](const string& s) { os << s << c; });
```

对于lambda的功能，我们可以很轻松用一个普通函数实现：

```cpp
ostream& print(ostream& os, const string& s, char c)
{
	return os << s << c;
}
```

但是，我们却不能用`bind`直接代替对`os`的捕获：

```cpp
// 错误：不能拷贝os
for_each(words.begin(), words.end(), bind(print, os, _1, ' '));
```

为了实现对`os`的引用，我们需要使用标准库函数`ref`和`cref`： 

```cpp
for_each(words.begin(), words.end(), bind(print, ref(os), _1, ' '));
```

- `ref`返回一个对象，包含给定对象的引用，**并且这个返回的对象是可以拷贝的**
- `cref`返回一个保存`const`引用的对象

同样的，这两个函数定义在`functional`头文件中

## 关于`bind`的备注

在旧版C++中，有与`bind`功能类似，但是不如其强大的`bind1st`和`bind2nd`。与`bind`相同，这两个函数接收一个函数作为参数，生成一个新的可调用对象，该对象调用给定函数，并将绑定的参数传递给它。但是，这些函数分别只能绑定第一个或者第二个参数，由于局限性太强，现在已经不再使用，现在应当使用`bind`