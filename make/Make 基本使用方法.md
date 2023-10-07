> [如何编译 C++ 程序：轻松搞定 Makefile](https://www.bilibili.com/video/BV1dF41117NV?vd_source=8b03f6e8f77627cf848cfa96e05c2f23)

[TOC]

> [用例代码](codes)

# 基本写法

## 基本形式

```makefile
target:
	g++ -I. add.cpp sub.cpp main.cpp -o main
```

+ `target`:目标名称, 可以随意命名
+ `g++`前面不是空格, 必须是 tab 缩进
+ Makefile里如果有多个目标, 可以通过 `make` 加目标名称来指定执行的目标. 如果不指定目标, 则默认选择第一个目标执行

## 第二种写法

```makefile
target: main

main:
	g++ -I. add.cpp sub.cpp main.cpp -o main
```

`target: main`表示`target`目标依赖`main`目标. `main`为目标名称, 可以随便命名

## 第三种写法

```makefile
target: main add_o sub_o main_o

main:
	g++ -I. add.o sub.o main.o -o main

add_o:
	g++ -I. -c add.cpp -o add.o

sub_o:
	g++ -I. -c sub.cpp -o sub.o

main_o:
	g++ -I. -c main.cpp -o main.o
```

在`target`运行的时候, 首先会运行`main`中的指令. 此时会报错: 找不到`add.o`等目标文件. 因此需要修改顺序, 将`main`放到最后.

```makefile
target: add_o sub_o main_o main
```

# 进阶写法

## 规则模式

```makefile
target: add.o sub.o main.o main 

main:
	g++ -I. add.o sub.o main.o -o main

%.o: %.cpp
	g++ -I. -c $< -o $@
```

+ `%.o: %.cpp`: 所有的`.o`文件都由相同名称的`.cpp`文件编译生成
+ `<`: 表示所有依赖的挨个值
+ `@`: 表示所有目标的挨个值

`<`和`@`称为"*自动化变量*"

## 变量替换

```makefile
OBJS := add.o sub.o main.o

target: ${OBJS} main

main:
	g++ -I. ${OBJS} -o main

%.o: %.cpp
	g++ -I. -c $< -o $@
```

引用变量时, 加小括号或者大括号, 可以更为安全地引用变量:

+ `=`是最基本的赋值
+ `:=`是覆盖之前的赋值
+ `?=`是如果没有被赋值, 那就赋值
+ `+=`是添加值

## 清理文件

```makefile
clean:
	rm -rf ${OBJS} main
```

# 高级写法

## 文件过滤

```makefile
# 获取当前目录下所有的 .cpp 文件, 并将值赋给 SRCS
SRCS := ${shell find ./* -type f | grep .cpp}
# 打印检查
${warning SRCS is ${SRCS}}

# 将 SRCS 中所有的 .cpp 替换为 .o, 赋值给 OBJS
OBJS := ${patsubst %.cpp, %.o, ${filter %.cpp, ${SRCS}}}
# 打印检查
${warning OBJS is ${OBJS}}

target: ${OBJS} main

main:
	g++ -I. ${OBJS} -o main

%.o: %.cpp
	g++ -I. -c $< -o $@

clean:
	rm -rf ${OBJS} main
```

+ `shell`: 在 shell 中执行给定的指令
+ `warning`: 以警告级别打印信息, 类似的还有`info`和`error`
+ `patsubst`: 基本格式为`$(patsubst a,b,$(var))`, 其作用为将`var`中的`a`替换为`b`
+ `filter`: 基本格式为``$(filter pattern…,text)`, 将`text`中满足`pattern...`的字符串返回

其中, 替换代码也可为:

```makefile
OBJS := ${SRCS:%.cpp=%.o} # 切记: 在:和%间不可以有多余空格
```

在这样修改过后, 即使源文件不在当前目录, 也可以被`find`找到, 并且生成正确的文件名称

## 编译选项与包含路径

```makefile
SRCS := ${shell find ./* -type f | grep .cpp}
OBJS := ${SRCS:%.cpp=%.o}
CFLAGS := -g -O2 -Wall -Werror -Wno-unused  -std=c++11
INCLUDE := -I.

target: ${OBJS} main

main:
	g++ ${INCLUDE} ${CFLAGS} ${OBJS} -o main

%.o: %.cpp
	g++ ${INCLUDE} ${CFLAGS} -c $< -o $@

clean:
	rm -rf ${OBJS} main
```

# 多入口编译

```makefile
SRCS := ${shell find ./* -type f |\
								grep .cpp |\
								grep -v "main\.cpp" |\ # 删除 main.cpp
								grep -v "test\.cpp"}   # 删除 test.cpp
OBJS := ${SRCS:%.cpp=%.o}
CFLAGS := -g -O2 -Wall -Werror -Wno-unused  -std=c++11
INCLUDE := -I.

MAIN_SRC := main.cpp
MAIN_OBJ := ${MAIN_SRC:%.cpp=%.o}
MAIN_EXE := main

TEST_SRC := test.cpp
TEST_OBJ := ${TEST_SRC:%.cpp=%.o}
TEST_EXE := test

target: ${MAIN_EXE} ${TEST_EXE}

${MAIN_EXE}: ${OBJS} ${MAIN_OBJ}
	g++ -o $@ $^ ${INCLUDE} ${CFLAGS}

${TEST_EXE}: ${OBJS} ${TEST_OBJ}
	g++ -o $@ $^ ${INCLUDE} ${CFLAGS}

%.o: %.cpp
	g++ ${INCLUDE} ${CFLAGS} -c $< -o $@

clean:
	rm -rf ${OBJS} ${MAIN_OBJ} ${TEST_OBJ}
	rm -rf ${MAIN_EXE} ${TEST_EXE}
```

+ `$^`代表所有的依赖项

# 补充

## 自动化变量

+ `$@`: 目标规则的文件名
+ `$<`: 规则中的第一个依赖项
+ `$^`: 规则中所有的依赖项列表, 以空格分割
+ `$*`: 引用目标中的文件部分

 
