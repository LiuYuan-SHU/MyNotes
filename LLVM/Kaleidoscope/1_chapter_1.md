# 第一章

## 教程简介

> 使用 LLVM 实现 Kaleidoscope 语言. 

目录:

1. [第一章](1_chapter_1.md): Kaleidoscope的介绍, 以及其语法的定义. 为了让本教程在最大限度上易于理解, 本教程选择使用 C++而不是任何的词法分析程序和分析器生成器, 但是 LLVM 能够支持
2. [第二章](): 实现分析器和 AST(Abstract Semantic Tree), 到第二章为止, 这些代码都不需要 LLVM
3. [第三章](): 将代码生成为 LLVM IR.
4. [第四章](): 添加 JIT 和优化器支持
5. [第五章](): 控制流
6. [第六章](): 用户自定义操作符
7. [第七章](): 可变参数
8. [第八章](): 编译为目标代码
9. [第九章](): 调试信息
10. [第十章](): 总结和其他信息

## 基础语言

Kaleidoscope 是一个过程性语言, 它支持函数, 条件语句, 数学运算等等. 在本教程中, 将会讲述如何让Kaleidoscope 支持`if/then/else`构造, 一个`for`循环, 用户自定义运算符, 一个包含简单的命令行接口的 JIT 编译

为了让事情简单一些, Kaleidoscope 支持的数据类型只有 64bit 的浮点类型(`double` in C). 以下是一个斐波那契数的计算函数:

```
def fib(x)
  if x < 3 then
    1
  else
    fib(x - 1) + fib(x - 2)

fib(40)
```

我们同样允许 Kaleidoscope 来调用标准库函数(LLVM JIT 让这件事变得非常简单). 这意味着我们可以在使用一个函数前使用`extern`关键字来定义它, 这在互递归函数(mutually recursive functions)中很有用.

```
extern sin(arg);
extern cos(arg);
extern atan2(arg1, arg2);

atan2(sin(.4), cos(42))
```

## 词法分析器(Lexer)

在实现一种语言时, 首先要完成的工作就是能够读取并分析一串字符串的含义. 常规的做法是使用一个"lexer"(也就是扫描器*scanner*), 来将输入分割为*tokens*. 每一个词法分析器返回的 *token* 都包含一个 *token* 码和某种可能的元数据(例如某个数字的值). 首先我们需要定义元数据的种类:

```cpp
enum Token {
  tok_eof = -1;

  // commands
  tok_def = -2;
  tok_extern = -3;

  // primary
  tok_identifier = -4;
  tok_number = -5;
};

static std::string IdentifierString;  // Filled in if to_identifier
static double NumVal;                 // Filled in if tok_number
```

每一个由词法分析器返回的 *token* 要么是`Token`枚举类中的值, 要么就是一个未识别的字符, 例如`+`, 这个值将会以其 ASCII 值直接返回. 如果当前的 *token* 是一个标识符(identifier), 那么全局变量`IdentifierStr`就会记录这个标识符的名称. 如果当前 *token* 是一个数字常量(numeric literal), 例如`1.0`, `NumVal`就会记录其值. 需要注意的是, 此处使用全局变量只是为了方便, 但是并不是在真实语言实现下的最好选择.

词法分析器的实现通过一个叫做`gettok`的函数. 这个函数在被调用之后将会返回标准输入的下一个*token*.

```cpp
static int gettok() {
  static int LastChar = ' ';

  // Skip any whitespace.
  while (isspace(LastChar)) {
    LastChar = getchar();
  }
}
```

`gettok`通过调用 C 语言的`getchar()` 函数来每次从标准输入中获得一个字符. 其将其读到的字符保留在`LastChar`中, 但并不分析. 它完成的首要工作是忽略*token*之间的空格.

`gettok`的下一个任务是识别标识符和特殊的关键字例如`def`.

```cpp
if (isalpha(LastChar)) { // identifier: [a-zA-Z][a-zA-Z0-9]
  IdentifierStr = LastChar;
  while (isalnum((LastChar = getchar())))
    IdentifierStr += LastChar;

  if (IdentifierStr == "def")
    return tok_def;
  if (IdentifierStr == "extern")
    return tok_extern;

  return tok_identifier;
}
```

需要注意到的是, 当识别到标识符的时候, 这段代码会设置`IdentifierStr`来保存标识符的名称. 同时, 由于语言的关键字也满足相同的循环, 我们在这里一并处理. 数字值的处理过程类似:

```cpp
if (isdigit(LastChar) || LastChar == '.') { // Number: [0-9.]+
  std::string NumStr;
  do {
    NumStr += LastChar;
    LastChat = getchar();
  } while (isdigit(LastChar) || LastChar == '.');

  NumVal = strtod(NumStr.c_str(), 0);
  return tok_number;
}
```

这样的处理代码非常直白. 当程序读取到数字值的时候, 其使用 C 函数 `strtod` 来将其转换为一个数字值, 将其保存到`NumVal`中. 需要注意的是, 这里并没有做足够的错误检查: 形如`1.23.45.678`的输入会被解析为`1.23`. 当然, 这处理起来非常容易, 只需要增加一些判断即可.

接下来处理注释:

```cpp
if (LastChar == '#') {
  // Comment until end of line
  do 
    LastChar = getchar();
  while (LastChar != EOF && LastChar != '\n' && LastChar != 'r');

  if (LastChar != EOF) 
    return gettok();
}
```

我们通过跳过当前行的方式来跳过当前行, 并返回下一个*token*. 最终, 如果输入不满足上述的任意情况, 那么它要么是一个运算符字符, 例如`+`, 要么文件就应当结束.

```cpp
// Check for end of file. Don't eat the EOF
if (LastChar == EOF) {
  return tok_eof;
}

// Otherwise, just return the character as its ascii value
int ThisChar = LastChar;
LastChar = getchar();
return ThisChar;
```

通过这样的方式, 我们就实现了Kaleidoscope的词法分析器. 接下来我们将会编写一个使用这个词法分析器的分析器, 通过这个分析器我们将能够构建抽象语法树 AST.