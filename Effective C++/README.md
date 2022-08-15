# Effective C++

***55 Specific Ways to Improve your programs and designs. -- Scott Meyers***

> Third Edition

## Preface

### Translation Preface

1. Four programming paradigms: procedural-based, object-based, object-oriented, generics.
2. The true meaning of **object** in **Object Oriented** is ***a thing***, instead of ***target***.

## Introduction

### Terminology

1. We name `int x` an **object**, even though it is a build-in type.
2. A signature of a function contains **parameters** and **return type** thought the official C++ function signature doesn't contain return type.
3. Contructor functions declared with `explicit` prevent unexpected ***implict type conversion***, but they can still be used in ***explicit type conversion.*** Unless we have a good reason to allow implict type conversions, the implict contructor functions are prefered.
4. A ***pass-by-reference-to-const*** is usually a good choice.
5. A **client** is something or somebody who uses your code. The **client of function** is the caller of the function and is also whom write this part of code. The **client of `class` or `template`** is the part the program uses it. And the **client** for programmers.
6. Use **ctor** for constructor function and **dtor** for destructor function.

### Naming Convertions

1. **lhs** for **left-hand side** and **rhs** for **right-hand side**

## Accustoming Yourself to C++

### No 1. Consider C++ a union of different parts

> Nowadays, C++ is multiparadigm programming language, which contains ***procedural***, ***objetc-oriented***, ***functional***, ***generic*** and ***metaprogramming***.

To understand C++, we need to get to know four sub-languages, which are:

1. C
2. Object-Oriented C++
3. Template C++
4. STL

When we switch one to another one, the rule we programming is also changed. 

For example, for build-in type(C-like) programming, *pass-by-value* is usually more efficient than *pass-by-reference*. However, things change when we switched to Object-Oriented C++. Because of **user-defined** ctor and dtor, **pass-by-reference-to-const** is usually better. Especially in templates for we don't even know what we are dealling with. But we will find **pass-by-value** also work in iterators and functor of STL for they are created from C pointer.

### No 2. Prefer `const`, `enum`, `inline` to `#define`


