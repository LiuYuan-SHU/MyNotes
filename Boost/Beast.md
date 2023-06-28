[TOC]

# CMake加载

```cmake
find_package(Boost REQUIRED)
include_directories(${BOOST_INCLUDE_DIR})
```

# 介绍

该库为以下目的而设计:

+ 对称性： 算法是不分角色的；建立客户端、服务器或两者。
+ 易用性：Boost.Asio的用户会立即理解Beast。
+ 灵活性： 用户可以做出重要的决定，如缓冲区或线程管理。
+ 性能： 构建处理成千上万连接的应用程序。
+ 进一步抽象的基础: 组件很适合在此基础上进行构建。

这个库不是一个客户端或服务器，但它可以用来构建那些东西。

