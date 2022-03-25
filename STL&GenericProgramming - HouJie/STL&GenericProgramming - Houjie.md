# STL与泛型编程

> C++标准库 - 体系结构与内核分析
>
> 使用一个东西,却不明白它的道理,不高明!

## 引入

### 应该具备的基础

- C++基本语法(包括如何正确使用模板,template)



### 目标

1. level 0 : 使用C++标准库
2. level 1 : 认识C++ 标准库(***胸中有丘壑***)
3. level 2 : 良好使用C++标准库
4. level 3 : 扩充C++标准库(不是很必要)



### C++ Standard Library *vs*. Standard Template Library

 在整个C++标准库中,STL占据了70~80%的部分. 而STL又由六大部件组成



标准库以head files形式呈现

- C++标准库的head file不带`.h`, 例如`#include<vector>`
- 新的C head files不带`.h`, 例如`#include<cstdio>`
- 旧的C head files带`.h`, 例如`#include<stdio.h>`



### 重要网页

1. http://www.cpluscplus.com
2. http://cppreference.com
3. https://gcc.gnu.org



### 书推荐

1. ***The C++ Standard Library - A Tutorial and Reference***
2. ***STL源码剖析***

## STL体系结构基础介绍

### ***STL六大部件（Components）***

- 容器（Containers）
- 分配器（Allocators）
- 算法（Algorithms）
- 迭代器（Iterators）
- 适配器（Adapters）
- 仿函数（Functors）

```mermaid
flowchart TD;
subgraph  Container Adapters
	容器Containers
end
subgraph  Iterator Adapters
	迭代器Iterators
end
subgraph Functor Adapters
	仿函数Functors
end
算法Algorithms --> 迭代器Iterators --> 容器Containers
分配器Allocator --分配空间--> 容器Containers
仿函数Functors --> 算法Algorithms
```

******

### ***复杂度（Complexity，Big-oh）***

目前常见的Big-oh有下列几种情形（n必须是一个很大的数量）：

1. $$
    O(1) / O(c)：称为常数时间（constant\; time）
    $$

2. $$
    O(n)：称为线性时间（linear\; time）
    $$

3. $$
    O(log_{2}{n})：称为次线性时间(sub-linear\; time)
    $$

4. $$
    O(n^2)：称为平方时间（quadratic\;time）
    $$

5. $$
    O(n^3)：称为立方时间（cubic\; time）
    $$

6. $$
    O(2^n)：称为指数时间(exponential\; time)
    $$

7. $$
    O(nlog_{2}{n})：介于线性及二次方成长的中间的行为模式
    $$

******

### “前闭后开”区间

### range-based for statement (since C++11)

```c++
for(decl : coll) 	//decl:declaration	coll:collection
{
    statement
}
```

```c++
std::vector<double> vec;

//在不需要操作元素本身的时候不需要引用（详见《C++ Primer(5th edition)》）
for( auto elem : vec)
{
    std::cout << elem << std::endl;
}
//在需要操作元素本身的时候使用引用
for( auto& elem : vec )
{
    elem *= 3;
}
```

******

### auto keyword

原本写法：

```c++
list<string> c;
...
list<string>::iterator ite;
ite = ::find(c.begin(), c.end(), target);
```

C++11写法：

```c++
list<string> c;
...
auto ite = ::find(c.begin(), c.end(), target);
```

## 容器之分类与各种测试

### 容器——结构与分类

```mermaid
flowchart LR;
subgraph C++11
		Array
		Froward-List
		subgraph HSC[HashTable Separate Chaining]
			uSet[Unorded Set/Multiset]
			uMap[Unorded Map/Multimap]
		end
end
subgraph Sequence Containers
	Vector
	Deque
	List
end
subgraph AC[Associative Containers, using <strong><i>Red/Black Tree</i></strong>]
	Set
	Multiset
	Map
	Multimap
end

Array --> desArray[fixed number of elements]
HSC --> hash[HashTable Separate Chaning, 存放在bucket]
Set --> des[value is key]
Multiset --> des
Map --> des1[key / value]
Multimap --> des1
Set & Map ==> Unique
Multiset & Multimap ==> Ordinary
```

### 使用容器

#### 写测试程序的习惯

1. 将一段独立的单元放在一段独立的命名空间中
2. 将包含的头文件放在命名空间的上面
3. 在用到变量的时候再去声明，并且与其他代码之间少一个tab，方便寻找

## 分配器的测试

***GNU额外附加的allocator：***

1. `<ext\array_allocator.h>`
2. `<ext\mt_allocator.h>`，多线程allocator
   `list<string, __gnu_cxx::__mt_alloc<stirng> >`
3. `<ext\debug_allocator.h>`，debug用allocator
4. `<ext\pool_allocator.h>`，优化过的allocator，详见[后文](#pool_allocator)
   `__gnu_cxx::__pool_alloc`
5. `<ext\bitmap_allocator.h>`，哈希表allocator
   `__gnu_cxx:bitmap_allocator`
6. `<ext\malloc_allocator.h>`
7. `<ext\new_allocator.h>`

## 体系结构与内核分析

### ***OOP(Object-Oriented Programming) vs. GP(Generic Programming)***

***采用GP的优势：***

- Containers和Algorithms团队可以各自开发，其间以Iterator沟通即可
- Algorithms通过Iterators确定操作范围，并通过Iteratos取用Container元素

### 技术基础 - 操作符重载&模板泛化、全特化、偏特化

> 书目推荐：《*C++ Templates - The Complete Guide*》

#### 特化

> 对一个模板的完整特化

```cpp
// 泛化
template <class Key> struct hash {  };

// 特化
typedef __STL_TEMPLATE_NULL template<>;

__STL_TEMPLATE_NULL struct hash<char>
{
	size_t operator() (char x) const { return x; }
};

```

#### 偏特化（*Partial Specialization*）

##### 对模板参数个数的局部特化

```cpp
// 泛化
template <class T, class Alloc = alloc>
class vector
{
	// ...
};

// 偏特化
// 特化其中一个，剩下一个模板保留
template <class Alloc>
class vector<bool, Alloc>
{
	// ...
}
```

##### 对模板参数范围的局部特化

```cpp
// generalization
template <class Iterator>
struct iterator_traits
{
	typedef typename Iterator::iterator_category	iterator_category;
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
};

// partial specialization
// 对指针进行偏特化
template <class T>
struct iterator_traits<T*>
{ 
	typedef random_access_iterator_tag	iterator_category;
	typedef T							value_type;
	typedef ptrdiff_t					difference_type;
	typedef T*							pointer;
	typedef T&							reference;
};

template <class T>
struct iterator_traits<const T*>
{ 
	typedef random_access_iterator_tag	iterator_category;
	typedef T							value_type;
	typedef ptrdiff_t					difference_type;
	typedef const T*					pointer;
	typedef const T&					reference;
};

```

### 分配器 - *allocator*

#### 先谈`operator new()`和`malloc()`

> 所有的C++ `new` 最终都会回到`operator new()`
>
> 所有的申请空间的代码，最终都会回到`malloc()`函数 ***memory allocation***
> 所有的释放空间的代码，最终都会回到`free()`函数

<a name="malloc申请到的内存空间"></a>

![malloc申请到的内存空间](STL&GenericProgramming - Houjie.assets/malloc().png)

<center>malloc申请到的内存空间样式</center>

1. 用户所申请的空间是浅蓝色`size`的部分
2. 灰色的部分是debug mode下添加的
3. 红色的部分是cookie
4. 调整后添加边界pad，也就是绿色的部分

***malloc提供给我们的空间超过我们申请的空间，所申请的空间越大，多余部分所占的内容越少。因此，申请空间<F9>越大，对内存的浪费越少***

#### 分配器`allocators`

##### VC6 version

***VC6 STL对allocator的使用***

```cpp
template <class _Ty, class _A = allocator<_Ty> >
class vector
{
//...
};
```

***VC6 STL对allocator的实现***

```cpp
#ifndef _FARQ
	#define _FARQ
	#define _PDFT	ptrdiff_t
	#define _SIZT	size_t
#endif
	#define _POINTER_X(T, A)	T_FARQ *
	#define _REFERENCE_X(T, A)	T_FARQ &

template<class _Ty> inline
_Ty _FARQ *_Allocate(_PDFT _N, _Ty _FARQ *)
{
	if (_N < 0) _N = 0;
	return ((_Ty _FARQ*)operator new((_SIZT)_N * sizeof (_Ty)));
}

template<class _Ty>
{
public:
	typedef _SIZT size_type;
	typedef _PDFT difference_type;
	typedef _Ty _FARQ *pointer;
	typedef _Ty value_type;
	// =========================================================
	// allocator最重要的两个函数
	pointer allocate(size_type _N, const void *)
	{
		return (_Allocate((difference_type)_N, (pointer)0));
	}
	void deallocate(void _FARQ *_P, size_type)
	{
		operator delete(_P);
	}
	// =========================================================
};
```

具体使用：[Allocators测试](./testCode/1_test_allocator_VC6.cpp)

- `allocate()`函数的第二个参数没有类型，传参仅仅是为了知道想要**申请什么样的数据**
- `deallocate()`函数要求传入当初申请的数据的个数。这是不合理的，没有人会去记住当初申请了多少个元素，我们只会知道指针。但是如果是容器来使用，一切就会变得非常方便

##### BC5 version

***BC5 STL对allocator的使用***

```cpp
// in <stdcomp.h>
#define _RWSTD_COMPLEX_DEFAULT(a) = a

template <class T, class Allocator = _RWSTD_COMPLEX_DEFAULT(allocator<T>) >
class vector ...

// 等价于
template <class T, class Allocator = allocator<T> >
class vector ...
```

***BC5 STL对allocator的实现***

> BC++的allocator只是以::operator new和::operator delete完成allocate()和deallocate()，没有任何特殊设计

```cpp
// in <memory.stl>
template <class T>
class allocator
{
public:
	typedef size_t		size_type;
	typedef ptrdiff_t	difference_type;
	typedef T*			pointer;
	typedef T&			reference;

	pointer allocate(size_type n, allocator<void>::const_pointer = 0)
	{
		pointer tmp = 
			_RWSTD_STATIC_CAST(pointer, (::operator new(_RWSTD_STATIC_CAST(size_t, (n * sizeof(value_type))))));
		_RWSTD_THROW_NO_MSG(tmp == 0, bad_alloc);
		return tmp;
	}
	void deallocate(pointer p, size_type)
	{
		::operator delete(p);
	}
}
```

具体使用：[Allocators测试](./testCode/1_test_allocator_BC5.cpp)

##### 小结

1. 不管是VC, BC还是GNU C，allocator最后还是回到malloc，这就决定了，如果我们放入容器的元素很小，会导致额外开销很大，令人不能忍受
2. 不要单独使用Allocator
   > G++ <defalloc.h>中有这样的注释：
   > DO NO USE THIS FILE unless you have an old container implementation that requires an allocator with the HP-style interface.
   > SGI STL uses a different allocator interface. SGI-style allocator are not parametrized with respect to the object type; they traffic in void* pointers.
   > THIS FILE IS NOT INCLUDED BY ANY OTHER HEAD FILE
3. 由此可见，并没有使用这个Allocator，而是有更好的设计的分配器。也就是
   `template <class T, class Alloc = alloc> vector` 中的`alloc`

#### `alloc` of G2.9

![`alloc` for G2.9](./STL&GenericProgramming - Houjie.assets/G2.9_alloc.png)

<center><b><i>G2.9下的`alloc'</i></b></center>

> 根本思想： ***尽量减少malloc的次数，进而减少malloc带来的额外开销***

回顾[malloc申请到的内存空间样式](#malloc申请到的内存空间)，cookie中记录的是申请到的整个空间的大小，因此在归还指针的时候不需要知道空间的大小, free会去查看cookie中的数据，从而决定需要回收多大的空间
   - 考虑到容器：容器的每个元素的大小是固定的，这样就不需要记录每个元素的大小。所以，在容器的应用情况下，可以不需要cookie，尽量减少malloc次数
   - 具体的实现方法：
      1. 设计16条链表，每一条链表负责某一种特定大小的区块，用链表穿起来
	  2. #n负责`(n + 1) * 8`个字节大小的元素
   - 所有的容器需要内存的时候，都来向allocators申请空间
   - 容器的元素大小一般都会被拓展到8的倍数，如果容器为元素申请的空间大小不符合任何的链表，allocators就会使用`malloc`向操作系统申请一大块空间，将申请到的空间切分成小块，并且把这个空间用单向链表连接起来。这样的小块就不带有cookie。
   - 同时，因为在malloc申请到的内存中，最上层和最下层都有cookie，每一个cookie 4个字节。所以每一个元素都有8个字节的多余空间

##### G4.9下的allocator

> 纵使如前文所述，`alloc`是非常有效的设计，G4.9并没有使用这个版本，而是使用了`allocator`

###### G4.9 STL对allocator的使用

```cpp
template <typename _Tp, typename _Alloc = std::allocator<_Tp> >
class vector : protected _Vector_base<_Tp, _Alloc>
{
	// ...
};
```

###### G4.9 STL对allocator的实现

```cpp
template <typename _Tp>
class new_allocator
{
	// ...
	pointer allocate(size_type __n, const void* = 0)
	{
		if (__n > this->max_size())
			std::__throw_bad_alloc();
		return static_cast<_Tp*>(::operator new(__n * sizeof(_Tp)));
	}

	void deallocate(pointer __p, size_type)
	{
		::operator delete(__p);
	}
	
	// ...
};

// in <bits/c++allocator.h>
#define __allocator_base __gnu_cxx::new_allocator


template<typename _Tp>
class allocator : public __allocator_base<_Tp>
{
	// ...
};
```

###### 结论

> G4.9 抛弃了已经设计好的很棒的设计，而重回了原来的版本

<a name="pool_allocator"></a>

G2.9版本的`alloc`仍然还在。G4.9所附的标准库，有许多extention allocators，其中`__pool_alloc`就是G2.9的`alloc`

```cpp
class __pool_alloc_base
{
protected:
	enum { _S_align = 8 };
	enum { _S_max_bytes = 128 };
	enum { _S_free_list_size = (size_t)_S_max_bytes / (size_t)_S_align };

	union _Obj
	{
		union _Obj*	_M_free_list_link;
		char		_M_client_data[1];		// The client sees this
	};

	static _Obj* volatile	_S_free_list[_S_free_list_size];

	// ...
};

template<typename _Tp>
class __pool_alloc : private __pool_alloc_base
{
	// ...
};
```
## 容器的深度探索

### 容器之间的实现关系与分类

![容器，结构与分类](./STL&GenericProgramming - Houjie.assets/容器，结构与分类.png)

<center><b><i>sizeof()中的大小指的是容器自己的大小，与其中装的元素的大小没有关系</i></b></center>

### 深度探索list

> 最简单的容器是array，但是list是最具代表性的容器

![容器list](./STL&GenericProgramming - Houjie.assets/list.png)

```cpp
template <class T, class Alloc = alloc>
class list
{
protected:
	typedef __list_node<T> list_node;
public:
	typedef list_node* link_type;
	typedef __list_iterator<T,T&,T*> iterator;
protected:
	link_type node;

	// ...
}
```

1. 整个list唯一的数据成员就是`node`，为了知道`link_type`到底是什么，我们需要向上寻找，发现`link_type`是一个指针。由此我们也就知道了整个容器的大小就是一个指针，4个byte。所以，如果我们对一个list对象进行`sizeof()`，最后得到的结果是4。
2. 再来看节点本身`list_node` ：
	```cpp
	template <class T>
	struct __list_node
	{
		typedef void* void_pointer;
		void_pointer prev;
		void_pointer next;
		T data;
	}
	```
	我们可以发现，指针的类型是`void *`，也就是说在实际的程序运作中是需要转型的。***这样不是很理想***。
	同时，每一个元素申请的元素大小，除了`data`的大小本身，还有两根指针。
3.	再来看`iterator`,我们希望iterator的运行类似指针，但是一定要比指针“聪明：当我们使用`iterator++`的时候，我们希望的是挪到下一个元素的位置，而不是向后挪4个byte。所有的容器，除了array和vector，都必须是一个class，才能设计出聪明的iterator
	```cpp
	template <class T, class Ref, class Ptr>
	struct __list_iterator
	{
		// 几乎所有的容器都有五个typedef
		typedef __list_iterator<T, Ref, Ptr>	self;
		typedef bidirectional_iterator_tag		iterator_category;	//(1)
		typedef T								value_type;			//(2)
		typedef Ptr								pointer;			//(3)
		typedef Ref								reference;			//(4)
		typedef __list_node<T>*					link_type;
		typedef ptrdiff_t						difference_type;	//(5)

		link_type node;
		
		// 模拟指针的操作
		reference operator*() const { return (*node).data; }
		pointer operator->() const { return &(operator*()); }
		self& operator++()
			{ node = (link_type) ((*node).next); return *this; }
		self  operator++(int)
			{ self tmp = *this; ++*this; return tmp; }
	}
	```
4.	对iterator进行提领
	
	> 当我们对某个type实施`operator->`，而该type并非 build-in ptr时，编译器会做一件很有趣的事：
	>
	> 在找出`user-defined operator->`并将它施行于该type后，编译器会对执行结果再次施行`operator->`。
	>
	> 编译器会不断执行这个动作直到触及`pointer to a build-in type`，然后才进行成员存取
