> 命令行选项分析

[TOC]

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

    保存之后, 就可以使用这些选项了. `variable_map`能像`std::map`一样使用, 只是必须像代码示例中那样使用. 如果选项的实际值和`as`中指定的值类型不一样, 就会抛出一个异常.

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

    1. 我们传入了`opt`的地址, 在将命令行的值通过`notify`之后保存到`variable_map`之后, 命令行中的`optimization`的值也会被保存到`opt`之中
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

程序会选择已经被`store`存储到`variable_map`中的值, 代码中先对命令行的选项调用`store`, 再对配置文件调用`store`, 于是实际的运行效果是采用命令行中的选项。这就是`--optimization`选项的应对方式。

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
