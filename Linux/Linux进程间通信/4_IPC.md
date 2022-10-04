[TOC]

# IPC通信概述

## IPC运行逻辑

```mermaid
flowchart TD
IPC通信 --> IPC对象 --分为--> kernel
subgraph kernel
	共享内存 & 消息队列 & 信号灯 
end
```

```mermaid
flowchart
pa[program A]
pb[program B]

subgraph kernel
	创建 --> IPC对象 --> 删除
end

pa --W--> IPC对象 
pb --R--> IPC对象
```
IPC的思路和文件IO的思路相同，创建，I/O，删除，只不过函数的名称不同

## 查看内核IPC对象——`ipcs`

+ 查看共享内存：`ipcs -m`
+ 查看消息队列：`ipcs -q`
+ 查看信号灯：`ipcs -s`

## 删除内核IPC对象——`ipcrm`

删除的选项同[查看](#查看内核IPC对象——`ipcs`)，只是需要额外添加要删除的IPC对象的id号

# 共享内存（Shared Memory）

## 共享内存的创建和打开——`shmget`

### 函数定义

```c
#include <sys/shm.h>

/*
 * key		IPC_PRIVATE或ftok的返回值
 * size		共享内存区大小
 * shmflg	同open函数的权限位，也可以使用八进制表示法
 */
// 成功：返回共享内存段标识符，类似文件描述符
// 失败：返回-1
int shmget(key_t key, size_t size, int shmflg);
```

[***`shmget.c`中的`ifndef`部分***](./code/IPC/shm/shmget.c)

### `key`参数

#### `ftok`

如果我们使用`IPC_PRIVATE`，那么创建的共享内存的KEY值永远都是`0x00000000`（可以通过`ipcs`查看）。这样的好处是，由于共享内存的值一直都是0，所以只要任何进程通过`shmget`函数打开这片内存进行操作。

如果我们使用`ftok`函数，他就会返回一个`key`值。

```c
#include <sys/ipc.h>

/*
 * path	文件路径和文件名
 * key	一个字符
 */
// 成功：返回一个key值
// 失败：返回-1
key_t ftok(const char *path, int id);
```
[***`shmget.c`中的`else`部分***](./code/IPC/shm/shmget.c)

> ###### 需要注意的是，如果使用`ftok`返回的key值作为`shmget`的参数，一定要在读写权限出加上`IPC_CREATE`

#### 与管道的类比

在管道的部分，无名管道只能用于有亲缘关系进程之间的通信，而有名管道可以作为无亲缘关系进程之间的通信方式

在此处，IPC_PRIVATE就像有名管道，使用`ftok`函数创建的IPC对象就像无名管道。

## 共享内存的读写——`shmat`

如果我们使用`read`和`write`，那么不仅我们首先需要在程序中准备缓冲区，将将要传递的消息格式化到缓冲区，然后再将缓冲区的内容进行写入，或者将共享内存中的内容读出；同时，我们还需要在用户态和内核态之间反复横跳。

`shmat`的功能是，在用户区开辟一块内存，作为内核中共享内存的映射。我们向这片内存的IO操作，就会等同于我们对共享内存进行IO。

### 函数定义

```c
#include <sys/shm.h>

/*
 * shmid	共享内存ID
 * shmaddr	映射到的地址，NULL为系统自动完成映射
 * shmflg	SHM_RDONLY表示内存只读，默认是0，代表共享内存可读写
 */
// 成功：返回映射后的地址
// 失败：NULL
void *shmat(int shmid, const void *shmaddr, int shmflg);
```

### 举个栗子

[***`shmget_IO.c`***](./code/IPC/shm/shmget_IO.c)

### 共享内存的特点

+ 共享内存创建之后，一直存在于内核中，直到被删除或系统关闭
+ 共享内存和管道不一样，读取完后，内容仍在共享内存中

## 共享内存的删除——`shmdt` & `shmctl`

### 用户区映射内存的释放——`shmdt`

> [***`shmdt.c`***](./code/IPC/shm/shmdt.c)
```c
#include <sys/shm.h>

/*
 * shmaddr	共享内存映射的地址
 */
// 成功返回0，失败返回-1
int shmdt(const void *shmaddr);
```

### 内核共享内存的释放——`shmctl`

> [***`shmctl.c`***](./code/IPC/shm/shmctl.c)
```c
#include <sys/shm.h>

/*
 * shmid	要操作的共享内存标识符
 * cmd		IPC_STAT	获取对象属性
 *			IPC_SET		设置对象属性
 *			IPC_RMID	删除对象
 * buf		指定IPC_STAT/IPC_SET时用以保存/设置属性
 */
// 成功返回0，失败返回-1
int shmctl(int shmid, int cmd, struct shmid_ds *buf);
```

对于删除操作来说，第三个参数是多余的，设置为NULL即可。

```mermaid
flowchart
program --> shmctl --> 共享内存

shmctl --> 功能

subgraph 功能
	属性获取 & 设置属性 & 删除对象
end

subgraph kernel
	共享内存
end
```

## 你已经掌握加法啦，来试试微积分吧！

### 实现父子进程间通信

> [***communicate_with_child.c***](./code/IPC/shm/communicate_with_child.c)

<table>
<tr>
<td>

```mermaid
flowchart

parent
child

subgraph kernel
	shm[shared memory]
end

parent --write--> buffer --> shm
kernel --SIGUSR1--> child
```

</td>
<td>

```mermaid
flowchart

parent
child

subgraph kernel
	shm[shared memory]
end

child --read--> buffer -->shm 
kernel --SIGUSR2-->parent
```

</td>
</table>

这个程序只实现了父进程与子进程的单向通信。如果需要让子进程能够与父进程通信，那么可以再开辟一个共享内存。

### 独立进程间通信

> [***`serv.c`***](./code/IPC/shm/serv.c)与[***`clnt.c`***](./code/IPC/shm/clnt.c)

服务端将自身PID写到共享内存中

```mermaid
flowchart LR
server

subgraph kernel
	shm[shared memory]
end

server --write pid--> shm
```

客户端启动，直接从共享内存读取pid，然后写入自身PID，发送信号让服务端读取client的PID

```mermaid
flowchart LR
server
client

subgraph kernel
	shm[shared memory]
end

shm --read server pid--> client
client --write client pid--> shm
kernel --SIGUSR2--> server
```

服务端读取客户端PID，然后写入数据，发信号让客户端读取数据

```mermaid
flowchart LR
server
client

subgraph kernel
	shm[shared memory]
end

server --write data--> shm
kernel --SIGUSR2--> client
```
