# 1	虚函数表指针位置分析

> 如果一个类中有虚函数，则针对这个类会产生一个虚函数表
>
> **注：基于不同的实验平台，实验的结果可能不同，但是核心思想是相同的**
>
> ```shell
> > g++ -v
> Apple clang version 14.0.0 (clang-1400.0.29.202)
> Target: arm64-apple-darwin22.1.0
> Thread model: posix
> InstalledDir: /Library/Developer/CommandLineTools/usr/bin
> ```

生成虚函数表的时候，该对象中就会有一个虚函数表指针用来指向这个虚函数表的起始地址。这个指针可以看成类中的成员变量，也占一定的字节数（一般是4字节或8字节）。通常会将这个这个指针存放在对象的开头或者末尾。

参考下面的代码：

[***1_where_is_virtual_funcPointer.cpp***](./1_virtualFunctionCodes/1_where_is_virtual_funcPointer.cpp)

```c++
#include <cstdio>
#include <iostream>

using namespace std;

class Normal
{
        long data;
};

class Virtual
{
public:
        long data;
        virtual void func() { cout << "I'm virtual class" << endl; }
};

int main()
{
        printf("size of class Normal: %zu\n", sizeof(Normal));
        printf("size of class Virtual: %zu\n", sizeof(Virtual));
        Virtual v;
        printf("Offset of member data: %zu\n", reinterpret_cast<char*>(&(v.data)) - reinterpret_cast<char*>(&v));
}
```

在上面的代码中，我们使用了一个不包含虚函数的类`Normal`和一个包含虚函数的类`Virtual`。相同的地方是，他们都有一个长整型的数据成员。至于此处为什么不是整型，此处涉及到内存对齐，不过多展开。

以下是运行结果：

```
size of class Normal: 8
size of class Virtual: 16
Offset of member data: 8
```

于是我们可以引出关于虚函数指针的第一个性质：

<center><b><i>===== 虚函数指针位于对象内存的开头。 =====</i></b></center>

对于Windows，Linux和Darwin，他们都位于对象内存的开头，对于其他平台，可以使用上面的方法验证。

# 继承关系作用下虚函数的手工调用

