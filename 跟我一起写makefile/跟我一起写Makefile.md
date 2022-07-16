> [跟我一起写Makefile](https://seisman.github.io/how-to-write-makefile)

[TOC]

# 概述

## 程序的编译和链接

无论是C还是C++，首先要把源文件编译成中间代码文件，在Windows下`.obj`文件，Unix下是`.o`文件，也就是**Object File**。这个动作叫做编译（cimpile）。然后把大量的Object File合成执行文件，这个动作叫做链接（link）。

编译的时候，编译器需要的是虚发正确，函数与变量的声明的正确。对于后者，通常是你需要告诉编译器头文件的所在位置（头文件中应该只是声明，而定义应该放在C/C++文件中），只要所有的语法正确，编译器就可以编译出中间目标文件。一般来说，每个源文件都应该对应于一个中间目标文件（ `.o` 文件或 `.obj` 文件）。

链接时，主要是链接函数和全局变量。所以，我们可以使用这些中间目标文件（ `.o` 文件或 `.obj` 文件）来链接我们的应用程序。链接器并不管函数所在的源文件，只管函数的中间目标文件（Object File），在大多数时候，由于源文件太多，编译生成的中间目标文件太多，而在链接时需要明显地指出中间目标文件名，这对于编译很不方便。所以，我们要给中间目标文件打个包，在Windows下这种包叫“库文件”（Library File），也就是 `.lib` 文件，在UNIX下，是Archive File，也就是 `.a` 文件。

总结一下，源文件首先会生成中间目标文件，再由中间目标文件生成执行文件。在编译时，编译器只检测程序语法和函数、变量是否被声明。如果函数未被声明，编译器会给出一个警告，但可以生成Object File。而在链接程序时，链接器会在所有的Object File中找寻函数的实现，如果找不到，那到就会报链接错误码（Linker Error），在VC下，这种错误一般是： `Link 2001错误` ，意思说是说，链接器未能找到函数的实现。你需要指定函数的Object File。

# Makefile介绍

当我们编写一个makefile来告诉`make`命令如何编译和链接这几个文件的时候，我们的规则是：

1. 如果这个工程没有编译过，那么我们所有的`c`文件都要编译并被链接
2. 如果这个工程的某几个`c`文件被修改，那么我们只编译被修改的`c`文件，并链接目标程序
3. 如果这个工程的头文件被改变了，那么我们需要编译引用了这几个头文件的`c`文件，并链接目标程序

## Makefile的规则

```makefile
target ... : prerequisites ...
	command
	...
	...
```

* target: 可以是一个object file，也可以是一个执行文件，还可以是一个标签（lable）。对于标签这种特性，在“伪目标”章节中会有叙述
* prerequisites: 生成该target所依赖的文件和/或者target
* command: 该target所需要执行的命令（任意的shell命令）

这其实是一个文件的依赖关系，也就是说，`target`这一个或多个的目标文件依赖于`prerequisites`中的文件，其生成规则定义在`command`中。

> [!NOTE] makefile的规则
> 说白一些，`prerequisites`中如果有一个以上的文件比`target`文件要新的话，`command`所定义的命令就会被执行

## 一个示例

考虑这样几个文件：

```shell
# 头文件
defs.h
command.h
buffer.h
# c文件
main.c
kbd.c
command.c
display.c
insert.c
search.c
files.c
utils.c
```

为了完成前述的三个规则，我们可以这样编写一个makefile：

```makefile
edit : main.o kbd.o command.o display.o \
        insert.o search.o files.o utils.o
    cc -o edit main.o kbd.o command.o display.o \
        insert.o search.o files.o utils.o

main.o : main.c defs.h
    cc -c main.c
kbd.o : kbd.c defs.h command.h
    cc -c kbd.c
command.o : command.c defs.h command.h
    cc -c command.c
display.o : display.c defs.h buffer.h
    cc -c display.c
insert.o : insert.c defs.h buffer.h
    cc -c insert.c
search.o : search.c defs.h buffer.h
    cc -c search.c
files.o : files.c defs.h buffer.h command.h
    cc -c files.c
utils.o : utils.c defs.h
    cc -c utils.c
clean :
    rm edit main.o kbd.o command.o display.o \
        insert.o search.o files.o utils.o
```

***反斜杠`\`是换行符的意思。这样比较便于makefile的阅读。我们可以把这个内容保存在名字为“makefile”或“Makefile”的文件中，然后再该目录下直接输入命令`make`就可以生成执行文件`edit`。如果想要删除执行文件和所有的中间目标文件，那么，只需要简单地执行`make clean`就可以了。***

在这个makefile中，目标文件（target）包含：执行文件edit和中间目标文件（ `*.o` ），依赖文件（prerequisites）就是冒号后面的那些 `.c` 文件和 `.h` 文件。每一个 `.o` 文件都有一组依赖文件，而这些 `.o` 文件又是执行文件 `edit` 的依赖文件。依赖关系的实质就是说明了目标文件是由哪些文件生成的，换言之，目标文件是哪些文件更新的。

在定义好依赖关系后，后续的那一行定义了如何生成目标文件的操作系统命令，**一定要以一个 `Tab` 键作为开头**。记住，make并不管命令是怎么工作的，他只管执行所定义的命令。make会比较targets文件和prerequisites文件的修改日期，如果prerequisites文件的日期要比targets文件的日期要新，或者target不存在的话，那么，make就会执行后续定义的命令。

这里要说明一点的是， `clean` 不是一个文件，它只不过是一个动作名字，有点像c语言中的label一样，其冒号后什么也没有，那么，make就不会自动去找它的依赖性，也就不会自动执行其后所定义的命令。要执行其后的命令，就要在make命令后明显得指出这个label的名字。这样的方法非常有用，我们可以在一个makefile中定义不用的编译或是和编译无关的命令，比如程序的打包，程序的备份，等等。

## make是如何工作的

在默认的情况下，也就是我们只输入`make`命令，那么：

1. `make`会在当前目录下找到名字叫“Makefile”或者“makefile”的文件
2. 如果找到，它会找文件中的第一个目标文件，并把这个文件作为**最终的目标文件**
3. 如果目标文件不存在，或者是目标文件的依赖项文件的更新时间更新，那么，它就会执行后面所定义的命令来生成这个目标文件
4. 如果目标文件的依赖项文件也不存在，那么`make`就会在当前文件夹中查找目标为缺失的依赖项文件的依赖项文件，然后再按照对应的规则来生成，这类似一个堆栈

这就是整个make的依赖性，make会一层又一层地去找文件的依赖关系，直到最终编译出第一个目标文件。在找寻的过程中，如果出现错误，比如最后被依赖的文件找不到，那么make就会直接退出，并报错，而对于所定义的命令的错误，或是编译不成功，make根本不理。make只管文件的依赖性，即，如果在我找了依赖关系之后，冒号后面的文件还是不在，那么对不起，我就不工作啦。

通过上述分析，我们知道，像clean这种，没有被第一个目标文件直接或间接关联，那么它后面所定义的命令将不会被自动执行，不过，我们可以显示要make执行。即命令—— `make clean` ，以此来清除所有的目标文件，以便重编译。

于是在我们编程中，如果这个工程已被编译过了，当我们修改了其中一个源文件，比如 `file.c` ，那么根据我们的依赖性，我们的目标 `file.o` 会被重编译（也就是在这个依性关系后面所定义的命令），于是 `file.o` 的文件也是最新的啦，于是 `file.o` 的文件修改时间要比 `edit` 要新，所以 `edit` 也会被重新链接了（详见 `edit` 目标文件后定义的命令）。

而如果我们改变了 `command.h` ，那么， `kdb.o` 、 `command.o` 和 `files.o` 都会被重编译，并且， `edit` 会被重链接。

## makefile中使用变量

让我们回顾一下上一个示例makefile中`edit`的规则：

```makefile
edit : main.o kbd.o command.o display.o \
        insert.o search.o files.o utils.o
    cc -o edit main.o kbd.o command.o display.o \
        insert.o search.o files.o utils.o
```

我们可以看到 `.o` 文件的字符串被重复了两次，如果我们的工程需要加入一个新的 `.o` 文件，那么我们需要在两个地方加（应该是三个地方，还有一个地方在clean中）。当然，我们的makefile并不复杂，所以在两个地方加也不累，但如果makefile变得复杂，那么我们就有可能会忘掉一个需要加入的地方，而导致编译失败。所以，为了makefile的易维护，在makefile中我们可以使用变量。makefile的变量也就是一个字符串，理解成C语言中的宏可能会更好。

当然我们可以定义一个变量来代表这些obj文件：

```makefile
objects = ...
```

于是，我们就可以在Makefile中以`$(objects)`使用这个变量：

```makefile
edit : $(objects)
	cc -o edit $(objects)
```

## 让make自动推导

GNU的make很强大，它可以自动推导文件以及文件依赖关系后面的命令，于是我们就没必要去在每一个 `.o` 文件后都写上类似的命令，因为，我们的make会自动识别，并自己推导命令。

只要make看到一个 `.o` 文件，它就会自动的把 `.c` 文件加在依赖关系中，如果make找到一个 `whatever.o` ，那么 `whatever.c` 就会是 `whatever.o` 的依赖文件。并且 `cc -c whatever.c` 也会被推导出来。

于是，我们可以写出更为简洁的Makefile：

```makefile
objects = main.o kbd.o command.o display.o \
    insert.o search.o files.o utils.o

edit : $(objects)
    cc -o edit $(objects)

main.o : defs.h
kbd.o : defs.h command.h
command.o : defs.h command.h
display.o : defs.h buffer.h
insert.o : defs.h buffer.h
search.o : defs.h buffer.h
files.o : defs.h buffer.h command.h
utils.o : defs.h

.PHONY : clean
clean :
    rm edit $(objects)
```

这种方法，也就是make的“隐晦规则”。上面文件内容中， `.PHONY` 表示 `clean` 是个伪目标文件。

## 另类风格的makefiles

上面是的Makefile中存在大量的冗余：对于不同的`.o`文件，有着相同的依赖头文件。我们能否将这些语句合并？答案是可以的：

```makefile
objects = main.o kbd.o command.o display.o \
    insert.o search.o files.o utils.o

edit : $(objects)
    cc -o edit $(objects)

$(objects) : defs.h
kbd.o command.o files.o : command.h
display.o insert.o search.o files.o : buffer.h

.PHONY : clean
clean :
    rm edit $(objects)
```

这种风格，让我们的makefile变得很简单，但我们的文件依赖关系就显得有点凌乱了。鱼和熊掌不可兼得。

1. 文件的依赖关系看不清楚
2.  如果文件一多，要加入几个新的 `.o` 文件，那就理不清楚了。

## 清空目标文件的规则

每个Makefile中都应该写一个清空目标文件（ `.o` 和执行文件）的规则，这不仅便于重编译，也很利于保持文件的清洁。这是一个“修养”（呵呵，还记得我的《编程修养》吗）。一般的风格都是：

```makefile
clean:
    rm edit $(objects)
```

更为稳健的做法是：

```makefile
.PHONY : clean
clean :
    -rm edit $(objects)
```

前面说过， `.PHONY` 表示 `clean` 是一个“伪目标”。而在 `rm` 命令前面加了一个小减号的意思就是，也许某些文件出现问题，但不要管，继续做后面的事。当然， `clean` 的规则不要放在文件的开头，不然，这就会变成make的默认目标，相信谁也不愿意这样。不成文的规矩是——“clean从来都是放在文件的最后”。

上面就是一个makefile的概貌，也是makefile的基础。

## makefile里有什么？

Makefilefile里主要包含了五个东西：显式规则、隐晦规则、变量定义、文件指示和注释。

1. 显式规则：显式规则说明了如何生成一个火多个目标文件。这是由Makefile的书写者明确指出要生成的文件、文件的依赖文件和生成指令
2. 隐晦规则：由于我们的`make`具有自动推导的功能，所以隐晦的规则可以让我们比较简略地数学makefile，这是`make`所支持的
3. 变量的定义：在Makefile中我们要定义一系列的变量，变量一般都是字符串，这个有些像C语言中的宏，当Makefile被执行的时候，其中的变量都会被扩展到相应的引用位置上
4. 文件指示：其包括了三个部分：
	1. 在一个Makefile中引用另一个makefile，就像C语言中的`include`一样
	2. 根据某些情况指定makefile的有效部分，就像C语言的预编译`#if`一样
	3. 定义一个多行的命令
5. 注释：Makefile中只有行注释，和UNIX的Shell脚本一样，其注释是`#`字符，这个就像C/C++中的`//`一样。如果你要在你的Makefile中使用`#`字符，可以使用反斜杠进行转义，也就是`\#`

最后，值得一提的是，***在Makefile中的命令必须要以`tab`开始***

## Makefile的文件名

默认的情况下，make命令会在当前目录下按顺序找寻文件名为“GNUmakefile”、“makefile”、“Makefile”的文件，找到了解释这个文件。在这三个文件名中，最好使用“Makefile”这个文件名，因为，这个文件名第一个字符为大写，这样有一种显目的感觉。最好不要用“GNUmakefile”，这个文件是GNU的make识别的。有另外一些make只对全小写的“makefile”文件名敏感，但是基本上来说，大多数的make都支持“makefile”和“Makefile”这两种默认文件名。

当然，你可以使用别的文件名来书写Makefile，比如：“Make.Linux”，“Make.Solaris”，“Make.AIX”等，如果要指定特定的Makefile，你可以使用make的 `-f` 和 `--file` 参数，如： `make -f Make.Linux` 或 `make --file Make.AIX` 。

## 引用其他的Makefile

在Makefile中使用`include`关键字可以把别的makefile包含进来，这很像C语言的`#include`，被包含的文件就会原模原样的放在当前文件的包含位置，`include`的语法是：

```makefile
include <filename>
```

`filename` 可以是当前操作系统Shell的文件模式（可以包含路径和通配符）。

在 `include` 前面可以有一些空字符，但是绝不能是 `Tab` 键开始。 `include` 和 `<filename>` 可以用一个或多个空格隔开。举个例子，你有这样几个Makefile： `a.mk` 、 `b.mk` 、 `c.mk` ，还有一个文件叫 `foo.make` ，以及一个变量 `$(bar)` ，其包含了 `e.mk` 和 `f.mk` ，那么，下面的语句：

```makefile
include foo.make *.mk $(bar)
```

等价于：

```makefile
include foo.make a.mk b.mk c.mk e.mk f.mk
```

make命令开始时，会找寻 `include` 所指出的其它Makefile，并把其内容安置在当前的位置。就好像C/C++的 `#include` 指令一样。如果文件都没有指定绝对路径或是相对路径的话，make会在当前目录下首先寻找，如果当前目录下没有找到，那么，make还会在下面的几个目录下找：

1.  如果make执行时，有 `-I` 或 `--include-dir` 参数，那么make就会在这个参数所指定的目录下去寻找。
    
2.  如果目录 `<prefix>/include` （一般是： `/usr/local/bin` 或 `/usr/include` ）存在的话，make也会去找。
    

如果有文件没有找到的话，make会生成一条警告信息，但不会马上出现致命错误。它会继续载入其它的文件，一旦完成makefile的读取，make会再重试这些没有找到，或是不能读取的文件，如果还是不行，make才会出现一条致命信息。如果你想让make不理那些无法读取的文件，而继续执行，你可以在include前加一个减号“-”。如：

```makefile
-include <filename>
```

其表示，无论include过程中出现什么错误，都不要报错继续执行。和其它版本make兼容的相关命令是sinclude，其作用和这一个是一样的。

## 环境变量makefiles

如果你的当前环境中定义了环境变量 `MAKEFILES` ，那么，make会把这个变量中的值做一个类似于 `include` 的动作。这个变量中的值是其它的Makefile，用空格分隔。只是，它和 `include` 不同的是，从这个环境变量中引入的Makefile的“目标”不会起作用，如果环境变量中定义的文件发现错误，make也会不理。

但是在这里我还是建议不要使用这个环境变量，因为只要这个变量一被定义，那么当你使用make时，所有的Makefile都会受到它的影响，这绝不是你想看到的。在这里提这个事，只是为了告诉大家，也许有时候你的Makefile出现了怪事，那么你可以看看当前环境中有没有定义这个变量。

## `make`的工作方式

## make的工作方式[¶](https://seisman.github.io/how-to-write-makefile/introduction.html#id10 "永久链接至标题")

GNU的make工作时的执行步骤如下：（想来其它的make也是类似）

1.  读入所有的Makefile。
2.  读入被include的其它Makefile。
3.  初始化文件中的变量。
4.  推导隐晦规则，并分析所有规则。
5.  为所有的目标文件创建依赖关系链。
6.  根据依赖关系，决定哪些目标要重新生成。
7.  执行生成命令。

1-5步为第一个阶段，6-7为第二个阶段。第一个阶段中，如果定义的变量被使用了，那么，make会把其展开在使用的位置。但make并不会完全马上展开，make使用的是拖延战术，如果变量出现在依赖关系的规则中，那么仅当这条依赖被决定要使用了，变量才会在其内部展开。

当然，这个工作方式你不一定要清楚，但是知道这个方式你也会对make更为熟悉。有了这个基础，后续部分也就容易看懂了。

# 书写规则

规则包含两个部分，一个是依赖关系，一个是生成目标的方法。

在Makefile中，规则的顺序是很重要的，因为，啊克服了中只应该有一个最终目标，其他的目标都是被这个目标所连带出来的，所以一定要让`make`知道你的最终目标是什么。一般来说，定义在Makefile中的目标可能会有很多，但是第一条规则中的目标将被确立为最终的目标。如果第一条规则中的目标有很多个，那么，第一个目标会成为最终的目标。`make`所完成的也就是这个目标。

## 规则举例

```makefile
foo.o: foo.c defs.h       # foo模块
    cc -c -g foo.c
```

看到这个例子，各位应该不是很陌生了，前面也已说过， `foo.o` 是我们的目标， `foo.c` 和 `defs.h` 是目标所依赖的源文件，而只有一个命令 `cc -c -g foo.c` （以Tab键开头）。这个规则告诉我们两件事：

1.  文件的依赖关系， `foo.o` 依赖于 `foo.c` 和 `defs.h` 的文件，如果 `foo.c` 和 `defs.h` 的文件日期要比 `foo.o` 文件日期要新，或是 `foo.o` 不存在，那么依赖关系发生。
    
2.  生成或更新 `foo.o` 文件，就是那个cc命令。它说明了如何生成 `foo.o` 这个文件。（当然，foo.c文件include了defs.h文件）

## 规则的语法

```makefile
targets : prerequisites
    command
    ...
```

或者这样：

```makefile
targets : prerequisites
    command
    ...
```

targets是文件名，以空格分开，可以使用通配符。一般来说，我们的目标基本上是一个文件，但也有可能是多个文件。

command是命令行，如果其不与“target:prerequisites”在一行，那么，必须以 `Tab` 键开头，如果和prerequisites在一行，那么可以用分号做为分隔。（见上）

prerequisites也就是目标所依赖的文件（或依赖目标）。如果其中的某个文件要比目标文件要新，那么，目标就被认为是“过时的”，被认为是需要重生成的。这个在前面已经讲过了。

如果命令太长，你可以使用反斜杠（ `\` ）作为换行符。make对一行上有多少个字符没有限制。规则告诉make两件事，文件的依赖关系和如何生成目标文件。

一般来说，make会以UNIX的标准Shell，也就是 `/bin/sh` 来执行命令。

## 在规则中使用通配符

如果我们想定义一系列比较类似的文件，我们很自然地就想起使用通配符。make支持三个通配符： `*` ， `?` 和 `~` 。这是和Unix的B-Shell是相同的。

波浪号（ `~` ）字符在文件名中也有比较特殊的用途。如果是 `~/test` ，这就表示当前用户的 `$HOME` 目录下的test目录。而 `~hchen/test` 则表示用户hchen的宿主目录下的test 目录。（这些都是Unix下的小知识了，make也支持）而在Windows或是 MS-DOS下，用户没有宿主目录，那么波浪号所指的目录则根据环境变量“HOME”而定。

通配符代替了你一系列的文件，如 `*.c` 表示所有后缀为c的文件。一个需要我们注意的是，如果我们的文件名中有通配符，如： `*` ，那么可以用转义字符 `\` ，如 `\*` 来表示真实的 `*` 字符，而不是任意长度的字符串。

## 文件搜寻

