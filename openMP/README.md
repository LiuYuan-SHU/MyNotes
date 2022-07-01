# OpenMP Notes

> [Excellent Free Tutorials to Learn OpenMP](https://www.linuxlinks.com/excellent-free-tutorials-learn-openmp/)
>
> [OpenMP API 用户指南](./OpenMP API 用户指南.pdf)

[TOC]

## [OpenMP by Blaise Barney](https://hpc-tutorials.llnl.gov/openmp/)

### Parallel Construct

> A parallel region is a block of code that will be executed by multiple threads. This is the fundamental OpenMP parallel construct.

When a thread reaches a PARALLEL directive, it creates a team of threads and becomes the master of the team. The master is a member of that team and has thread number 0 within that team.

Starting from the beginning of this parallel region, the code is duplicated and all threads will execute that code.

There is an implied barrier at the end of a parallel section. Only the master thread continues execution past this point.

If any thread terminates within a parallel region, all threads in the team will terminate, and the work done up until that point is undefined.

***Format***

```c++
#pragma omp parallel [clause ...]  newline 
                     if (scalar_expression) 
                     private (list)
                     shared (list) 
                     default (shared | none) 
                     firstprivate (list) 
                     reduction (operator: list) 
                     copyin (list) 
                     num_threads (integer-expression)

 
   structured_block
```

***How many threads?***

The number of threads in a parallel region is determined by the following factors, in order of precedence:

1. Evaluation of the `IF` clause
2. Setting of the `NUM_THREADS` clause
3. Use of the `omp_set_num_threads()` library function
4. Setting of the `OMP_NUM_THREADS` environment variable
5. Implementation default - usually the number of CPUs on a node, though it could be dynamic.

Threads are numbered from $0$ (master thread) to $N-1$.

***Restrictions***

* A parallel region must be a structured block that does not span multiple routines or code files.

* It is illegal to branch (`goto`) into or out of a parallel region.

* Only a single IF clause is permitted.

* Only a single `NUM_THREADS` clause is permitted.

* A program must not depend upon the ordering of the clauses.

#### 工作共享构造

>工作共享构造在遇到该构造的线程组成员中分配封装代码区域的执行。要使工作共享构造以并行方式执行，构造必须封装在并行区域内。

##### **DO** 和 **for** 构造

> 指定随后的 **DO** 或 **for** 循环的迭代必须以并行方式执行。

```c++
#pragma omp for [clause[[,]clause]...]
for-loop
```

**for** pragma 指定其后紧跟的 for- *循环*的迭代应以并行方式执行。此 pragma 必须出现在并

行区域内才有效。 **for** pragma 对相应 **for** 循环的结构有限制，且必须有*规范形状*：

`for (initexpr; var logicop b; increxpr)`

其中：

*  `initexpr` 为以下之一：
    
    * `var = lb`
    * `integer_type var = lb`
    
* `increxpr` 为以下表达式形式之一：

    * `++var`

    * `var++`

    * `--var`

    * `var--`

    * `var += incr`

    * `var -= incr`

    * `var = var + incr`

    * `var = incr + var`

    * `var = var - incr`

        

* `var` 是有符号整型变量，被隐式设置为供 **for** 范围专用。切勿修改 **for** 语句体内的`var`。除非指定 **`lastprivate`**，否则其值在循环后不确定。

* `logicop` 为以下逻辑操作符之一：

$$
< <= > >=
$$

* `lb`、` b `和 `incr `是循环不变量整型表达式。

对 < 或 <= 和 > 或 >= 作为 **for** 语句中的` logicalop `使用尚有其它限制。有关详细信息，参见OpenMP C/C++ 规范。



##### **SECTIONS** 构造

> **SECTIONS** 构造用于封装要在组内的线程中分配的非迭代代码块。每个块由组内的线程执行一次。
>
> 每段均以 **SECTION** 指令开头，该指令对第一段为可选指令

示例代码可见[此处](./Exercises/exercise1/3. omp_workshare2.c)

```cpp
#pragma omp sections [clause1, clause2, ...]
{
    [#pragma omp section]
    { /*非迭代代码*/}
}

```



##### SINGLE构造

> 使用 **SINGLE** 封装的结构化块只由组内的一个线程来执行。除非指定 **NOWAIT**，否则组内未在执行 **SINGLE** 块的线程会在块结尾处等待。

```c++
#pragma omp single [clause[[,] clause]...]
{
    /*单独执行代码*/
}
```



#### 子句含义

> [笔记来源](https://blog.csdn.net/qq_37206769/article/details/89189780)

##### collapse

在一些情况下，collapse 能够解决线程间[负载均衡](https://so.csdn.net/so/search?q=负载均衡&spm=1001.2101.3001.7020)或线程负载太小的问题。假设有一个双层循环，外层循环次数都比较少，内层循环的计算量也不大。单独使用OpenMP线程化内层循环都会存在负载不够的问题，即每个线程的计算量比较小，导致线程的计算时间相比线程的建立、销毁时间不够长；单独使用OpenMP线程化外层循环则会存在负载均衡问题。

`collapse(n)`表示紧随其后的 n 层循环会被合并然后并行化。简而言之，就是将接下来的n层循环展开成一个语句，然后执行本来应当执行的次数

```cpp
#pragma omp parallel for collapse(2)
for (int i = 0; i < 3; i++)
{
    for (int j = 0; j < num; j++)
    {
        vector[i][j] = ...;
    }
}
```

collapse(2)表示同时线程化接下来的两层循环，这样循环次数就变成了$3 × num$，这既改善了负载均衡性，又增加了每个线程的计算量。

##### private

private将一个或多个变量声明成线程私有，每个线程都会拥有该变量的一个副本，且不允许其他线程染指。private子句声明的变量的初始值在并行区域的入口处是未定义的，即使并行区域外已经给予了值也不会初始化为在并行区域前同名的共享变量值。一般而言，private声明的变量都可以使用线程私有栈上的变量替代。另外，出现在reduction子句中的参数不能出现在private子句中。

```cpp
#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int x = 5;
    printf("x = %d, address of x = %p\n", x, &x);
#pragma omp parallel num_threads(3) private(x)
	{
    	printf("i am %d, x = %d, address of x = %p\n", omp_get_thread_num(), x, &x);
	}
    printf("x = %d, address of x = %p\n", x, &x);
    return 0;
}
```

***输出：***

```
x = 5, address of x = 000000000065FE1C			// 开启多线程前
// 开启多线程
i am 0, x = 0, address of x = 000000000065FD6C
i am 1, x = 0, address of x = 000000000130FDFC
i am 2, x = 0, address of x = 000000000150FDFC
// 多线程结束
x = 5, address of x = 000000000065FE1C
```

从输出可以看出，并行区域内x的值和并行区域外毫无关系，而并行区域前后两者又是一样的。

##### firstprivate

private变量不能继承并行区域前同名变量的值，但实践中有时需要初始化为原有共享变量的值，OpenMP提供了`firstprivate`子句来实现这个功能。`firstprivate`指定的变量每个线程都有它自己的私有副本，并且继承主线程中的初值（并行区域前的值）。`firstprivate` 子句并不会更改原共享变量的值。

```cpp
#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int x = 5;
#pragma omp parallel num_threads(3) firstprivate(x)
	{
		printf("i am %d, x = %d\n", omp_get_thread_num(), x);
		x++;
	}
    printf("x = %d\n", x);

    return 0;
}
```

***输出***

```
// 线程间的变量彼此不影响
i am 0, x = 5
i am 1, x = 5
i am 2, x = 5
// 线程对私有变量的操作不影响开启前的变量值
x = 5
```

##### lastprivate

```cpp
#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int x = 5;
#pragma omp parallel for num_threads(3) lastprivate(x)
    for(int i = 0; i < 3; i++)
    {
        x = 36;
        printf("i am %d, %d\n", omp_get_thread_num(), x+=i);
    }

    printf("x = %d\n", x);

    return 0;

}
```

***输出***

```
i am 0, 36
i am 1, 37
i am 2, 38
x = 38		// 在结束后将值复制给x
```

从结果可以看出，退出for循环的并行区域后，共享变量x的值发生了改变，而不是保持原来的值不变。

由于并行区域内有多个线程并行执行，因此最后到底是将哪个线程的最终计算结果赋给了对应的变量是一个问题。如果是for循环，那么是最后一次循环计算得到的值；如果是section构造，那么是最后一个section语句中计算得到的值。

##### shared

shared子句用来声明一个或多个变量是共享变量。需要注意的是，由于在并行区域内的多个线程都可以访问共享变量，因此必须对共享变量的写操作加以保护。为了提高性能，应尽量使用私有变量而不是共享变量。

循环迭代变量在for循环并行区域内是私有的。声明在循环构造区域内的自动变量都是私有的。

##### default

default子句用来指定并行处理区域内没有显式指定访问权限的变量的默认访问权限，其取值有shared和none两个。指定为shared表示在没有显式指定访问权限时，传入并行区域内的变量访问权限为shared；指定为none意味着必须显式地为这些变量指定访问权限。

在某些情况下，OpenMP默认变量访问权限会导致一些问题，如需要private访问权限的数组被默认成shared了。故建议显式地使用default(none)来去掉变量的默认访问权限。

##### reduction

reduction子句用来在运算结束时对并行区域内的一个或多个参数执行一个操作。每个线程将创建参数的一个副本，在运算结束时，将各线程的副本进行指定的操作，操作的结果赋值给原始的参数。

reduction支持的操作符是有限的，支持+ - * / += -= *= /= |&^，且不能是C++重载后的运算符，具体可参见OpenMP规范。

```cpp
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

long double computePI(int numThread, int num)
{
	long double PI = 0.0;
	const double delta = 1.0/(numThread*num);
#pragma omp parallel for num_threads(numThread) reduction(+:PI)
	for(int i = 0; i < num*numThread; i++)
	{
		double x = (0.5+i)*delta;
		PI += 1.0/(1+x*x);
    }

    return PI*delta*4;
}

int main(int argc, char *argv[])
{
    int numThread, num;
	if(argc != 3)
    {
		printf("usage: ./a.out numThread computeNum\n");
		return 1;
	}
	else
	{
		numThread = atoi(argv[1]);
		num = atoi(argv[2]);
		printf("use thread %d, every thread compute times %d\n", numThread, num);
		if(0 <= numThread || 0 <= num)
         {
           	 printf("input data format error\n");
			return 1;
		 }
    }

	clock_t s = clock();
	double PI = computePI(numThread, num);
	clock_t e = clock();

	printf("PI is %1.15lf, use clock %ld\n", PI, e-s);

	return 0;
}

```

***输出***

```
$ ./test.exe 24 10000000
use thread 24, every thread compute times 10000000
PI is 3.141592653589814, use clock 46
```

##### schedule

***测试代码***

```cpp
#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
#pragma omp parallel for num_threads(3) schedule(schedule_style, 2)
// #pragma omp parallel for num_threads(3) schedule(runtime)
	for(int i = 0; i < 300; i++)
    {
    	printf("i am %d, i = %d\n", omp_get_thread_num(), i);
	}
    
    return 0;
}
```

***编译方式***

```
g++ -fopenmp -Dschedule_style=<策略> test.cpp
如果采用的是runtime策略，那么将第一个宏注释，启用第二个
```



schedule子句指定采取的负载均衡策略及每次分发的数据大小。其使用方式如下：`schedule(type <,size>)`。其中，size参数是可选的

* type参数表示负载均衡策略，主要有4种：dynamic、guided、static和runtime。实际上只有static、dynamic、guided三种方式，runtime指的是根据环境变量的设置来选择前3种中的某一种。

* size参数表示每次分发的循环迭代次数，必须是整数。3种策略都可用可不用size参数。当type为runtime时，需要忽略size参数。

###### 静态负载均衡策略（static）

[输出](./Test/子句含义/schedule/static.txt)

当编译指导语句没有指定schedule子句时，大部分系统中默认采用static，static方式使用的算法非常简单。

假设有从0开始的N次循环迭代，K个线程，如果没有指定size参数，那么给第一个线程分配的迭代为$[0，N/K]$。因为$N/K$不一定是整数，因此存在着轻微的负载均衡问题；如果指定size参数的话，那么分配给第一个线程的是$[0，size-1]$， 第K个线程的是$[size*K，size*K+size-1]$其他线程类推，直到分配完循环迭代。

###### 动态负载均衡策略（dynamic）

[输出](./Test/子句含义/schedule/dynamic.txt)

动态负载均衡策略动态地将迭代分发到各个线程。当线程计算完时，就会取得下一次任务。在静态负载均衡策略失效时，使用动态负载均衡策略通常可以得到性能提升。

动态负载均衡的机制类似于工作队列，线程在并行执行的时候，不断从这个队列中取出相应的工作完成，直到队列为空为止。由于每一个线程在执行的过程中的线程标识号是不同的，可以根据这个线程标识号来分配不同的任务。OpenMP中动态负载均衡时，每次分发size个循环计算，而队列中的数据就是所有的循环变量值。

动态负载均衡策略可用可不用size参数，不使用size参数时等价于size为1。使用size参数时，每次分配给线程的迭代次数为指定的size次。

选择size参数时，要注意伪共享问题。通常要使得每个线程从内存中加载的数据大小可以占满一个缓存线。

###### 指导负载均衡策略（guided）

[输出](./Test/子句含义/schedule/guided.txt)

guided负载均衡策略采用启发式自调度方法。开始时每个线程会分配较大的循环次数，之后分配的循环次数会逐渐减小。通常每次分配的循环次数会指数级下降到指定的size大小，如果没有指定size参数，那么最后会降到1。

###### 运行时负载均衡策略（rumtime）

[输出](./Test/子句含义/schedule/runtime.txt)

runtime是指在运行时根据环境变量OMP_SCHEDULE的值来确定负载均衡策略，最终使用的负载均衡策略是上述3种中的一种。

##### if

子句if提供了一种由运行时决定是否并行的机制，如果if条件为真，并行区域会被多个线程执行，否则只由一个线程执行。

```cpp
#pragma omp parallel for num_threads(3) if(x <= 5)
```



### exercise1

> [files](./Exercises/exercise1)

#### 常用API总结

> 此部分来源于[OpenMP API 用户指南](./OpenMP API 用户指南.pdf)

##### **OMP_SET_NUM_THREADS** 例程

>  设置供后续并行区域使用的线程数

```c++
#include <omp.h>
void omp_set_num_threads(int num_threads);
```



##### **OMP_GET_THREAD_NUM** 例程

> 返回组内执行对此函数调用的线程的号码。此号码位于 0 和OMP_GET_NUM_THREADS()-1 之间， 0 为主线程。

```c++
#include <omp.h>
int omp_get_thread_num(void);
```

##### **OMP_SET_NUM_THREADS** 例程

> 设置供后续并行区域使用的线程数

```c++
#include <omp.h>
void omp_set_num_threads(int num_threads);
```

##### **OMP_GET_NUM_THREADS** 例程

> 返回当前组中正在执行从中调用其的并行区域的线程的数量。

```c++
#include <omp.h>
int omp_get_max_threads(void);
```

