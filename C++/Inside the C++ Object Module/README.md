# Inside the C++ Object Module

> 《深度探索C++对象模型 - 侯杰译》
>
> by Stanley B. Lippman

## 什么是C++对象模型？

1. 语言中直接支持面向对象程序设计的部分
2. 对于各种支持的底层实现机制

## 本书组织

第一章，***关于对象（Object Lessons）***，提供以对象为基础的观念背景，以及由C++提供的面向对象程序设计范式（paradigm）。

第二章，***构造函数语义学（The Semantics of Constructors）***，详细讨论constructor如何工作。本章谈到constructor何时被编译器合成，以及给你的程序效率带来什么样的意义。

> ###### 第三章至第五章是本书的重要内容。在这里，本书详细地讨论了C++对象模型的细节。

第三章，***Data语义学（The Semantics of Data）***，讨论数据成员的处理。

第四章，***Function语义学（The Semantics of Function）***，专注于各式各样的对象函数，并特别详细地讨论如何支持虚函数

第五章，***构造、析构、拷贝语义学（Semantics of Construction, Destruction, and Copy）***，讨论如何支持class模型，也讨论到object的生命期。

第六章，***执行期语义学（Runtime Semantics）***，查看执行期的某些对象模型。包括临时性对象的生命及其死亡，以及对`new`运算符和`delete`运算符的支持

第七章，***On the Cusp of the Object Module***，专注于exception handling，template support，runtime type identification

