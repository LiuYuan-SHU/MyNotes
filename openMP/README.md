# OpenMP Notes

> [Excellent Free Tutorials to Learn OpenMP](https://www.linuxlinks.com/excellent-free-tutorials-learn-openmp/)

[TOC]

### 





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

* Only a single NUM_THREADS clause is permitted.

* A program must not depend upon the ordering of the clauses.

#### 子句含义

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



#### Example

```c++
#include <omp.h>

main ()  {

int nthreads, tid;

/* Fork a team of threads with each thread having a private tid variable */
#pragma omp parallel private(tid)
  {

  /* Obtain and print thread id */
  tid = omp_get_thread_num();
  printf("Hello World from thread = %d\n", tid);

  /* Only master thread does this */
  if (tid == 0) 
    {
    nthreads = omp_get_num_threads();
    printf("Number of threads = %d\n", nthreads);
    }

  }  /* All threads join master thread and terminate */

}
```

### exercise1

> [files](./Exercises/exercise1)
