> 命令行选项分析

[TOC]

# CMake 加载

```cmake
find_package(Boost REQUIRED COMPONENTS
        program_options)
include_directories(${BOOST_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::program_options)
```

# 样例

## quick start - first.cpp

```c++
// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/* The simplest usage of the library.
 */

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <iostream>
#include <iterator>
using namespace std;

int main(int ac, char* av[])
{
    try {

        po::options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce help message")
            ("compression", po::value<double>(), "set compression level")
        ;

        po::variables_map vm;
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            cout << desc << "\n";
            return 0;
        }

        if (vm.count("compression")) {
            cout << "Compression level was set to "
                 << vm["compression"].as<double>() << ".\n";
        } else {
            cout << "Compression level was not set.\n";
        }
    }
    catch(exception& e) {
        cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch(...) {
        cerr << "Exception of unknown type!\n";
    }

    return 0;
}
```

1. `options_description`: 程序所有允许的选项都在这个对象中被声明. 

    `add_options`方法返回一个定义了`operator()`的代理对象, 因此可以反复调用`operator()`来设置选项, 所以代码看起来会比较鬼畜. 这个函数的参数是:

    1. 选项的名称
    2. 关于选项值的信息
    3. 选项的描述

    在本例中, 第一个选项没有值; 第二个选项的值应当是`int`类型

2. `variables_map`: 这个类用于保存选项的值, 并且可以保存任意类型的值. 

    接下来, 调用`store`/`parse_command_line`/`notify`来将在命令行中的参数全部保存到`vm`中.

    保存之后, 就可以使用这些选项了. `variables_map`能像`std::map`一样使用, 只是必须像代码示例中那样使用. 如果选项的实际值和`as`中指定的值类型不一样, 就会抛出一个异常.

## 选项的描述与细节 - options_decriptions.cpp

假设我们在写一个编译器, 那么这个编译器应该能够接受:

+ 优化等级
+ 若干数量的包含路径(include path)
+ 若干数量的输入文件(input file)

描述这些需求的代码如下:

```c++
int opt;
int portnum;
po::options_description desc("Allowed options");
desc.add_options()
    ("help", "produce help message")
    ("optimization", po::value<int>(&opt)->default_value(10), "optimization level")
    ("verbose,v", po::value<int>()->implicit_value(1), "enable verbosity (optionally specify level)")
    ("listen,l", po::value<int>(&portnum)->implicit_value(1001)->default_value(0, "no"), "listen on a port.")
    ("include-path,I", po::value<vector<string>>(), "include path")
    ("input-file", po::value<vector<string>>(), "input file");
```

1. `help`选项并没有改变, 在任何情况下提供`help`都是一个很好的主意

2. `optimization`展示了两个新的特性. 

    1. 我们传入了`opt`的地址, 在将命令行的值通过`notify`之后保存到`variables_map`之后, 命令行中的`optimization`的值也会被保存到`opt`之中
    2. 我们使用`10`作为`opt`的默认值

3. `include-path`选项使用`include-path,I`作为选项的名称, 能够接受两种不同的调用方式:

    + `--include-path path1`
    + `-I path1`

    需要注意的是, `include-path`的选项是`std::vector`, 这个库为`vector`提供了特殊的支持: 这个库可能多次检测到这个选项, 这些检测到的选项都会被收集到一个`vector`对象中.

4. `input-file`选项指定了一系列要处理的文件. 当然, 现在的实现看起来是这个样子的:

    ```bash
    compiler --input-file=a.cpp
    ```

    这个和通常的使用方法比较起来看起来有些"不标准":

    ```bash
    compiler a.cpp
    ```

    这个问题会在稍后解决.

那些没有选项名称的命令行参数, 例如`compiler a.cpp`, 被称为***位置选项(positional options)***.  这些参数也可以被识别. 只要使用这个库的用户提供一点点帮助, 库就能识别出`a.cpp`是`--input-file`选项的参数. 以下是我们需要的代码:

```c++
po::positional_options_description p;
p.add("input-file", -1);

po::variables_map vm;
po::store(po::command_line_parser(ac, av).
          options(desc).positional(p).run(), vm);
po::notify(vm);
```

头两行的含义是, 所有的位置选项都会被解释为`input-file`选项的参数. 同时需要注意的是, 我们此处在`store`函数中调用的是`command_line_parser`, 而不是上一个例子中使用的`parse_command_line`. 后者是在简单情况下的一个很好用的包装器(wrapper), 但现在我们需要一些额外的选项, 因此需要使用前者.

一切就绪, 加上选项识别后的处理代码, 一切准备就绪:

```c++
// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/program_options.hpp>

using namespace boost;
namespace po = boost::program_options;

#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;


// A helper function to simplify the main part.
template<class T>
    ostream& operator<<(ostream& os, const vector<T>& v)
{
    copy(v.begin(), v.end(), ostream_iterator<T>(os, " "));
    return os;
}

int main(int ac, char* av[])
{
    try {
        int opt;
        int portnum;
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce help message")
            ("optimization", po::value<int>(&opt)->default_value(10),
             "optimization level")
            ("verbose,v", po::value<int>()->implicit_value(1),
             "enable verbosity (optionally specify level)")
            ("listen,l", po::value<int>(&portnum)->implicit_value(1001)
             ->default_value(0,"no"),
             "listen on a port.")
            ("include-path,I", po::value< vector<string> >(),
             "include path")
            ("input-file", po::value< vector<string> >(), "input file")
            ;

        po::positional_options_description p;
        p.add("input-file", -1);

        po::variables_map vm;
        po::store(po::command_line_parser(ac, av).
                  options(desc).positional(p).run(), vm);
        po::notify(vm);

        if (vm.count("help")) {
            cout << "Usage: options_description [options]\n";
            cout << desc;
            return 0;
        }

        if (vm.count("include-path"))
        {
            cout << "Include paths are: "
                << vm["include-path"].as< vector<string> >() << "\n";
        }

        if (vm.count("input-file"))
        {
            cout << "Input files are: "
                << vm["input-file"].as< vector<string> >() << "\n";
        }

        if (vm.count("verbose")) {
            cout << "Verbosity enabled.  Level is " << vm["verbose"].as<int>()
                << "\n";
        }

        cout << "Optimization level is " << opt << "\n";

        cout << "Listen port is " << portnum << "\n";
    }
    catch(std::exception& e)
    {
        cout << e.what() << "\n";
        return 1;
    }
    return 0;
}
```

以下是运行示例:

```bash
$ bin/gcc/debug/options_description --help
Usage: options_description [options]
Allowed options:
  --help                 : produce help message
  --optimization arg     : optimization level
  -I [ --include-path ] arg : include path
  --input-file arg       : input file
$ bin/gcc/debug/options_description
Optimization level is 10
$ bin/gcc/debug/options_description --optimization 4 -I foo -I another/path --include-path third/include/path a.cpp b.cpp
Include paths are: foo another/path third/include/path
Input files are: a.cpp b.cpp
Optimization level is 4
```

在这里可能会让程序的用户产生一些困惑: 究竟应该使用`input-file`选项还是位置选项? 此处需要查看下一个示例.

## 多个输入源 - multiple-sources.cpp

>此处多个输入源的含义是, 将选项从配置文件和命令行等不同的地方输入

在命令行上显示所有的选项很有可能让用户觉得很困惑. 如果一个用户安装了一个库并且一直都想要将这个库包含在编译选项中怎么办? 如果程序的每一次运行, 都有一些选项是固定的怎么办? 在这样的情况下, 一个装着一些常用选项的配置文件就应当被命令行接受. 

当然, 我们需要将配置文件中的选项和实际在命令行中的选项相结合. 例如, 命令行中的优化等级选项应该覆盖配置文件中的优化等级; 而包含路径应该取并集.

那么来看看代码. 代码中有些有趣的地方, 我们声明了几个`options_description`实例. 

+ 总的来说, 不是所有的选项都是相似的, 他们属于不同的功能模块. 
+ 像`input-file`不应该出现在自动帮助信息中.
+ 有的选项只会在配置文件中生效

总的来说, 一个有结构的帮助信息是很不错的, 而不是简单地打印一长串选项.

```cpp
// Declare a group of options that will be
// allowed only on command line
po::options_description generic("Generic options");
generic.add_options()
    ("version,v", "print version string")
    ("help", "produce help message")
    ("config,c", po::value<string>(&config_file)->default_value("multiple_sources.cfg"),
     "name of a file of a configuration.")
    ;

// Declare a group of options that will be
// allowed both on command line and in
// config file
po::options_description config("Configuration");
config.add_options()
    ("optimization", po::value<int>(&opt)->default_value(10),
     "optimization level")
    ("include-path,I",
     po::value< vector<string> >()->composing(),
     "include path")
    ;

// Hidden options, will be allowed both on command line and
// in config file, but will not be shown to the user.
po::options_description hidden("Hidden options");
hidden.add_options()
    ("input-file", po::value< vector<string> >(), "input file")
    ;
```

注意在`include-path`选项中调用`composing`方法. 其告知 ProgramOptions 库对来自不同输入源的选项取并集.

******

`options_description`的`add`方法能被用来对选项进一步分组:

 ```cpp
 po::options_description cmdline_options;
 cmdline_options.add(generic).add(config).add(hidden);
 
 po::options_description config_file_options;
 config_file_options.add(config).add(hidden);
 
 po::options_description visible("Allowed options");
 visible.add(generic).add(config);
 ```

选项值的解析和存储遵循通常的模式，除此之外, 我们额外调用`parse_config_file`，并调用两次`store`函数。

但是，在命令行和配置文件中都指定了相同的值，会发生什么？

程序会选择已经被`store`存储到`variables_map`中的值, 代码中先对命令行的选项调用`store`, 再对配置文件调用`store`, 于是实际的运行效果是采用命令行中的选项。这就是`--optimization`选项的应对方式。

对于需要被组合的选项，如“include-file”，这些值将被合并。

******

以下是完整的代码文件, 配置文件和运行示例:

```cpp
// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/* Shows how to use both command line and config file. */

#include <boost/program_options.hpp>
namespace po = boost::program_options;


#include <iostream>
#include <fstream>
#include <iterator>
using namespace std;

// A helper function to simplify the main part.
template<class T>
    ostream& operator<<(ostream& os, const vector<T>& v)
{
    copy(v.begin(), v.end(), ostream_iterator<T>(os, " "));
    return os;
}


int main(int ac, char* av[])
{
    try {
        int opt;
        string config_file;

        // Declare a group of options that will be
        // allowed only on command line
        po::options_description generic("Generic options");
        generic.add_options()
            ("version,v", "print version string")
            ("help", "produce help message")
            ("config,c", po::value<string>(&config_file)->default_value("multiple_sources.cfg"),
             "name of a file of a configuration.")
            ;

        // Declare a group of options that will be
        // allowed both on command line and in
        // config file
        po::options_description config("Configuration");
        config.add_options()
            ("optimization", po::value<int>(&opt)->default_value(10),
             "optimization level")
            ("include-path,I",
             po::value< vector<string> >()->composing(),
             "include path")
            ;

        // Hidden options, will be allowed both on command line and
        // in config file, but will not be shown to the user.
        po::options_description hidden("Hidden options");
        hidden.add_options()
            ("input-file", po::value< vector<string> >(), "input file")
            ;


        po::options_description cmdline_options;
        cmdline_options.add(generic).add(config).add(hidden);

        po::options_description config_file_options;
        config_file_options.add(config).add(hidden);

        po::options_description visible("Allowed options");
        visible.add(generic).add(config);

        po::positional_options_description p;
        p.add("input-file", -1);

        po::variables_map vm;
        store(po::command_line_parser(ac, av).
              options(cmdline_options).positional(p).run(), vm);
        notify(vm);

        ifstream ifs(config_file.c_str());
        if (!ifs)
        {
            cout << "can not open config file: " << config_file << "\n";
            return 0;
        }
        else
        {
            store(parse_config_file(ifs, config_file_options), vm);
            notify(vm);
        }

        if (vm.count("help")) {
            cout << visible << "\n";
            return 0;
        }

        if (vm.count("version")) {
            cout << "Multiple sources example, version 1.0\n";
            return 0;
        }

        if (vm.count("include-path"))
        {
            cout << "Include paths are: "
                << vm["include-path"].as< vector<string> >() << "\n";
        }

        if (vm.count("input-file"))
        {
            cout << "Input files are: "
                << vm["input-file"].as< vector<string> >() << "\n";
        }

        cout << "Optimization level is " << opt << "\n";
    }
    catch(exception& e)
    {
        cout << e.what() << "\n";
        return 1;
    }
    return 0;
}
```

multiple_sources.cfg:

```
#
# Comment out this line to use hard-coded default value of 10
#
optimization = 1
include-path = /opt
```

使用示例:

```bash
$ bin/gcc/debug/multiple_sources
Include paths are: /opt
Optimization level is 1
$ bin/gcc/debug/multiple_sources --help
Allows options:

Generic options:
  -v [ --version ]       : print version string
  --help                 : produce help message

Configuration:
  --optimization n       : optimization level
  -I [ --include-path ] path : include path

$ bin/gcc/debug/multiple_sources --optimization=4 -I foo a.cpp b.cpp
Include paths are: foo /opt
Input files are: a.cpp b.cpp
Optimization level is 4
```

第一次调用使用了来自配置文件的值.

第二次调用调用了`help`, 之所以没有继续打印配置文件中的值, 是因为调用`help`之后调用了`return 0`.

第三次调用中, 命令行输入的包含路径和配置文件中的包含路径被合并, 而优化等级采取了命令行的输入.

# 库概览

Program Options 库有 3 个核心组件:

+ 选项描述组件, 其描述了允许的选项, 以及程序如何处理这些选项, 例如`options_description`类
+ 分析组件, 其利用选项描述组件中的信息来查找参数中的选项名称以及他们的值并且将其返回, 例如`parse_command_line`函数
+ 存储组件, 其提供了访问选项的值的接口. 其同样将字符串转换为分析组件希望的 C++类型, 例如`variables_map`类

## 选项描述组件

选项描述组件有 3 个主要类:

+ `option_description`
+ `value_semantic`
+ `options_description`

头两个用于描述一个单独的选项. 

+ `option_description`类包含了选项的名称, 描述和一个指向`value_semantic`对象的指针, 这个被指向的对象知道选项的值类型, 并且能够分析这个值,使用其默认值, 或者采取别的措施.

+ `options_description`类是一个装着`option_description`对象的容器.

对几乎每一个库来说, 这些类可以按照习惯来创建: 你使用构造函数来创建选项, 然后使用`options_decription`的`add`方法来添加这个选项. 但是, 对于声明大量的选项来说, 这太冗长了. 这样的情况催生了下面语法的创建:

```cpp
po::options_description generic("Generic options");
generic.add_options()
    ("version,v", "print version string")
    ("help", "produce help message")
    ("config,c", po::value<string>(&config_file)->default_value("multiple_sources.cfg"),
     "name of a file of a configuration.")
    ;
```

调用`value`函数将会创造一个派生于`value_semantic`类的一个类`typed_value`的实例. 这个派生类包含着分析特定类型值的代码, 同时包含着一系列能够被用户调用来的方法, 这些方法能够指定一些额外的信息. 

对`add_options`函数返回的对象调用`operator()`，该函数会将参数转给`option_description`类的构造函数，并添加新的实例。

除了`value`之外，库还提供了`bool_switch`函数,该函数的工作方式与`value`函数的工作方式相同，但是创建的`value_semantic`不会接受任何明确的值。因此，如果在命令行中存在该选项，其值将是 `true`。

而且用户可以编写自己的函数，从而返回具有不同行为的`value_semantic`的其他子类。

关于选项的信息分为句法信息和语义信息。

+ 句法信息包括选项的名称和可用于指定值的$token$数量。这些信息被解析器用来将$token$分组为$(name, value)$对，其中$value$只是一个字符串的向量`std::vector<std::string>`。
+ 语义层负责将选项的值转换为更可用的C++类型。

$token$的分割是一个很重要的部分. 分析器只使用了语法层, 这导致一些复杂的结构不能被很好的识别, 例如:

```bash
calc --expression=1 + 2/3
```

因为这个式子在不知道它是一个 C 表达式的情况下几乎无法分析:

```
1 + 2/3
```

如果用户能够提供一点小小的帮助, 那么事情就会变得很简单了:

```bash
calcl --expression="1 + 2/3"
```

### 选项的语法信息

语法信息由`boost::program_options::options_decription`类和`boost::program_options::value_semantic`类的方法提供, 其包含:

+ 选项的名称, 用于标识程序的选项
+ 选项的描述, 其可以被呈现给用户, 帮助其理解选项的含义
+ 选项的值的数量，这在解析过程中被使用

考虑以下的例子:

```cpp
options_description desc;
desc.add_options()
	("help", "produce help message")
	("compression", value<string>(), "compression level")
	("verbose", value<string>()->implicit_value("0"), "verbosity level")
	("email", value<string>()->multitoken(), "email to send to")
	;

```

+ 对于第一个选项，我们只指定名称和描述。在解析的源中不能指定任何值。

+ 对于第二个选项，用户必须指定一个值，使用单个$token$。

+ 对于第三个选项，用户可以为值提供一个单一的$token$，或者根本不提供任何$token$。

+ 对于最后一个选项，该值可以变为几个$token$。

例如，下面的命令行是可以的：

```bash
test --help --compression 10 --verbose --email beadle@mars beadle2@mars
```

### 选项的描述格式

有时选项的描述可能会很长. 例如, 当几个选项的值需要单独的记录的时候.

一个选项字符串有一个或者多个段落, 用`\n`分开. 当一个选项被输出的时候, Program Options库会计算描述的对齐. 每一个段落都会被单独输出为一行. 如果段落无法在一行中被放下, 那就会被变为多行, 并且拥有相同的缩进距离.

可以通过插入空格的方式为一个段落的第一行指定额外的缩进, 例如:

```cpp
options.add_options()
	("help", "   A long help msg a long help msg a long help msg a long help msg a long help msg a long help msg a long help msg a long help msg ")
	;
```

输出会看起来像这样:

```
  --help                    A long help msg a long
                        help msg a long help msg
                        a long help msg a long
                        help msg a long help msg
                        a long help msg a long
                        help msg
```

如果需要将行包起来，你可以为被包起来的文本增加一个缩进。这可以通过在所需位置插入一个制表符`'\t'`来实现。

```cpp
options.add_options()
      ("well_formated", "As you can see this is a very well formatted option description.\n"
                        "You can do this for example:\n\n"
                        "Values:\n"
                        "  Value1: \tdoes this and that, bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla\n"
                        "  Value2: \tdoes something else, bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla\n\n"
                        "    This paragraph has a first line indent only, bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla");
```

看起来会像这样:

```
  --well_formated       As you can see this is a
                        very well formatted
                        option description.
                        You can do this for
                        example:

                        Values:
                          Value1: does this and
                                  that, bla bla
                                  bla bla bla bla
                                  bla bla bla bla
                                  bla bla bla bla
                                  bla
                          Value2: does something
                                  else, bla bla
                                  bla bla bla bla
                                  bla bla bla bla
                                  bla bla bla bla
                                  bla

                            This paragraph has a
                        first line indent only,
                        bla bla bla bla bla bla
                        bla bla bla bla bla bla
                        bla bla bla
```

每个段落只允许有一个制表符，否则会抛出program_options::error类型的异常。最后，如果制表符不在段落的第一行，或者在第一行的最后一个可能的位置，则会被忽略。

### 语义信息

语义信息完全由`boost::program_options::value_semantic`类提供. 例如:

```cpp
options_description desc;
desc.add_options()
    ("compression", value<int>()->default_value(10), "compression level")
    ("email", value< vector<string> >()
        ->composing()->notifier(&your_function), "email")
    ;
```

这些声明指定:

+ 第一个选项的默认值为10
+ 第二个选项可以出现几次，所有的实例都会被合并. 解析完成后，库将调用函数`your_function`，将 "email "选项的值作为参数传递。

### 位置选项

将选项定义为$(name, value)$是简单而有用的. 但是对于命令行中的一种情况, 会存在一点问题. 命令行中可能存在位置选项, 并且不指定任何名字:

```bash
archiver --compression=9 /etc/passwd
```

`positional_options_description`类允许命令行分析器分配名称. 这个类会指定有多少个位置选项, 并且对于每一个位置选项, 指定一个名称. 例如:

```cpp
positional_options_description pd; 
pd.add("input-file", 1);
```

这段代码指定了一个, 同时也是第一个位置选项的名称为"input-file".

甚至可以指定一个数字，然后将所有的位置选项都被赋予相同的名称:

```cpp
positional_options_description pd;
pd.add("output-file", 2).add("input-file", -1);
```

在上面的例子中, 头两个位置选项会与名字"output-file"关联, 其他的位置选项则会于名字"input-file"关联.

需要注意的是, positional_options_description类只指定了从位置到名称的翻译，选项名称仍然应该用options_description类的一个实例来注册。

## 分析器组件

分析器组件将输入源分解为$(name, value)$对. 每个解析器都会寻找可能的选项，并查阅选项描述组件，以确定该选项是否已知以及如何指定其值。

比较简单的情况是, 名称已经被显式地指定, 这样库就可以决定这个选项是否已知. 

+ 如果选项已知, `value_semantic`示例就会决定这个选项的值会被如何指定. 
+ 如果选项未知, 就会抛出一个异常.

或者是, 有的选项只要被指定, 那么就是`true`, 这个时候需要确定用户没有输入了多余的值, 并返回一个新的$(name, value)$对.

要调用分析器, 通常需要调用一个函数, 将选项描述和输入源(命令行参数或者是配置文件, 或者别的什么东西)传入. 分析的结果将会以`parsed_options`实例的形式返回. 通常, 这个实例会被直接传入存储组件. 但是, 它也可以被直接使用, 或者进行一些额外处理. 

上述模式有三个例外, 它们都与命令行的传统用法有关。虽然它们需要选项描述组件的一些支持，但额外的复杂性是可以容忍的。

+ 在命令行上指定的名称可能与选项的名称不同: 为一个较长的名称提供一个 "短选项名称 "的别名是很常见的。允许在命令行上指定一个缩写的名字也很常见。
+ 有时，将值指定为几个标记也是可取的。例如，一个选项"--email-recipient "后面可能有几个email，每个都是一个单独的命令行标记。这种行为是被支持的，尽管它可能会导致解析上的歧义，而且默认情况下不启用。
+ 命令行可能包含位置选项: 没有任何名称的元素。命令行分析器提供了一个机制来猜测这些选项的名称，正如上面看到的那样。

## 存储组件

一个存储组件的功能是:

+ 将一个选项的最终值存储到一个特殊的类和常规变量中
+ 解决不同输入源的优先级问题
+ 使用选项的最终值调用用户指定的`notify`函数

考虑下面的例子:

```cpp
variables_map vm;
store(parse_command_line(argc, argv, desc), vm);
store(parse_config_file("example.cfg", desc), vm);
notify(vm);
```

`variables_map`用于存储选项的值. 上述代码中对`store`的两次调用将在命令行和配置文件中找到的选项加入`vm`. 最终调用`notify`函数来执行用户指定的notify函数, 并在需要的时候将结果存入常规的变量中.

优先级的问题被以一个简单的方式解决: 如果一个选项已经被赋予了一个值, 那么`store`函数不会覆盖这个值. 在这样的前提下, 如果命令行已经指定了一个选项的值, 那么配置文件中关于这个选项的任何值都会被忽略. 

## 额外补充

### 具体的分析器

#### 配置文件分析器

`parse_config_file`函数实现了一个简单的类 INI 配置文件的分析器. 配置文件的语法是基于行的:

+ 像这样的一行将一个值赋给一个选项:

    ```ini
    name=value
    ```

+ 像这样的一行介绍配置文件的一个分区(section):

    ```ini
    [section name]
    ```

+ `#`符号代表从该符号开始直至行尾的注释

选项名与分区名关联, 例如:

```ini
[gui.accessibility]
visual_bell=yes
```

等同于:

```ini
gui.accessibility.visual_bell=yes
```

所以在代码中加入选项是这样的:

```cpp
options_description desc;
desc.add_options()
    ("gui.accessibility.visual_bell", value<string>(), "flash screen for bell")
    ;    
```

#### 环境变量分析器

环境变量是字符串变量，所有程序都可以通过C语言运行库的`getenv`函数获得环境变量。

操作系统允许为一个给定的用户设置初始值，并且可以在命令行上进一步改变这些值。例如，在Windows中可以使用autoexec.bat文件, 在Unix中可以使用/etc/profile、~/.profile和~/.bash_profile文件。

因为环境变量可以为整个系统进行设置，所以它们特别适用于适用于所有程序的选项。

环境变量可以用`parse_environment`函数进行解析。该函数有几个重载版本。第一个参数总是一个`options_description`实例，第二个参数指定哪些变量必须被处理，以及哪些选项名称必须与之对应。为了描述第二个参数，我们需要考虑环境变量的命名规则。

如果你有一个应该通过环境变量指定的选项，你需要编造变量的名字。

+ 为了避免名称冲突，我们建议你为环境变量使用一个足够独特的前缀。

+ 另外，虽然选项名称很可能是小写的，但环境变量习惯上使用大写。

因此，对于一个选项名称代理，环境变量可能被称为`BOOST_PROXY`。在解析过程中，我们需要对这些名称进行反向转换。这是通过将选择的前缀作为`parse_environment`函数的第二个参数来完成的。比如说，如果你传递`BOOST_`作为前缀，而有两个变量，`CVSROOT`和`BOOST_PROXY`，第一个变量将被忽略，第二个变量将被转换为选项代理。

上述方案在很多情况下是足够的，但也可以作为`parse_environment`函数的第二个参数，传递任何接受`std::string`并返回`std::string`的函数。该函数将为每个环境变量被调用，并应返回选项的名称，或在变量被忽略时返回空字符串。

```cpp
// Copyright Thomas Kent 2016
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/program_options.hpp>

namespace po = boost::program_options;

#include <string>
#include <iostream>

std::string mapper(std::string env_var) {
  // ensure the env_var is all caps
  std::transform(env_var.begin(), env_var.end(), env_var.begin(), ::toupper);

  if (env_var == "PATH") return "path";
  if (env_var == "EXAMPLE_VERBOSE") return "verbosity";
  return "";
}

void get_env_options() {
  po::options_description config("Configuration");
  config.add_options()
          ("path", "the execution path")
          ("verbosity", po::value<std::string>()->default_value("INFO"),
           "set verbosity: DEBUG, INFO, WARN, ERROR, FATAL");

  po::variables_map vm;
  // 对于每一个环境变量(value), 都调用函数对象(封装了 mapper)来获取它的名称(name)
  // 如果返回了一个非空字符串, 那么就将其记入variables_map
  // 否则将其丢弃
  store(po::parse_environment(config, boost::function1<std::string, std::string>(mapper)), vm);
  notify(vm);

  if (vm.count("path")) {
    std::cout << "First 75 chars of the system path: \n";
    std::cout << vm["path"].as<std::string>().substr(0, 75) << std::endl;
  }

  std::cout << "Verbosity: " << vm["verbosity"].as<std::string>() << std::endl;
}

int main(int ac, char *av[]) {
  get_env_options();

  return 0;
}
```

### 类型

所有在命令行、环境变量或配置文件中传入的东西都是字符串。对于需要作为非字符串类型的值，`variables_map`中的值会尝试将其转换为正确的类型。

整数和浮点值会使用Boost的`lexical_cast`进行转换。

它将接受整数值，如 "41 "或"-42"。

它将接受十进制下的浮点值, 无论是科学计数法还是常见的浮点数表示法.

但是，C++中可用的十六进制、八进制和二进制表示法不被`lexical_cast`支持，因此将不能与`program_options`一起使用。

# 特定情形下的例子

## 非常见语法

有的时候, 标准的命令行语法并不够. 例如, gcc 编译器有"-frtti"和"-fno-rtti"选项, 这些选项并没有被直接支持.

对于这样的情况, program options 库允许用户提供一个额外的解析器. 在命令行中的每个元素被 program options 库解析之前, 这个额外的解析都可以被调用. 如果这个解析器在元素中检测到了对应的语法, 那么它就会返回可以被直接使用的这个选项的名字和值. 例如:

```cpp
pair<string, string> reg_foo(const string& s)
{
    if (s.find("-f") == 0) {
        if (s.substr(2, 3) == "no-")
            return make_pair(s.substr(5), string("false"));
        else
            return make_pair(s.substr(2), string("true"));
    } else {
        return make_pair(string(), string());
    }
}
```

以下是额外解析器的定义. 当我们解析命令行的时候, 我们会传入额外解析器:

```cpp
store(command_line_parser(ac, av).options(desc).extra_parser(reg_foo)
        .run(), vm);
```

以下是完整的例子:

```cpp
// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/** This example shows how to support custom options syntax.

    It's possible to install 'custom_parser'. It will be invoked on all command
    line tokens and can return name/value pair, or nothing. If it returns
    nothing, usual processing will be done.
*/


#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

using namespace boost::program_options;

#include <iostream>
using namespace std;

/*  This custom option parse function recognize gcc-style
    option "-fbar" / "-fno-bar".
*/
pair<string, string> reg_foo(const string& s)
{
    if (s.find("-f") == 0) {
        if (s.substr(2, 3) == "no-")
            return make_pair(s.substr(5), string("false"));
        else
            return make_pair(s.substr(2), string("true"));
    } else {
        return make_pair(string(), string());
    }
}

int main(int ac, char* av[])
{
    try {
        options_description desc("Allowed options");
        desc.add_options()
        ("help", "produce a help message")
        ("foo", value<string>(), "just an option")
        ;

        variables_map vm;
        store(command_line_parser(ac, av).options(desc).extra_parser(reg_foo)
              .run(), vm);

        if (vm.count("help")) {
            cout << desc;
            cout << "\nIn addition -ffoo and -fno-foo syntax are recognized.\n";
        }
        if (vm.count("foo")) {
            cout << "foo value with the value of "
                 << vm["foo"].as<string>() << "\n";
        }
    }
    catch(exception& e) {
        cout << e.what() << "\n";
    }
}
```

## 响应文件 - Response File

有些操作系统对命令行的长度有限制. 绕过这些限制的常用方法是使用响应文件. 响应文件是一个使用了与命令行相同语法的文件. 如果命令行中指定了响应文件的路径, 那么响应文件就会被当做命令行剩余的部分被加载和解析. 

program options 没有对响应文件提供直接的支持, 所以我们需要自己写一点代码.

1. 首先 要定义一个针对响应文件的选项:

    ```cpp
    ("response-file", value<string>(),
         "can be specified with '@name', too")
    ```

2. 然后需要一个额外的分析器来支持指定响应文件的标准语法

    ```cpp
    pair<string, string> at_option_parser(string const&s)
    {
        if ('@' == s[0])
            return std::make_pair(string("response-file"), s.substr(1));
        else
            return pair<string, string>();
    }
    ```

3. 最后, 每当"response-file"选项被找到, 我们就需要加载文件, 同时将其传递给命令行分析器. 这是最难的一部分, 我们会需要用到 Boost.Tokenizer 库, 它能够正常使用, 但是会有一些限制. 或者是考虑使用Boost.StringAlgo. 代码如下:

    ```cpp
    if (vm.count("response-file")) {
         // Load the file and tokenize it
         ifstream ifs(vm["response-file"].as<string>().c_str());
         if (!ifs) {
             cout << "Could not open the response file\n";
             return 1;
         }
         // Read the whole file into a string
         stringstream ss;
         ss << ifs.rdbuf();
         // Split the file content
         char_separator<char> sep(" \n\r");
         std::string ResponsefileContents( ss.str() );
         tokenizer<char_separator<char> > tok(ResponsefileContents, sep);
         vector<string> args;
         copy(tok.begin(), tok.end(), back_inserter(args));
         // Parse the file and store the options
         store(command_line_parser(args).options(desc).run(), vm);
    }
    ```

完整代码如下:

```cpp
// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/** This example shows how to handle response file.

    For a test, build and run:
       response_file -I foo @response_file.rsp

    The expected output is:
      Include paths: foo bar biz

    Thanks to Hartmut Kaiser who raised the issue of response files
    and discussed the possible approach.
*/


#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/tokenizer.hpp>
#include <boost/token_functions.hpp>
using namespace boost;
using namespace boost::program_options;

#include <iostream>
#include <fstream>
using namespace std;

// Additional command line parser which interprets '@something' as a
// option "config-file" with the value "something"
pair<string, string> at_option_parser(string const&s)
{
    if ('@' == s[0])
        return std::make_pair(string("response-file"), s.substr(1));
    else
        return pair<string, string>();
}

int main(int ac, char* av[])
{
    try {
        options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce a help message")
            ("include-path,I", value< vector<string> >()->composing(),
                 "include path")
            ("magic", value<int>(), "magic value")
            ("response-file", value<string>(),
                 "can be specified with '@name', too")
        ;

        variables_map vm;
        store(command_line_parser(ac, av).options(desc)
              .extra_parser(at_option_parser).run(), vm);

        if (vm.count("help")) {
            cout << desc;
        }
        if (vm.count("response-file")) {
            // Load the file and tokenize it
            ifstream ifs(vm["response-file"].as<string>().c_str());
            if (!ifs) {
                cout << "Could not open the response file\n";
                return 1;
            }
            // Read the whole file into a string
            stringstream ss;
            ss << ifs.rdbuf();
            // Split the file content
            char_separator<char> sep(" \n\r");
            string sstr = ss.str();
            tokenizer<char_separator<char> > tok(sstr, sep);
            vector<string> args;
            copy(tok.begin(), tok.end(), back_inserter(args));
            // Parse the file and store the options
            store(command_line_parser(args).options(desc).run(), vm);
        }

        if (vm.count("include-path")) {
            const vector<string>& s = vm["include-path"].as<vector< string> >();
            cout << "Include paths: ";
            copy(s.begin(), s.end(), ostream_iterator<string>(cout, " "));
            cout << "\n";
        }
        if (vm.count("magic")) {
            cout << "Magic value: " << vm["magic"].as<int>() << "\n";
        }
    }
    catch (std::exception& e) {
        cout << e.what() << "\n";
    }
}
```

以下是response_file.rsp

```
-I bar
-I biz
--magic 10
```

## Winmain 命令行

在Windows操作系统上，GUI应用程序接收的命令行是一个单一的字符串，而不是被分割成多个元素。由于这个原因，不能直接使用命令行解析器。至少在一些编译器上，有可能获得分割的命令行，但不清楚是否所有的编译器在所有版本的操作系统上都支持同样的机制。

基于这个原因, program options 函数提供了可移植的`split_winmain` 函数.

```cpp
vector<string> args = split_winmain(lpCmdLine);
store(command_line_parser(args).options(desc).run(), vm);
```

`split_winmain`函数对`wchar_t`字符串进行了重载，因此也可用于Unicode应用程序。

## 选项组与隐藏选项

将整个程序的所有选项放在一个`options_description`类里面存在一些问题:

+ 有的选项只针对特定的输入源有用, 例如配置文件
+ 用户可能希望生成的帮助信息有结构
+ 有些选项完全不应该出现在帮助信息中

要解决上面提到的问题, program options 允许创建`options_description`类的多个实例, 他们可以依照不同的方式合并. 

下面的例子定义了三个选项组: 一个指定了通过命令行生效的选项, 剩下的两个指定了程序的模式. 只有一个会在生成的帮助信息中显示.

每一个选项组都是用标准的语法声明, 但是, 你需要给每一个选项组一个合理的名字:

```cpp
options_description general("General options");
general.add_options()
    ("help", "produce a help message")
    ("help-module", value<string>(),
        "produce a help for a given module")
    ("version", "output the version number")
    ;

options_description gui("GUI options");
gui.add_options()
    ("display", value<string>(), "display to use")
    ;

options_description backend("Backend options");
backend.add_options()
    ("num-threads", value<int>(), "the initial number of threads")
    ;
```

在声明选项组之后, 就可以将他们合并到一起. 首先会将所有的选项都包含, 用于分析; 其次会被用于显示帮助信息:

```cpp
// Declare an options description instance which will include
// all the options
options_description all("Allowed options");
all.add(general).add(gui).add(backend);

// Declare an options description instance which will be shown
// to the user
options_description visible("Allowed options");
visible.add(general).add(gui);
```

剩下的就是分析和处理选项了:

```cpp
variables_map vm;
store(parse_command_line(ac, av, all), vm);

if (vm.count("help"))
{
    cout << visible;
    return 0;
}
if (vm.count("help-module")) {
    const string& s = vm["help-module"].as<string>();
    if (s == "gui") {
        cout << gui;
    } else if (s == "backend") {
        cout << backend;
    } else {
        cout << "Unknown module '"
             << s << "' in the --help-module option\n";
        return 1;
    }
    return 0;
}
if (vm.count("num-threads")) {
    cout << "The 'num-threads' options was set to "
         << vm["num-threads"].as<int>() << "\n";
}
```

在解析命令行的时候, 所有的选项都是允许的. 但是帮助信息并不会包含"Backend options"选项组, 这个选项组被隐藏了. 用户只能显式地调用"--help-module backend"选项来强制打印这部分帮助信息. 以下是完整的示例:

```cpp
// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/** This example shows how to handle options groups.

    For a test, run:

    option_groups --help
    option_groups --num-threads 10
    option_groups --help-module backend

    The first invocation would show to option groups, and will not show the
    '--num-threads' options. The second invocation will still get the value of
    the hidden '--num-threads' option. Finally, the third invocation will show
    the options for the 'backend' module, including the '--num-threads' option.

*/


#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/tokenizer.hpp>
#include <boost/token_functions.hpp>
using namespace boost;
using namespace boost::program_options;

#include <iostream>
#include <fstream>
#include <exception>
using namespace std;

int main(int ac, char* av[])
{
    try {
        // Declare three groups of options.
        options_description general("General options");
        general.add_options()
            ("help", "produce a help message")
            ("help-module", value<string>(),
                "produce a help for a given module")
            ("version", "output the version number")
            ;

        options_description gui("GUI options");
        gui.add_options()
            ("display", value<string>(), "display to use")
            ;

        options_description backend("Backend options");
        backend.add_options()
            ("num-threads", value<int>(), "the initial number of threads")
            ;

        // Declare an options description instance which will include
        // all the options
        options_description all("Allowed options");
        all.add(general).add(gui).add(backend);

        // Declare an options description instance which will be shown
        // to the user
        options_description visible("Allowed options");
        visible.add(general).add(gui);


        variables_map vm;
        store(parse_command_line(ac, av, all), vm);

        if (vm.count("help"))
        {
            cout << visible;
            return 0;
        }
        if (vm.count("help-module")) {
            const string& s = vm["help-module"].as<string>();
            if (s == "gui") {
                cout << gui;
            } else if (s == "backend") {
                cout << backend;
            } else {
                cout << "Unknown module '"
                     << s << "' in the --help-module option\n";
                return 1;
            }
            return 0;
        }
        if (vm.count("num-threads")) {
            cout << "The 'num-threads' options was set to "
                 << vm["num-threads"].as<int>() << "\n";
        }
    }
    catch(std::exception& e) {
        cout << e.what() << "\n";
    }
}
```

## 自定义的验证器

默认情况下, 将选项的值从字符串转换到 C++的类型是由`iostream`完成的, 但有时不是很方便. program options库允许用户针对一些特定的类自定义转换方式. 为了实现这样的功能, 用户需要提供一些合适的`validate`函数的重载.

首先需要定义一个简单的类:

```cpp
struct magic_number {
public:
    magic_number(int n) : n(n) {}
    int n;
};
```

然后重载`validate`函数:

```cpp
void validate(boost::any& v,
              const std::vector<std::string>& values,
              magic_number* target_type, int)
{
    static regex r("\\d\\d\\d-(\\d\\d\\d)");

    using namespace boost::program_options;

    // Make sure no previous assignment to 'a' was made.
    validators::check_first_occurrence(v);
    // Extract the first string from 'values'. If there is more than
    // one string, it's an error, and exception will be thrown.
    const string& s = validators::get_single_string(values);

    // Do regex match and convert the interesting part to
    // int.
    smatch match;
    if (regex_match(s, match, r)) {
        v = any(magic_number(lexical_cast<int>(match[1])));
    } else {
        throw validation_error(validation_error::invalid_option_value);
    }
}
```

上面这个函数接受四个参数. 

+ 第一个是值的存储，在这种情况下，要么是空的，要么包含`magic_number`类的一个实例.
+  第二个是在选项的下一次出现时发现的字符串列表.

剩下的两个参数是为了解决某些编译器上缺乏部分模板专用化和部分函数模板排序的问题。

函数首先确定我们没有尝试为同一个选项赋值两次. 然后确定只有一个字符串被传入了函数. 这个字符串会在 `Boost.Regex`类的帮助下完成检查. 如果检查通过, 那么这个被解析的值就会被存储到变量`v`中.

以下是完整的示例:

```cpp
// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// This example shows how a user-defined class can be parsed using
// specific mechanism -- not the iostream operations used by default.
//
// A new class 'magic_number' is defined and the 'validate' method is overloaded
// to validate the values of that class using Boost.Regex.
// To test, run
//
//    regex -m 123-456
//    regex -m 123-4567
//
// The first invocation should output:
//
//   The magic is "456"
//
// and the second invocation should issue an error message.

#include <boost/program_options.hpp>
#include <boost/regex.hpp>

using namespace boost;
using namespace boost::program_options;

#include <iostream>
using namespace std;

/* Define a completely non-sensical class. */
struct magic_number {
public:
    magic_number(int n) : n(n) {}
    int n;
};

/* Overload the 'validate' function for the user-defined class.
   It makes sure that value is of form XXX-XXX
   where X are digits and converts the second group to an integer.
   This has no practical meaning, meant only to show how
   regex can be used to validate values.
*/
void validate(boost::any& v,
              const std::vector<std::string>& values,
              magic_number*, int)
{
    static regex r("\\d\\d\\d-(\\d\\d\\d)");

    using namespace boost::program_options;

    // Make sure no previous assignment to 'a' was made.
    validators::check_first_occurrence(v);
    // Extract the first string from 'values'. If there is more than
    // one string, it's an error, and exception will be thrown.
    const string& s = validators::get_single_string(values);

    // Do regex match and convert the interesting part to
    // int.
    smatch match;
    if (regex_match(s, match, r)) {
        v = any(magic_number(lexical_cast<int>(match[1])));
    } else {
        throw validation_error(validation_error::invalid_option_value);
    }
}


int main(int ac, char* av[])
{
    try {
        options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce a help screen")
            ("version,v", "print the version number")
            ("magic,m", value<magic_number>(),
                 "magic value (in NNN-NNN format)")
            ;

        variables_map vm;
        store(parse_command_line(ac, av, desc), vm);

        if (vm.count("help")) {
            cout << "Usage: regex [options]\n";
            cout << desc;
            return 0;
        }
        if (vm.count("version")) {
            cout << "Version 1.\n";
            return 0;
        }
        if (vm.count("magic")) {
            cout << "The magic is \""
                 << vm["magic"].as<magic_number>().n << "\"\n";
        }
    }
    catch(std::exception& e)
    {
        cout << e.what() << "\n";
    }
}
```

## Unicode 字符集支持

要在 Unicode 字符集下使用 program options 库, 你首先需要:

+ 使用能够解析 Unicode 输入的 Unicode 解析器
+ 为需要 Unicode 值的选项提供 Unicode 支持

大多数解析器都提供了 Unicode 的版本. 例如, `parse_command_line`函数就提供了一个接收`wchar_t`字符串, 而不是普通`char`字符串的重载版本.

即使有一些解析器支持 Unicode, 这不意味着你需要改变所有选项的定义. 事实上, 对很多选项来说, 例如整型选项, 这没有任何意义. 要使用 Unicode, 你首先需要有一些需要 Unicode 值的选项. 他们和普通选项的区别在于他们接收 `wchar_t` 类型的输入, 并且使用宽字符流进行处理. 

创建一个支持 Unicode 的选项是很简单的: 只需要使用`wvalue`函数而不是常用的`value`函数即可.

当一个 ASCII 解析器将一个值传递给 ASCII 选项, 或者是一个 Unicode 解析器将一个值传递给一个 Unicode 选项, 这个值都不会有任何的改变. 所以, ASCII 选项会以 本地的 8-bit 格式看待这个字符串, 而 Unicode 选项则会以 Unicode 格式看待这个字符串.

但是如果将一个 Unicode 值传递给一个 ASCII 选项, 或者是反过来, 会发生什么? program options 库将会自动完成 Unicode 与 ASCII 之间的转换. 例如, 如果命令行是 ASCII 格式的, 但是你是用了`wchar_t`选项, 那么这个 ASCII 输入会被转换为 Unicode 格式.

要完成这样的转换, program options 库会使用全局的`codecvt<wchar_t, char>`. 如果你想要以本地的 8-bit 编码来进行工作, 那么你的程序需要以下面的代码开始:

```cpp
locale::global(locale(""));
```

这段代码会根据用户设置的编码格式进行转换.

不过，检查你的实现对C++语言的支持状况是明智的. 你可以使用下面的步骤来进行一个快速的检测:

1. 编译下面这段代码:

    minitest.hpp

    ```cpp
    #ifndef BOOST_PROGRAM_OPTIONS_MINITEST
    #define BOOST_PROGRAM_OPTIONS_MINITEST
    
    #include <assert.h>
    #include <iostream>
    #include <stdlib.h>
    
    #define BOOST_REQUIRE(b) assert(b)
    #define BOOST_CHECK(b) assert(b)
    #define BOOST_CHECK_EQUAL(a, b) assert(a == b)
    #define BOOST_ERROR(description) std::cerr << description; std::cerr << "\n"; abort();
    #define BOOST_CHECK_THROW(expression, exception) \
        try \
        { \
            expression; \
            BOOST_ERROR("expected exception not thrown");\
            throw 10; \
        } \
        catch(exception &) \
        { \
        }
    
    
    
    #endif
    ```

    

    ```cpp
    // Copyright Vladimir Prus 2002-2004.
    // Distributed under the Boost Software License, Version 1.0.
    // (See accompanying file LICENSE_1_0.txt
    // or copy at http://www.boost.org/LICENSE_1_0.txt)
    
    #include <cstring>
    #include <cassert>
    #include <string>
    #include <fstream>
    #include <sstream>
    #include <iostream>
    #include <boost/progress.hpp>
    #include <boost/bind.hpp>
    #include <boost/ref.hpp>
    
    #include <boost/program_options/detail/convert.hpp>
    #include <boost/program_options/detail/utf8_codecvt_facet.hpp>
    
    #include "minitest.hpp"
    
    using namespace std;
    
    string file_content(const string& filename)
    {
        ifstream ifs(filename.c_str());
        assert(ifs);
    
        stringstream ss;
        ss << ifs.rdbuf();
    
        return ss.str();
    }
    
    // A version of from_8_bit which does not use functional object, for
    // performance comparison.
    std::wstring from_8_bit_2(const std::string& s,
                              const codecvt<wchar_t, char, mbstate_t>& cvt)
    {
        std::wstring result;
    
    
        std::mbstate_t state = std::mbstate_t();
    
        const char* from = s.data();
        const char* from_end = s.data() + s.size();
        // The interace of cvt is not really iterator-like, and it's
        // not possible the tell the required output size without the conversion.
        // All we can is convert data by pieces.
        while(from != from_end) {
    
            // std::basic_string does not provide non-const pointers to the data,
            // so converting directly into string is not possible.
            wchar_t buffer[32];
    
            wchar_t* to_next = buffer;
            // Try to convert remaining input.
            std::codecvt_base::result r =
                cvt.in(state, from, from_end, from, buffer, buffer + 32, to_next);
    
            if (r == std::codecvt_base::error)
                throw logic_error("character conversion failed");
            // 'partial' is not an error, it just means not all source characters
            // we converted. However, we need to check that at least one new target
            // character was produced. If not, it means the source data is
            // incomplete, and since we don't have extra data to add to source, it's
            // error.
            if (to_next == buffer)
                throw logic_error("character conversion failed");
    
            // Add converted characters
            result.append(buffer, to_next);
        }
    
        return result;
    }
    
    
    void test_convert(const std::string& input,
                      const std::string& expected_output)
    {
        boost::program_options::detail::utf8_codecvt_facet facet;
    
        std::wstring output;
        {
            boost::progress_timer t;
            for (int i = 0; i < 10000; ++i)
                output = boost::from_8_bit(
                    input,
                    facet);
        }
    
        {
            boost::progress_timer t;
            for (int i = 0; i < 10000; ++i)
                output = from_8_bit_2(
                    input,
                    facet);
        }
    
        BOOST_CHECK(output.size()*2 == expected_output.size());
    
        for(unsigned i = 0; i < output.size(); ++i) {
    
            {
                unsigned low = output[i];
                low &= 0xFF;
                unsigned low2 = expected_output[2*i];
                low2 &= 0xFF;
                BOOST_CHECK(low == low2);
            }
            {
                unsigned high = output[i];
                high >>= 8;
                high &= 0xFF;
                unsigned high2 = expected_output[2*i+1];
                BOOST_CHECK(high == high2);
            }
        }
    
        string ref = boost::to_8_bit(output, facet);
    
        BOOST_CHECK(ref == input);
    }
    
    int main(int ac, char* av[])
    {
        std::string input = file_content("utf8.txt");
        std::string expected = file_content("ucs2.txt");
    
        test_convert(input, expected);
    
        if (ac > 1) {
            cout << "Trying to convert the command line argument\n";
    
            locale::global(locale(""));
            std::wstring w = boost::from_local_8_bit(av[1]);
    
            cout << "Got something, printing decimal code point values\n";
            for (unsigned i = 0; i < w.size(); ++i) {
                cout << (unsigned)w[i] << "\n";
            }
    
        }
    
        return 0;
    }
    ```

2. 在环境中设置一些非 ASCII 值, 例如:

    ```shell
    export LC_CTYPE=ru_RU.KOI8-R
    ```

3. 运行上面的测试代码，以所选编码的任何非ascii字符串作为其参数。如果你看到一个Unicode编码点的列表，那么一切都很好。否则，你系统上的语言支持可能被破坏了。

## 允许未知的选项

通常情况下，program options 库对未知的选项名称会抛出一个异常。这种行为可以被改变。例如，你的应用程序中只有一部分使用 program_options库，而你希望将不被识别的选项传递给程序的另一部分，甚至传递给另一个应用程序。

要允许命令行上的未注册选项，你需要使用`basic_command_line_parser`类进行解析（而不是`parse_command_line`）并调用该类的`allow_unregistered`方法：

```cpp
parsed_options parsed =
    command_line_parser(argc, argv).options(desc).allow_unregistered().run();
```

对于每个看起来像选项，但没有已知名称的标记，将在结果中添加一个`basic_option`的实例。实例的`string_key`和`value`字段将包含该标记的语法解析结果，`unregistered`字段将被设置为`true`，而`original_tokens`字段将包含该标记在命令行中出现的样子。

如果你想进一步传递未识别的选项，可以使用 `collect_unrecognized` 函数。该函数将收集所有未被识别的值的原始标记，并可选择收集所有发现的位置选项。

比方说，如果你的代码处理了一些选项，但完全没有处理位置选项，你可以这样使用这个函数：

```cpp
vector<string> to_pass_further = collect_unrecognized(parsed.options, include_positional);
```

## 测试选项是否存在

到目前为止，我们使用`variables_map`类上的`count`方法来测试一个选项是否已经被设置；由于你在重复选项的字符串名称，这很容易出现打字错误或在一个地方重命名选项而在另一个地方不重命名而导致错误：

```cpp
po::options_description desc("Allowed options");
desc.add_options()
    ("compression", po::value<int>(), "set compression level")
;

po::variables_map vm;
po::store(po::parse_command_line(ac, av, desc), vm);
po::notify(vm);

if (vm.count("compression")) {
    cout << "Compression level was set to "
 << vm["compression"].as<int>() << ".\n";
} else {
    cout << "Compression level was not set.\n";
}
```

相反，你可以使用一个`boost::option`类型的变量；program_options库为`Boost.Optional`提供了特殊支持，这样如果用户指定了选项，`boost::option`变量就会被初始化为相应的值：

```cpp
po::options_description desc("Allowed options");
boost::optional<int> compression;
desc.add_options()
    ("compression", po::value(&compression), "set compression level")
;

po::variables_map vm;
po::store(po::parse_command_line(ac, av, desc), vm);
po::notify(vm);

if (compression) {
    cout << "Compression level was set to " << *compression << ".\n";
} else {
    cout << "Compression level was not set.\n";
}
```

