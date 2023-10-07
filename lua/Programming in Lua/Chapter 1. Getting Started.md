[TOC]

> ```lua
> print("Hello World!")
> ```

# Chunks

Lua 中的每一段由文件或者交互模式下的每一行代码都被称为*chunk*.

一个*chunk*可以是一个简单的语句, 也可以是很多语句和函数定义的集合. 一个 chunk 可以按照我们的需求有任意大小.

```shell
❯ lua
Lua 5.3.6  Copyright (C) 1994-2020 Lua.org, PUC-Rio
> print ("Hello world!")
Hello world!
```

在 POSIX 上, 使用`ctrl-D`, 在Windows 上,使用`ctrl-z`来退出. 如果实在操作系统库中, 需要使用`os.exit()`

可以使用`lua -i prog`来让 Lua 在被提供一个chunk 之后以交互模式启动. 这在 debug 和手动测试的时候非常有用:

```lua
-- factorial.lua
-- defines a factorial function
function fact(n)
  if n == 0 then
    return 1
  else
    return n * fact(n - 1)
  end
end

print("enter a number: ")
a = io.read("*n")          -- reads a number
print(fact(a))
```

```shell
lua -i factorial.lua
```

另外一种方法是调用函数`dofile`, 这会立即执行文件.

```lua
function add(left, right)
  return left - right
end

function minus(left, right)
  return left - right
end
```

```shell
❯ lua
Lua 5.3.6  Copyright (C) 1994-2020 Lua.org, PUC-Rio
> dofile("operation.lua")
> a = 3
> b = 4
> add(a, b)
-1
```

`dofile`在测试代码的时候也非常有用. 例如: 一个窗口编辑代码, 一个窗口测试代码. 编辑结束后保存, 就可以直接在另一侧使用`dofile`直接载入测试.

# 一些词法传统

Lua 中的标识符可以是字符, 数字和下划线的字符串, 但是不能以数字开头.

同时, 也不应该使用以一个下划线开头, 用一个或多个大写字符开头的标识符(例如`_VERSION`). 在 lua 中这些标识符有特殊用途. 通常，虚拟变量保留标识符 `_`。

保留字:

<img src="Chapter 1. Getting Started.assets/image-20231007161352667.png" alt="image-20231007161352667" style="zoom:50%;" />

Lua 是一个大小写敏感的语言.

使用`--`用作单行注释, 使用`-- [[ <codes> --]]`用作多行注释, 这样, 只要在第一行注释的横线后多添一个, 就能够够取消注释: `---[[ <codes> --]]`.

对于连续代码, lua 不需要分隔符. 但是如果我们希望, 我们可以在中间加上`;`. Lua 中换行也不是必须的, 只是为了美观.

# 全局变量

全局变量不需要声明, 直接使用即可. 如果我们赋值`nil`给一个变量, Lua 的反应就好像我们没有使用过这个变量:

```shell
> b
nil
> b = 10
> b
10
> b = nil
> b
nil
```

但是这个变量对应的内存已经被占用了.

# 类型与值

Lua 是一个弱类型语言. lua 中没有类型声明, 但是每一个值都有自己的类型.

在 Lua 中有 8 中基本类型:

+ nil
+ Boolean
+ number
+ string
+ userdata
+ function
+ thread
+ table

函数`type`能够返回名称对应的类型:

```shell
> type(1)
number
> type(true)
boolean
> type(os.exit)
function
> type(type(1))
string
```

`type()`的返回值是一个字符串. `userdata`类型允许存储 C 语言数据. 因此在 Lua 中不能提前定义这样的类型, 而只能够被赋值和进行对应的测试. 举例来说, 标准 IO 库使用他们来标识打开的文件.

变量没有前置类型. 任何的变量可以存储任何类型的任意值.

# Nil

NIl 是一个只有一个值`nil`的类型. 它的作用是用来与其他类型相区别.

# Booleans

`Boolean`类型有两个值, `@false{}`和`@true{}`, 用来代表传统的布尔值. 但是, `Booleans`并不垄断条件值的使用权: 在 Lua 中, 所有类型都能代表一个条件. 除了`false`和`nil`, 所有其他的值都被视为`true`. 因此, ***0 和 空字符串也代表`true`***.

Lua 支持传统的逻辑运算: `and`, `or`和`not`. `not`和`or`都使用短路求值(short-circuit evaluation)机制.

在 Lua 中, 一个常用的机制为:

```lua
if not x then x = v end
```

它的作用是用来判断`x`是否已经被占用. 如果没有, 那么就赋予新值. 

`and`比`or`拥有更高的优先级:

```lua
((a and b) or c) -- (a and b or c)
```

这个式子可以当做 C 语言中的三目运算符`?:`

# 独立运行的解释器

一个独立运行的解释器(Stand-Alone Intepreter)是一个允许你直接使用 Lua 的轻巧程序.

当解释器加载一个文件的时候, 以井号`#`开头的第一行会被忽略. 这个特性允许我们像 POSIX系统 一样使用 Lua 的解释器.

如果我们以:

```shell
#! /usr/local/bin/lua
```

或者:

```shell
#! /usr/bin/env lua
```

的方式开启文件的第一行, 这就允许我们直接调用 Lua 解释器.

`lua`的调用格式:

```shell
lua [options] [script [args]]
```

+ `-e`允许我们直接从命令行中输入指令:

    ```shell
    ❯ lua -e "print('Hello World')"
    Hello World
    ```

+ `-i`加载一个库.

    ```shell
    ❯ lua -i -loperation -e "x = add(1, 2)"
    Lua 5.3.6  Copyright (C) 1994-2020 Lua.org, PUC-Rio
    > x
    -1
    ```

    一个脚本可以通过提前定义的全局变量`arg`来获取它的参数:

    ```shell
    lua -e "sin=math.sin" script a b
    ```

    那么对于解释器来说, 它收到的参数为:

    ```
    arg[-3] = "lua"
    arg[-2] = "-e"
    arg[-1] = "sin=math.sin"
    arg[0] = "script"
    arg[1] = "a"
    arg[2] = "b"
    ```

    
