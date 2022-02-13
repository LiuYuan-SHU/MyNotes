# JDBC

1. 概念

   Java DataBase Connectivity  ，Java数据库连接，Java语言操作数据库

   - 本质
   
     ![JDBC的本质](E:\刘元\学校\大学\大二\Java\JDBC\亿图图示工程文件\JDBC的本质.png)
   
     其实是官方（sun公司）定义的一套操作所有关系型数据库的规则，即接口。各个数据库厂商去实现这套借口，提供数据库驱动jar包。我们可以使用这套接口（JDBC)编程，真正执行的代码是驱动jar包中的实现类
   
2. 快速入门

   步骤：

   1. 导入驱动jar包
      1. 复制jar包到项目的lib目录下
      2. 右键-->Add as Library
   2. 注册驱动
   3. 获取数据库连接对象 `Connection`
   4. 定义sql
   5. 获取执行sql语句的对象 Statement
   6. 执行sql，接受返回的结果
   7. 处理结果
   8. 释放资源

# JDBC类详解

## DriverManager：驱动管理对象

1. 功能

   1. 注册驱动：告诉程序该使用哪一个数据库驱动jar

      ```java
      static void println(String message)
      //注册与给定的驱动程序DriverManager 
      ```

      写代码使用：`Class.forName("com.mysql.cj.jdbc.Driver");`

      通过查看源码发现：在`com.mysql.cj.jdbc.Driver`类中存在静态代码块

      ```java
      static {
              try {
                  DriverManager.registerDriver(new Driver());
              } catch (SQLException var1) {
                  throw new RuntimeException("Can't register driver!");
              }
          }
      ```

      **注意：**mysql5之后的驱动jar包可以省略注册驱动的步骤

      

   2. 获取数据库连接

      | `static Connection` | `getConnection(String url, String user, String password)`Attempts to establish a connection to the given database URL. |
      | ------------------- | ------------------------------------------------------------ |
      | 参数                | <code>url</code>：指定连接的路径                             |
      | 语法                | `jdbc:mysql://ip地址(域名):端口号/数据库名称`                |
      | 例子                | `jdbc:mysql://localhost:3306/db1`                            |
      | 细节                | 如果连接的是本机的mysql服务器，并且mysql服务默认端口是3306，则url可以简写为：`jdbc:mysql:///数据库名称` |
      | 参数                | <code>user</code>：用户名                                    |
      | 参数                | <code>password</code>：密码                                  |

      

## Connection：数据库连接对象

1. 功能：

   1. 获取执行sql的对象

      | `Statement`         | `createStatement()`Creates a `Statement` object for sending SQL statements to the database. |
      | ------------------- | ------------------------------------------------------------ |
      | `PreparedStatement` | `prepareStatement(String sql)`Creates a `PreparedStatement` object for sending parameterized SQL statements to the database. |

   2. 管理事务

      1. 开启事务

         | `void` | `setAutoCommit(boolean autoCommit)`Sets this connection's auto-commit mode to the given state. |
         | ------ | ------------------------------------------------------------ |
         |        | 调用该方法设置参数为false，即开启事务                        |

      2. 提交事务

         | `void` | `commit()`Makes all changes made since the previous commit/rollback permanent and releases any database locks currently held by this `Connection` object. |
         | ------ | ------------------------------------------------------------ |
         |        |                                                              |

      3. 回滚事务

         | `void` | `rollback()`Undoes all changes made in the current transaction and releases any database locks currently held by this `Connection` object. |
         | ------ | ------------------------------------------------------------ |
         |        |                                                              |

## Statement：执行sql的对象

**The object used for executing a static SQL statement and returning the results it produces.**

1. 执行sql

   1. | `boolean`                     | `execute(String sql)`Executes the given SQL statement, which may return multiple results. |
      | ----------------------------- | ------------------------------------------------------------ |
      | 可以执行任意的sql（了解即可） | **Returns:**`true` if the first result is a `ResultSet` object; `false` if it is an update count or there are no results |

   2. | `int`        | `executeUpdate(String sql)`Executes the given SQL statement, which may be an `INSERT`, `UPDATE`, or `DELETE` statement or an SQL statement that returns nothing, such as an SQL DDL statement. |
      | ------------ | ------------------------------------------------------------ |
      |              | 执行DML（通常）语句和DDL语句                                 |
      | **Returns:** | either (1) the row count for SQL Data Manipulation Language (DML) statements or (2) 0 for SQL statements that return nothing |

   3. | `ResultSet` | `executeQuery(String sql)`Executes the given SQL statement, which returns a single `ResultSet` object. |
      | ----------- | ------------------------------------------------------------ |
      |             | 执行DQL（select）语句                                        |

2. 练习

   1. account表 添加一条记录
   2. account表 修改一条记录
   3. account表 删除一条记录

## ResultSet：结果集对象，封装查询结果

- boolean next():光标从当前位置向前移动一行，判断当前行是否是最后一行末尾，如果是，返回false，否则返回true

- getXxx(参数):获取数据

  - Xxx：数据类型	如：int getInt()		String getString()
  - 参数：
    1. `int`：代表列的编号，从1开始  如：`getInt(1)`
    2. `String`：代表列的名称  如：`getDouble(balance)`

- 注意

  - 使用步骤
    1. 游标向下移动一行
    2. 判断是否有数据
    3. 获取数据

- 练习

  - 定义一个方法，查询emp表的数据将其封装为对象，然后装载集合，返回

    1. 定义Emp类

    2. 定义方法

       ```java
       public List<Emp> findAll(){}
       ```

    3. 实现方法

       ```mysql
       select * from emp;
       ```

       

## PreparedStatement：执行sql的对象

1. SQL注入问题：在拼接sql时，有一些sql的特殊关键字符与字符串的拼接。会造成安全性问题

   1. 输入用户随便，输入密码：

      ```sql
      a` or `a` = `a
      ```

      

   2. sql：

      ```sql
      select * from user where username = 'fhdsjkf' and password = 'a' or 'a' = 'a'
      -- false OR true --> 永远是true
      ```

2. 解决sql注入问题：使用PreparedStatement对象来解决

3. 预编译的sql：参数使用`?`作为占位符

4. 步骤：

   1. 导入驱动jar包

   2. 注册驱动

   3. 获取数据库连接对象 `Connection`

   4. 定义sql

      - 注意：sql的参数使用`?`作为占位符，如

        ```mysql
        select * from user where username = ? and password = ?;
        ```

        

   5. 获取执行sql语句的对象 `PreparedStatement`

      ```java
      Connection.perpareStatement(String sql)
      ```

      

   6. 给`?`赋值：

      - 方法：`setXxx(参数1,参数2)`
      - 参数1：`?`的位置编号 从1开始
      - 参数2：`?`的值

   7. 执行sql，接受返回的结果，不需要传递sql语句

   8. 处理结果

   9. 释放资源

5. 注意：后期都会使用PreparedStatement来完成增删改查的所有操作

   1. 可以防止SQL注入
   2. 效率更高
   
   



## 抽取JDBC工具类

- 目的：简化书写

- 分析：
  1. 注册驱动抽取

  2. 抽取一个方法获取链接对象

     - 需求：不想传递参数（太麻烦），还要保证工具类的通用性

     - 解决：配置文件

       jdbc.properties

       ​		url = 

       ​		user = 

       ​		password = 

  3. 释放资源
  
- 练习：

  - 需求
    1. 通过键盘录入用户名和密码
    2. 判断用户是否登录成功
       - `select * from user where username = "" and password = "";`
       - 如果这个sql有查询结果则成功，反之失败



## 使用JDBC控制事务

1. 事务：一个包含多个步骤的业务操作。如果这个业务操作被事务管理，则这多个步骤要么同时成功，要么同时失败

2. 操作：

   1. 开启事务
   2. 提交事务
   3. 回滚事务

3. 使用`Connection`对象来管理事务

   1. 开启事务

      | `void` | `setAutoCommit(boolean autoCommit)`Sets this connection's auto-commit mode to the given state. |
      | ------ | ------------------------------------------------------------ |
      |        | 调用该方法设置参数为false，即开启事务                        |
      |        | 在执行sql之前开启事务                                        |
   
   2. 提交事务
   
      | `void` | `commit()`Makes all changes made since the previous commit/rollback permanent and releases any database locks currently held by this `Connection` object. |
      | ------ | ------------------------------------------------------------ |
      |        | 在所有sql都执行完后提交事务                                  |
   
   3. 回滚事务
   
      | `void` | `rollback()`Undoes all changes made in the current transaction and releases any database locks currently held by this `Connection` object. |
      | ------ | ------------------------------------------------------------ |
      |        | 在catc中回滚事务                                             |
   



# 数据库连接池

1. 概念：容器（一个集合），存放数据库连接的容器

   当系统初始化好后，容器被创建，容器中会申请一些连接对象，当用户来访问数据库时，从容器中获取连接对象，用户访问完之后，会将连接对象归还给容器

2. 好处

   1. 节约资源
   2. 用户访问高效
   
3. 实现
   
   1. 标准接口：DataSource	javax.sql包下的
   
      1. 方法：
   
         - 获取连接：`getConnection()`
   
         - 归还连接：`Connection.close()`
   
           如果连接对象`Connection`是从连接池中获取的，那么调用`Connection.close()`方法，则不会在关闭连接了。而是归还连接
   
         - 
   
   2. 一般我们不去实现它，由数据库厂商去实现
   
      1. C3P0：数据库连接池技术
      2. Druid：数据库连接池实现技术，由阿里巴巴提供的
   
4. C3P0：数据库连接池技术

5. Druid：数据库连接池实现技术，由阿里巴巴实现

   1. 步骤
     1. 导入jar包
     2. 定义配置文件：
        - 是properties形式的
        - 可以叫任意名称，可以放在任意目录下
     3. 加载配置文件`Properties`
     4. 获取数据库连接池对象：通过工厂类来获取`DruidDataSourceFactory`
     5. 获取连接：`getConnection` 
   2. 定义工具类
      1. 定义一个类 JDBCUtils
      2. 提供静态代码块加载配置文件，初始化连接池对象
      3. 提供方法
         1. 获取连接方法：通过数据库连接池获取连接
         2. 释放资源
         3. 获取连接池的方法



# Spring JDBC - JDBC Template

- Spring框架对JDBC简单封装。提供了一个JDBCTemplate对象简化JDBC的开发
- 步骤：
  1. 导入jar包
  2. 创建JDBCTemplate对象。依赖于数据源DataSource
     - `JDBCTemplate template = new JDBCTemplate(ds);`
  3. 调用JDBCTemplate的方法来完成CRUD的操作
     - `update()`：执行增删改语句
     - `quieryForMap()`：查询结果将结果集封装为map集合
     - `quieryForList()`：查询结果将结果集封装为LIst集合
     - `quiery()`：查询结果将结果集封装为JavaBean对象
       - query的参数：`Roamapper`
         - 一般我们使用`BeanPropertyMapper`实现类。可以完成数据到`JavaBean`的自动封装
         - `List<Emp> list = jdbcTemplate.query(sql,new BeanPropertyRowMapper<类型>(类型.class));`
     - `quieryForObject()`：查询结果将结果集封装为对象
       - 一般用于聚合函数的查询
  4. 练习
     - 需求
       1. 修改1号数据的 salary 为 10000
       2. 添加一条记录
       3. 删除刚才添加的记录
       4. 查询所有记录，将其封装为Map结合
          - 这个方法查询的结果集长度只能是1，将列名作为key，将值作为value 将这条记录封装成一个map
       5. 查询所有记录，将其封装为Emp对象的List集合
          - 将每一条记录封装为一个Map集合，再将多个Map集合装在List集合中
       6. 查询总记录数



