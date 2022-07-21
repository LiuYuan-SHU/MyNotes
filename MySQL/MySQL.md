# MySQL自学

## DBMS（数据库管理系统）

MySQL：关系数据库管理系统：管理关系数据库，并将数据进行存取的系统

## 数据持久化

-   持久化（presistence）：把数据保存到可掉电式存储设备以供之后使用。大多数情况下，特别是企业级应用，数据持久化意味着将内存中的数据保存到硬盘上加以“固化”，而持久化的实现过程大多通过各种关系数据库来完成
-   持久化的主要应用是将内存中的数据存储在关系型数据库中，当然也可以存储在磁盘文件，XML数据文件中

### RDBMS

常用的关系数据库管理系统产品：MySQL、Oracle、DB2、SQL Server、Sybase。

MySQL：中大型数据库——百万级数据

其余：大型数据库——千万级数据

# SQL

结构化查询语言***（Structured Query Language）***简称SQL，结构化查询语言是一种数据库查询和程序设计语言，用于存取数据以及查询、更新和管理数据系统

## DML

用于查询与修改数据记录

1.  INSERT：添加数据到数据库中

2.  UPDATE：修改数据库中的数据

3.  DELETE：删除数据库中的数据

4.  SELECT：选择（查询）数据 —— 最重要的SQL语言基础


## DDL

用于定义数据库的结构，比如创建、修改或删除数据库对象，包括如下SQL语句：

1.  CREATE TABLE：创建数据库表

2.  ALTER TABLE：更改表结构、添加、删除、修改列长度

3.  DROP TABLE：删除表

4.  CREATE INDEX：在表上建立索引

5.  DROP INDEX：删除索引

## [DCL](#DCL_detailed)

用来控制数据库的访问，包括如下SQL语句：

-   GRANT：授予访问权限
-   REVOKE：撤销访问权限
-   COMMIT：提交事务处理
-   ROLLBACK：事务处理回退
-   SAVEPOINT：设置保存点
-   LOCK：对数据库的特定部分进行锁定

## SQL通用语法

-   支持多行书写，以分号结束
-   可以使用空格和缩进来增强语句的可读性
-   MySQL数据库的SQL语句不区分大小写，关键字建议使用大写

## 三种注释

单行注释：

1.  `-- + 一个空格`
2.  `#`

多行注释：

1.  `/*  */`



# 数据类型

1.  int：整数类型

    `age int,`

2.  double：小数类型

    `score double(5,2)`（长度最长为5，保留2位小数）

3.  date：日期，只包含年月日，yyyy-MM-dd

4.  datetime：日期，包含年月日，时分秒 yyyy-MM-dd HH:mm:ss

5.  timestamp：时间戳，包含年月日，时分秒 yyyy-MM-dd HH:mm:ss

    -   如果将来不给这个字段赋值，或赋值为null，则默认使用当前的系统时间，来自动赋值

6.  varchar：字符串

    `name varchar(20);`（姓名：最大20个字符）

7.  BLOB - 大文件

# 数据库操作 - [DDL](#DDL)

## 创建数据库

-   创建数据库

    `create database 数据库名称;`

-   在创建数据库之前判断是否存在数据库

    `create database if not exists 数据库名称;`

-   在创建数据库的时候制定字符集

    `create database 数据库名称 character set 字符集名称;`

-   使用数据库

    `use 数据库名称`

## 删除数据库

删除数据库

`drop database 数据库名称;`

`drop database if exists 数据库名称; `

## 修改数据库

修改数据库的字符集

`alter database 数据库名称 character set 字符集名称;`

## 查询数据库

-   查询所有数据库的名称

    `show databases;`

-   查询某个数据库中所有的表名称

    `show tables;`

-   查询某个数据库的字符集

    `show create database 数据库名称;`

-	查询当前正在使用的数据库名称

    `select database();`



# 表操作 - [DDL](#DDL)

## 查询表

`desc(describe) 表名称;`

## 创建表

```sql
create table 表名(
    列名1	数据类型1,
    列名2	数据类型2,
    ...
    列名n	数据类型n
);
```

```sql
create table student(
	id int,
	name varchar(32),
    age int,
    score double(4,1) default 0,
    birthday date,
    insert_time timestamp default CURRENT_TIME
);
```

### 复制表

`create table 表名2 like 表名1;`

## 删除表

`drop table if exists 表名;`

## 修改表

### 修改表的名称

`alter tabale 表名 rename to 新的表名;`

### 修改表的字符集 

`alter table 表名 characer set 字符集名称;`

### 添加列

`alter table 表名 add 列名 数据类型 (first);`

1. 如果定义了`first`，那么就添加到第一列，否则最后一列。
2. 在表的指定位置之后添加字段：

```mysql
alter table 表名 add 列名 数据类型 after 列名
```

### 修改列的名称和类型

1. `alter table 表名 change 列名 新列名 新数据类型;`
2. `alter table 表名 modify 列名 新数据类型;`

### 删除列

`alter table 表名 drop 列名`

# 数据操作 - [DML](#DML)

## 增加数据

### 基本语法

`insert into 表名(列名1,列名2,...,列名n) values(值1,值2,...,值n);`

注意：

-   列名和值一一对应
-   如果表名后不定义列名，则默认给所有列添加值
-   除了数字类型，其他类型需要用引号引起来，单双引号都可以

## 删除数据

语法

`delete from 表名 [where 条件];`



注意：

-   如果不加条件，则删除表中所有记录
-   如果要删除所有记录
    1.  `delete from 表名;` ——不推荐使用。效率较低
    2.  `truncate table 表名;` —— 删除表，然后创建一个一模一样的空表

## 修改数据

语法

`update 表名 set 列名1 = 值1, 列名2 = 值2,... [where 条件];`



注意：

1.  如果不加条件，则修改表中所有的记录

# 数据查询 - [DQL](#DQL)

查询表中的记录

1.  从表中查询所有的数据

    `select * from 表名;`

语法：

1.  select

    字段列表

2.  from

    表名列表

3.  where

    条件列表

4.  group by

    分组列表

5.  having

    分组之后的条件

6.  order by

    排序

7.  limit

    分页限定

## 基础查询

1.  多个字段的查询

    `select 字段名1,字段2,...,from 表名;`

    注意：

    ​		如果查询所有字段，则可以使用*来替代字段列表

2.  去除重复

    `distinct`

3.  计算列

    一般可以使用四则运算来计算一些列的值。（一般只能进行数值型的计算）

    `ifnull(表达式1,表达式2);`

    ​		表达式1：那个字段需要判断是否是NULL

    ​		表达式2：如果该字段为null后的替换值

4.  起别名

    `列名 as 别名`

```sql
create table student(
	id int, -- 编号
    name varchar(20), -- 姓名
    age int, -- 年龄
    sex varchar(5), -- 性别
    address varchar(100), -- 地址
    math int, -- 数学
    english int -- 英语
);

insert into student values
(1,'马云',55,'男','杭州',66,78),
(2,'马化腾',45,'女','深圳',98,87),
(3,'马景涛',55,'男','香港',56,77),
(4,'柳岩',20,'男','湖南',76,65),
(5,'柳青',20,'男','湖南',86,null),
(6,'刘德华',57,'男','香港',99,89),
(7,'马德',22,'女','香港',99,99),
(8,'德玛西亚',18,'男','南京',56,65);

select * from student;

-- 查询姓名和年龄
select 
	name,
    age 
from
	student;
    
-- 查询地址
select address from student;

-- 去除重复的结果集
select distinct address from student;
select distinct name,address from student;

-- 计算math和English分数之和
select name,math,english,math+english from student;
/*如果有null参与的运算，计算结果都是null*/
select 
	name,
	math,
	english,
	math+ifnull(english,0) 
from student;

-- 起别名
select 
	name,
	math as 数学,
	english as 英语,
	math+ifnull(english,0) as 总分
from student;
```

## 条件查询

1.  where子句有跟条件

2.  运算符

    1.  `< , > , <= , >= , = , <>`

        `<>`是不等于，在MySQL中可以使用`!=`

    2.  `between...and`

    3.  `like`

        占位符：

        ​	`_`：单个任意字符

        ​	`%`：多个任意字符

    4.  `is null`

    5.  `and`或`&&`

    6.  `or`或`||`

    7.  `not`或`!`

```sql
select * from student;

-- 查询年龄大于20岁
select * from student where age>20;
-- 查询年龄等于20岁
select * from student where age=20;
-- 查询年龄不等于20岁
select * from student where age!=20;

-- 年龄大于等于20，小于等于30
select * from student where age >=20 and age <=30;
select * from student where age between 20 and 30;

-- 查询年龄22,18,25的人
select * from student where age = 22 or age = 18 or age = 25;
select * from student where age in (22,18,25);

-- 查询英语成绩为null的学生
select * from student where english = null; -- 不正确，null不可以使用=(!=)来判断
select * from student where english is null;

-- 查询英语成绩不为null的学生
select * from student where english is not null;

-- 查询姓马的有哪些？
select * from student where name like '马%';
-- 查询第二个字是化的人
select * from student where name like '_化%';
-- 查询姓名是三个字的人
select * from student where name like '__';
-- 查询姓名中包含德的人
select * from student where name like '%德%';
```

## 排序查询

语法

`order by 排序字段1 排序方式1, 排序字段2 排序方式2 ...`

排列方式

- ASC：升序，默认方式
- DESC：降序 

注意

1. 如果有多个排序条件，则当前面的条件值一样时，才会判断第二条件

```mysql
-- 按照数学成绩排名，如果数学成绩一样，则按照英语成绩排名
select * from student order by 
	math ASC,
    english ASC;
```

## 聚合函数

将一列数据作为整体，进行纵向计算

聚合函数：

1. count：计算个数

   - 一般选择非空的列：主键
   - count(*)

   ```mysql
   select count(name)  from student;
   select count(ifnull(english,0)) from student;
   select count(*) from student; -- 并不是很推荐
   ```

   

2. max：计算最大值

3. min：计算最小值

4. sum：求和

5. avg：计算平均值

注意：

1. 聚合函数的计算，排除null值

   解决方案

   1. 选择不包含非空的列进行计算
   2. ifnull函数



## 分组查询

语法

`group by 分组字段`

注意：

1. 分组之后查询的字段：分组字段、聚合函数

2. `where`和`having`的区别
   1. `where`在分组之前进行限定，如果不满足条件，则不参与分组
   2. `having`在分组之后进行限定，如果不满足条件，则不会被查询出来
   3. `where`后不可以跟聚合函数，而having可以进行聚合函数的判断

```mysql
-- 按照性比分组，分别查询男、女同学的平均分、最高分和最低分
select sex,avg(math),max(math),min(math) from student group by sex;
-- 按照性别分组，分别查询男、女同学的平均分，分数低于70的人不参与分组
select sex,avg(math) from student where math > 70 group by sex;
-- 按照性别分组，分别查询男、女同学的平均分，分数低于70的人不参与分组，分组之后人数要大于2个人
select sex,avg(math) from student where math > 70 group by sex having count(id)>2;
select sex,avg(math) 人数 from student where math > 70 group by sex having 人数 > 2;

```

## 分页查询

语法：`limit 开始的索引, 每页查询的条数;`

公式：开始的索引 = (当前的页码 - 1) * 每页显示的条数

```mysql
-- 每页显示三条记录
select * from student limit 0,3; -- 第1页
select * from student limit 3,3; -- 第2页
select * from student limit 6,3; -- 第3页
```

***`limit`语法是MySQL的方言 ***

# 约束

## 概念

对表中的数据进行限定，从而保证数据的正确性、有效性和完整性

## 分类

### 主键约束 - primary key

1.  注意：

    1.  含义：非空且唯一
    2.  一张表只能有一个字段为主键
    3.  主键就是一张表表中记录的唯一标识

2.  在创建表时，添加主键约束

    ```mysql
    create table stu(
    	id int primary key, -- 给id添加主键约束
    	name varchar(20)
    );
    ```

3.  创建表后，添加主键

    `alter table stu modify id int primary key;`

4.  删除主键

    ```mysql
    -- 删除主键
    alter table stu drop primary key;
    ```

5.  自动增长：

    1.  概念：如果某一列是数值类型的，使用`auto_increment`可以完成值的自动增长

    2.  在创建表的时候，添加主键约束，并且完成主键自增长

        ```mysql
        create table stu(
        	id int primary key auto_increment, -- 给id添加主键约束
            name varchar(20)
        );
        ```

    3.  ```mysql
        -- 删除自动增长
        alter table stu modify id int;
        -- 添加自动增长
        alter table stu modify id int auto_increment;
        ```

6.  重置主键

    ```mysql
    ALTER table table_ AUTO_INCREMENT 1;
    ```

    

### 非空约束 - not null

1. 在创建表时，添加约束

   `name varchar(20) not null`

   ```mysql
   create table stu(
   	id int,
       name varchar(20) not null -- name非空
   );
   ```

   ​	

2. 创建表之后，添加非空约束

   `alter name varchar(20) not null;`

### 唯一约束 - unique

某一列的值不能重复

1. 在创建表时添加唯一约束

   ```mysql
   create table stu(
   	id int,
       phone_number varchar(20) unique -- 手机号
   );
   ```

2. 在创建表之后添加唯一约束

   ```MySQL
   alter table stu modify phone_number varchar(20) unique;
   ```




注意：

1. 唯一约束可以有null，但是只能有一条记录为null
2. 当表中有重复记录的时候，无法添加唯一约束
3. 删除唯一约束：`alter table stu drop index phone_number;`

### 外键约束 - foreign key

让表与表产生关系，从而保证数据的正确性

```mysql
-- 原始写法
create table emp(
	id int primary key auto_increment,
    name varchar(30),
    age int,
    dep_name varchar(30), -- 部门名称
    dep_location varchar(30) -- 部门地址
);

-- add data
insert into emp(name,age,dep_name,dep_location) values('张三',20,'研发部','广州');
insert into emp(name,age,dep_name,dep_location) values('李四',21,'研发部','广州');
insert into emp(name,age,dep_name,dep_location) values('王五',20,'研发部','广州');

insert into emp(name,age,dep_name,dep_location) values('老王',20,'销售部','深圳');
insert into emp(name,age,dep_name,dep_location) values('小王',22,'销售部','深圳');
insert into emp(name,age,dep_name,dep_location) values('大王',18,'销售部','深圳');
```

```mysql
-- 解决方案：分成2张表
-- 创建部门表(id,dep_name,dep_location)
-- 一方，主表
create table department(
	id int primary key auto_increment,
    dep_name varchar(20),
    dep_location varchar(20)
);

-- 创建员工表(id,name,age,dep_id)
-- 多方，从表
create table employee(
	id int primary key auto_increment,
    name varchar(20),
    age int,
    dep_id int,
    constraint emp_dept_fk foreign key (dep_id) references department(id)
);

-- 添加两个部门
insert into department values(null,'研发部','广州'),(null,'销售部','深圳');
select * from department;

-- 添加员工,dep_id表示员工所在的部门
insert into employee (name,age,dep_id) values('张三',20,1);
insert into employee (name,age,dep_id) values('李四',21,1);
insert into employee (name,age,dep_id) values('王五',20,1);

insert into employee (name,age,dep_id) values('老王',21,2);
insert into employee (name,age,dep_id) values('大王',22,2);
insert into employee (name,age,dep_id) values('小王',18,2);

select * from employee;
```



1.  在创建表时，可以添加外键

2.  语法

    ```mysql
    create table 表名(
    	...
    	外键列
        constraint 外键名称 foreign key (外键列名称) references 主表名称（主表列名称）
    );
    ```

3.  删除外键

    `alter table 表名称 drop foreign key 外键名称;`

4.  在创建表之后添加外键

    `alter table 表名称 add constraint 外键名称 foreign key (外键字段名称) references 主表 (主表列名称);`

5.  级联操作

    1.  添加级联的操作

        语法

        ```MySQL
        alter table employee 
        	add constraint 	emp_dept_fk 
            foreign key (dep_id) 
            references department(id) 
            on update cascade
            on delete cascade;
        ```

    2.  分类

        1.  级联更新

            `on update cascade`

        2.  级联删除

            `on delete cascade`

    
# 数据库的设计

## 多表之间的关系

1. 分类
   1. 一对一（了解）

      e.g. 人和身份证

      分析：一个人只有一个身份证，一个身份证只能对应一个人

   2. 一对多（多对一）

      e.g. 部门和员工

      分析：一个部门有多个员工，一个员工只能对应一个部门

   3. 多对多

      e.g. 学生和课程

      分析：一个学生可以选择很多门课程，一个课程也可以被很多学生选择
      
      实现方式： 多对多关系需要借助第三张中间表。中间表至少包含两个字段，两个字段分别作为第三张表的外键，分别指向两张表的主键
   
2. 实现关系

   1. 一对多（多对一）

       e.g. 部门和员工

       实现方式：在“多”的一方建立外键，指向“一”的一方的主键

       实现方式：一对一关系实现，恶意在任意一方添加唯一外键指向另一方的主键
       
        



***案例***

 

```mysql
-- 创建旅游路线分类表
-- cid 旅游线路分类主键，自动增长
-- cname 旅游线路分类名称非空，唯一，字符串100
create table tab_category(
	cid int primary key auto_increment,
    cname varchar(100) not null unique
);

-- 创建旅游线路表
/*
rid 旅游线路主键，自动增长
rname 旅游线路名称 非空，唯一，字符串100
price 价格
rdate 上架时间，日期类型
cid 外键，所属分类 
*/
create table tab_rout(
	rid int primary key auto_increment,
    rname varchar(100) not null unique,
    price double,
    rdate date,
    cid int,
    foreign key (cid) references tab_category(cid)
);

-- 创建用户表
/*
uid 用户主键，自增长
username 用户名长度 100，唯一，非空
password 密码长度 30，非空
name 真实姓名长度 100
birthday 生日
sex 性别，定长字符串 11
email 邮箱，字符串 长度100
*/
create table tab_user(
	uid int primary key auto_increment,
    username varchar(100) not null unique,
    password varchar(30) not null,
    name varchar(100),
    birthday date,
    sex char(1) default "男",
    telephone varchar(11),
    email varchar(100)
);

/*
创建收藏表 tab_favorite
rid 旅游线路id，外键
date 收藏时间
uid 用户 id，外键
rid和uid不能重复，设置复合主键，同一个用户不能收藏同一个线路两次
*/
create table tab_favorite(
	rid int,
    date datetime,
    uid int,
    -- 创建复合主键
    primary key(rid,uid),
    foreign key (rid) references tab_rout(rid),
    foreign key (uid) references tab_user(uid)
);
```

<img src="MySQL自学图片/旅游路线案例.png" alt="旅游路线案例" style="zoom:150%;" />

## 数据库设计的范式 

概念

设计数据库时，需要遵循的一些规范。要遵循后边的范式要求，必须先遵循前边的所有范式要求。

分类

1. 第一范式（1NF）<a name="第一范式"></a>

   - 每一列都是不可分割的原子数据项

2. 第二范式（2NF）<a name="第二范式"></a>

   - 在[第一范式](#第一范式)的基础上，非码属性必须完全依赖于候选码（在1NF基础上消除非主属性对主码的部分函数依赖）

   - 几个概念

     1. 函数依赖：A - - > B,如果通过A属性（属性组）的值，可以确定唯一B属性的值。则称B依赖于A

        ​	例如：学号 - - > 姓名 / （学号，课程名称） - - > 分数

     2. 完全函数依赖：A - - > B , 如果A是一个属性组，则B属性值的确定需要依赖于A属性组中所有的属性值

        ​	例如：（学号，课程名称） - - > 分数

     3. 部分函数依赖：A - - > B，如果A是一个属性组，则B属性的确定只需要依赖A属性组中的某一些值即可

        ​	例如：（学号，课程名称） - - > 姓名

     4. 传递函数依赖：A - - > B，B - - > C，如果通过A属性（属性组）的值，可以确定唯一B属性的值，在通过B属性（属性组）的值可以确定唯一的C属性的值，则称 C 传递函数依赖于A

        ​	例如：学号 - - > 姓名，姓名 - - > 系主任

     5. 码：如果在一张表中，一个属性或属性组被其他所有属性所完全依赖，则称这个属性（属性组）为该表的码

        - 例如：在该表中，码为（学号，课程名称）
        - 主属性：码属性组中的所有属性
        - 非主属性：除主属性意外的属性

        

3. 第三范式（3NF）

   - 在[第二范式](#第二范式)的基础上，任何非主属性不依赖于其它非主属性（在2NF基础上消除传递依赖）



**无范式**

![范式分析 - 无范式](MySQL自学图片/范式分析 - 无范式.png)

问题：系下包括了“系名”和“系主任”，不满足[第一范式](#第一范式)的要求

**第一范式**

![范式分析 - 第一范式](MySQL自学图片/范式分析 - 第一范式.png)

存在的问题：

1. 存在严重的数据冗余（数据重复）：姓名、系名、系主任
2. 数据添加存在问题：添加新开设的系和系主任时，数据不合法
3. 数据删除存在问题：学生毕业，删除学生数据会导致系和系主任被删除



**第二范式**

![范式分析 - 第二范式](MySQL自学图片/范式分析 - 第二范式.png)

存在的问题：

1. 数据添加存在问题：添加新开设的系和系主任时，数据不合法
2. 数据删除存在问题：学生毕业，删除学生数据会导致系和系主任被删除

**第三范式**

![范式分析 - 第三范式](MySQL自学图片/范式分析 - 第三范式.png)

# 数据库的备份与还原

## 命令行

语法：

-   备份`mysqldump -u用户名 -p密码 数据库名称 > 保存路径`
-   还原
    1.  登录数据库
    2.  创建数据库
    3.  使用数据库
    4.  执行文件 `source 文件路径`

## 图形化工具

# 多表查询

查询的语法

```mysql
select
	列名列表
from
	表名列表
where
	....
```

准备sql

```mysql
#创建部门表
create table dept(
	id int primary key auto_increment,
    name varchar(20)
);
insert into dept (name) values ("开发部"),("市场部"),("财务部");

#创建员工表
create table emp(
	id int primary key auto_increment,
    name varchar(10),
    gender char(1),
    salary double,
    join_date date,
    dept_id int,
    foreign key (dept_id) references dept(id)
);
insert into emp(name,gender,salary,join_date,dept_id) values("孙悟空","男",7200,"2013-02-24",1);
insert into emp(name,gender,salary,join_date,dept_id) values("猪八戒","男",3600,"2010-12-02",2);
insert into emp(name,gender,salary,join_date,dept_id) values("唐僧","男",9000,"2008-08-08",2);
insert into emp(name,gender,salary,join_date,dept_id) values("白骨精","女",5000,"2015-10-07",3);
insert into emp(name,gender,salary,join_date,dept_id) values("蜘蛛精","女",4500,"2011-03-14",1);
```

`select * from emp,dept; -- 笛卡尔积（A集合和B集合的所有组合）`

![image-20211001135444073](E:\Desktop\MySQL自学图片\笛卡尔积)



## 内连接查询

### 隐式内连接

使用`where`来消除无用的数据

```mysql
-- 查询所有员工信息和对应的部门信息
select * from emp,dept where emp.dept_id = dept.id;

-- 查询员工表的名称，性别，部门表的名称
select emp.name,emp.gender,dept.name from emp,dept where emp.dept_id = dept.id;
#或采用取别名的方式
select 
	t1.name,t1.gender,t2.name
from
	emp t1,dept t2
where
	t1.dept_id = t2.id;
```

### 显式内连接

语法：`select 字段列表 from 表名1 inner join 表名2 on 条件`

```mysql
select 
	* 
from 
	emp
inner join -- inner 可选
	dept 
on 
	emp.dept_id  = dept.id;
```

### 注意事项

1.  从哪些表中查询数据
2.  查询条件是什么
3.  查询哪些字段

## 外连接查询

### 左外连接

-   语法：`select 字段列表 from 表1 left [outer] join 表2 on 条件`
-   查询的是左表所有数据以及其交集部分

### 右外连接

-   语法：`select 字段列表 from 表1 right [outer] join 表2 on 条件`
-   查询的是右表所有数据以及其交集部分

## 子查询

-   概念：查询中嵌套查询，呈嵌套查询为子查询

-   ```MySQL
    -- 查询工资最高的员工信息
    -- 1.查询最高的工资是多少
    select max(salary) from emp;
    -- 2.查询员工信息，并且工资等于9000的
    select * from emp where emp.salary = 9000;
    
    -- 一条SQL完成操作
    select 
    	* 
    from 
    	emp 
    where 
    	emp.salary = (select max(salary) from emp);
    ```

    

**子查询的不同情况**

1.  子查询的结果是单行单列的

    -   子查询可以作为条件，是用运算符去判断

    -   ```MySQL
        -- 查询员工的工资小于平均工资的人
        select 
        	*
        from
        	emp
        where
        	emp.salary < (select avg(salary) from emp);
        ```

        

2.  子查询的结果是多行单列的

    -   子查询可以作为条件，使用运算符`in`来判断

    ```MySQL
    -- 查询财务部和市场部所有的员工信息
    select id from dept where name = '财务部' or name = "市场部";
    select * from emp where dept_id = 3 or dept_id =2;
    
    -- 在一句SQL中完成
    select 
    	*
    from 
    	emp
    where 
    	dept_id 
    in(
    	select 
    		id 
    	from 
    		dept
    	where
    		name = "财务部" or name = "市场部"
    	);
    ```

    

3.  子查询的结果是多行多列的

    子查询可以作为虚拟表

    ```MySQL
    -- 查询员工的入职日期是2011-11-11之后的员工信息和部门信息
    select 
    	* 
    from
    	dept t1,
        (select 
    		*
    	from
    		emp
    	where
    		emp.join_date > "2011-11-11") t2
    where t1.id = t2.dept_id;
    ```

    ```MySQL
    #普通内连接
    select 
    	*
    from
    	emp t1,dept t2 
    where 
    	t1.dept_id = t2.id and t1.join_date>"2011-11-11";
    
    ```

    

## 练习

```MySQL
-- 部门表
create table dept(
	id int primary key,
    dname varchar(50), -- 部门名称
    loc varchar(50) -- 部门所在地
);

-- 添加四个部门
insert into dept(id,dname,loc) values
(10,"教研部","北京"),
(20,"学工部","上海"),
(30,"销售部","广州"),
(40,"财务部","深圳");

-- 职务表，职务名称，职务描述
create table job(
	id int primary key,
    jname varchar(20),
    description varchar(50)
);

-- 添加4个职务
insert into job(id,jname,description) values
(1,"董事长","管理整个公司，接单"),
(2,"经理","管理部门员工"),
(3,"销售员","向客人推销产品"),
(4,"文员","使用办公软件");

-- 员工表
create table emp(
	id int primary key, -- 员工id
    ename varchar(60), -- 员工姓名
    job_id int, -- 职务id
    mgr int, -- 上级领导
    joindate date, -- 入职日期
    salary decimal(7,2), -- 工资
    bonus decimal(7,2), -- 奖金
    dept_id int, -- 所在部门编号
    constraint emp_jobid_ref_job_id_fk foreign key (job_id) references job(id),
    constraint emp_deptid_ref_dept_id_fk foreign key (dept_id) references dept(id)
);

-- 添加员工
insert into emp(id,ename,job_id,mgr,joindate,salary,bonus,dept_id) values
(1001,"孙悟空",4,1004,"2000-12-17","8000.00",null,20),
(1002,"卢俊义",3,1006,"2001-02-20","16000.00","3000.00",30),
(1003,"林冲",3,1006,"2001-02-22","12500.00","5000.00",30),
(1004,"唐僧",2,1009,"2001-04-02","29750.00",null,20),
(1005,"李逵",4,1006,"2001-09-28","12500.00","14000.00",30),
(1006,"宋江",2,1009,"2001-05-01","28500.00",null,20),
(1007,"刘备",2,1006,"2001-09-01","24500.00",null,10),
(1008,"猪八戒",4,1004,"2007-04-19","30000.00",null,20),
(1009,"罗贯中",1,null,"2001-11-17","50000.00",null,10),
(1010,"吴用",3,1006,"2001-09-08","15000.00","0.00",30),
(1011,"沙僧",4,1004,"2007-05-23","11000.00",null,20),
(1012,"李逵",4,1006,"2001-12-03","9500.00",null,30),
(1013,"小白龙",4,1004,"2001-12-03","30000.00",null,20),
(1014,"关羽",4,1002,"2002-01-23","13000.00",null,10);

-- 工资等级表
create table salarygrade(
	grade int primary key, -- 级别
    losalary int, -- 最低工资
    hisalary int -- 最高工资
);

-- 添加5个工资等级
insert into salarygrade(grade,losalary,hisalary) values
(1,7000,12000),
(2,12010,14000),
(3,14010,20000),
(4,20010,30000),
(5,30010,99990);

/*
需求：
1.查询所有员工信息。查询员工编号，员工姓名，工资，职务名称，职务描述
2.查询员工编号，员工姓名，工资，职务名称，职务描述，部门名称，部门位置
3.查询员工姓名，工资，工资等级
4.查询员工姓名，工资，职务名称，职务描述，部门名称，部门位置，工资等级
5.查询部门编号、部门名称、部门未知、部门人数
6.查询所有员工的姓名极其直接上级的姓名，没有领导的员工也要查询
*/

-- 1.查询所有员工信息。查询员工编号，员工姓名，工资，职务名称，职务描述
/*
分析：
	1.员工编号，员工姓名，工资需要查询emp表；职务名称，职务描述需要查询job表
    2.查询条件:emp.job_id = job.id
*/
select
	t1.id,	-- 	员工编号
    t1.ename, -- 员工姓名
    t1.salary, -- 员工工资
    t2.jname, -- 职务名称
    t2.description -- 职务描述
from
	emp t1,
    job t2
where
	t1.job_id = t2.id;
    
-- 2.查询员工编号，员工姓名，工资，职务名称，职务描述，部门名称，部门位置
/*
分析：
	1.员工编号，员工姓名，工资需要查询emp表；
		职务名称，职务描述需要查询job表；
        部门位置，部门名称需要查询dept表
	2.条件：
		emp.job_id = job.id and emp.dept_id = dept.id
*/
select
	t1.id,
    t1.ename,
    t1.salary,
    t2.jname,
    t2.description,
    t3.dname, -- 部门名称
    t3.loc -- 部门位置
from
	emp t1,
    job t2,
    dept t3
where
	t1.job_id = t2.id and
    t1.dept_id = t3.id;
    
-- 3.查询员工姓名，工资，工资等级
/*
	分析：
		1.员工姓名，工资 emp
			工资等级 salarygrade
		2.条件
			emp.salary >= salarygrade.losalary and
			emp.salary <= salarygrade.hisalary
            
            emp.salary between salarygrade.losalary and salarygrade.hisalary
*/
SELECT
	t1.ename,
    t1.salary,
    t2.grade
FROM
	emp t1,
    salarygrade t2
where
	t1.salary BETWEEN t2.losalary and t2.hisalary;
    
use try;

-- 4.查询员工姓名，工资，职务名称，职务描述，部门名称，部门位置，工资等级
/*
	分析：
		1.员工姓名，工资 emp
			职务名称，职务描述 job
			部门名称，部门位置 dept
            工资等级 salarygrade
		2.条件
			
*/
select 
	t1.ename,
    t1.salary,
    t2.jname,
    t2.description,
    t3.dname,
    t3.loc,
    t4.grade
from 
	emp t1,
	job t2,
	dept t3,
    salarygrade t4
where
	t1.job_id = t2.id and
    t1.dept_id = t3.id and
    t1.salary between t4.losalary and t4.hisalary;

-- 5.查询部门编号、部门名称、部门位置、部门人数
/*
	分析：
		1. 部门编号、部门名称、部门位置 dept表
			部门人数 emp表
		2.使用分组查询，按照emp.dept_id完成分组，查询count(id)
        3.使用子查询将第二部的查询结果和dept表进行关联查询
*/
select
	t1.id,
    t1.dname,
    t1.loc,
    t2.total
from
	dept t1,
    (select
			dept_id,count(id) total
	from 
			emp
	group by 
			dept_id) t2
where
	t1.id = t2.dept_id

-- 6.查询所有员工的姓名极其直接上街的姓名，没有领导的员工也需要查询
/*
	分析：
		1.姓名 emp，直接上级的姓名 emp
			* emp 表的id和mgr是自关联
		2.条件
			emp.id = emp.mgr
		3.查询坐标的所有数据，和“交集数据“
			*使用左外连接查询
*/
select
	t1.ename,
    t1.mgr,
    t2.id,
    t2.ename
from
	emp t1
left join
	emp t2
on
	t1.mgr = t2.id
```



# 事务

## 事务的基本介绍

1.  概念

    如果一个包含多个步骤的业务操作，被事务管理，那么这些操作要么同时成功，要么同时失败

2.  操作

    1.  开启事务：`start transaction;`
    2.  回滚：`rollback;`
    3.  提交：`commit`

```mysql
create table account(
	id int primary key auto_increment,
    name varchar(10),
    balance double
);
-- 添加数据
insert into account (name,balance) values("zhangsan",1000),("lisi",1000);

-- 张三给李四转账500元
-- 0. 开启事务
start transaction;
-- 1. 张三账户 -500
update account set balance = balance - 500 where name = "zhangsan";
-- 2. 李四账户 +500
------------(异常)--------------
update account set balance = balance + 500 where name = "lisi";
-- 未发现问题，提交事务
commit;
-- 发现问题，回滚事务
rollback;

```

3.   MySQL数据库中事务默认自动提交

     -   一条DML（增删改查）语句会自动提交一次事务

     -   事务提交的两种方式

         -   自动提交
             -   MySQL自动提交，一条DML语句提交一次
         -   手动提交
             -   Oracle 数据库默认是手动提交事务
             -   需要先开启事务，再提交

     -   修改事务的默认提交方式

         -   查看事务的默认提交方式

             ```mysql
             select @@autocommit; -- 1代表自动提交，0代表手动提交
             ```

         -   修改默认提交方式

             ```mysql
             set @@autocommit = 0;
             ```



## 事务的四大特征

1.  原子性：不可分割的最小操作单位，要么同时成功，要么同时失败
2.  持久性：如果事务一旦提交或是回滚，数据库会持久化的保存数据
3.  隔离性：多个事务之间相互独立
4.  一致性：事务操作前后，数据总量不变



## 事务的隔离级别（了解）

1.  概念

    多个事务之间是隔离的，相互独立。但是如果多个事务操作同一批数据，则会引发一些问题，设置不同的隔离级别就可以解决这些问题

2.  存在问题

    1.  脏读

        一个事务，读取到另一个事务中咩有提交的数据

    2.  不可重复读（虚度）

        在同一个事务中，两次读取到的数据不一样

    3.  幻读

        在一个事务操作（DML）数据表中所有记录，另一个事务添加了一条数据，则第一个事务查询不到自己的修改

3.  隔离级别

    1.  read uncommitted：读未提交

        -   会产生的问题：脏读、不可重复读、幻读

    2.  read committed：读已提交**（Oracle默认）**

        -   产生的问题：不可重复读、幻读

    3.  repeatable read：可重复读**（MySQL默认）**

        -   产生的问题：幻读

    4.  serializable：串行化

        -   可以解决所有的问题

    5.  **注意**：隔离级别从小到大安全性越来越高，但是效率越来越低

    6.  数据库查询隔离级别

        `select @@transaction_isolation;`

    7.  数据库设置隔离级别

        `set global transaction isolation level 级别字符串;`



# DCL<a name = 'DCL_detailed'></a>

## DBA：数据库管理员

## 管理用户

1. 添加用户

   ```mysql
   CREATE USER '用户名' @ '主机名' IDENTIFIED BY '密码';
   #主机名
   /*
   local host:本地
   %：所有主机
   */
   ```

   

2. 删除用户

   ```MySQL
   DROP USER '用户名' @ '主机名';
   ```

   

3. 修改用户密码

   ```mysql
   -- 修改用户的密码
   UPDATE USER SET PASSWORD = PASSWORD('new password') WHERE USER = '用户名';
   -- 或
   SET PASSWORD FOR '用户名' @ '主机名' = PASSWORD('新密码');
   
   ```

   - **在MySQL中忘记了用户密码**
     1. `cmd -> net stop mysql`	通过DOS停止MySQL服务，需要管理员权限
     2. 使用无验证方式启动MySQL服务：`mysqld --skip-grat-tables`
     3. 打开新的cmd窗口，直接输入mysql命令，敲回车，就可以登录成功
     4. `use mysql;`
     5. `update user set password = password('新密码') where user = 'root';`
     6. 关闭两个窗口
     7. 打开任务管理器，手动结束mysqld.exe的进程
     8. 启动MySQL服务
     9. 使用新密码登录

   

4. 查询用户

   ```MySQL
   -- 1.切换到mysql数据库
   USE mysql;
   -- 2.切换到user表
   SELECT * FROM USER;
   ```

   - 通配符：`%`表示可以在任意主机使用用户登录数据库



## 权限管理

1. 查询权限

   ```mysql
   -- 查询权限
   SHOW GRANTS FOR '用户名' @ '主机名';
   ```

   

2. 授予权限

   ```MySQL
   -- 授予权限
   GRANT 权限列表 ON 数据库.表名 TO '用户名' @ '主机名';
   
   /*
   SELECT	选择权限
   UPDATE	更新权限
   DELETE	删除权限
   */
   -- 给一个用户授予在任意数据库的任意表全部权限
   GRANT ALL ON * * TO '用户名' @ '主机名';
   ```

   

3. 撤销权限

   ```MySQL
   -- 撤销权限
   REVOKE 权限列表 ON 数据库名.表名 FROM '用户名' @ '主机名';
   ```

   



