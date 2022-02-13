# 第三章	Java的基本程序设计结构

## 3.1	print/println/println

```java
System.out.println("输出并换行");
System.out.print("输出但是并不换行");
System.out.printf("与C相同");
```

## 3.2	注释

```java
//-----1-----
//单行注释
//-----2-----
/*
多行注释
*/
//-----3-----
/**
输出到文件的注释
*/
```

## 3.3	数据类型

### 3.3.1	整型

*在Java中，整型的范围与运行Java代码的机器无关*

如何用printf输出byte，short，long？

| 数据类型 | 占用字节 |
| -------- | -------- |
| byte     | 1        |
| short    | 2        |
| dint     | 4        |
| long     | 8        |

#### 前、后缀

### 3.3.2	浮点类型

| 数据类型 | 占用字节 |
| -------- | -------- |
| float    | 4        |
| double   | 8        |

#### 特殊浮点值

| 特殊数值 | 常量                     |
| -------- | ------------------------ |
| 正无穷大 | Double.POSITIVE_INFINITY |
| 负无穷大 | Double.NEGATIVE_INFINITY |
| NaN      | Double.NaN               |

### 3.3.3	char类型

\u的转换顺序在编译之前？

### 3.3.4	Unicode和char类型

### 3.3.5	boolean类型

在Java中，0是0，false是false

## 3.4	变量

判断一个字符是不是Java中的“字母：Character.isJavaIdentifierStart() / Character.isJavaIdentifierPart()

### 3.4.1 	变量初始化

变量声明尽量靠近变量第一次使用的地方

### 3.4.2	常量——final

常量只能被赋值一次，一旦赋值，不能再修改。**习惯上，常量名使用全大写**

在Java中，经常希望某个常量可以在一个类中的多个方法中使用，通常将这些常量成为类常量。**使用关键字static final设置一个类常量**

```java
public class Constants2
{
    public static final double CM_PER_INCH = 2.54;
    
    public static void main(String[] args)
    {
        double paperwidth= 8.5;
        //………………………………………………
    }
}
```

## 3.5	运算符

**整数被0除会产生一个异常，而浮点数被0除将会得到无穷大或NaN的结果**

### 3.5.1	数学函数与常量——Math

```java
//不必在数学方法名和常量名之前添加前缀“Math”
import static java.lang.Math.*;
System.out.println("The square root of \u03C0 is "+squre(PI));
```

#### floorMod(a,b)

当b>0:	无论a符号如何，最后的结果都是正

当b<0:	最后结果为负数

### 3.5.2	数值类型切换

![3.5.2 数值类型切换](E:\刘元\学校\大学\大二\Java核心技术卷 - I 基础知识\3.5.2 数值类型切换.png)

### 3.5.3	强制类型转换

```java
//强制类型转换
{
    double x=9.997;
	int nx=(int)x;
}
//获得最接近的整数
{
    double x=9.997;
    int nx=(int)Math.round(x);
}
```

#### 警告

##### 1、如果源数据大小超过了目标数据类型的大小，结果就会截断成为完全不同的值

##### 2、尽量不要对boolean型数据进行转换

```java
boolean b=false;
int x=b?1:0;
```

### 3.5.4	结合赋值与运算符

如果运算符得到的值与被赋值变量数据类型不同，则会强制转换

```java
int x=2;
double y=3.5;
x+=y;
System.out.print(x);	//结果：5
```

### 3.5.5	自增与自减运算符

**建议不要在表达式中使用，很容易引起困惑和bug**

### 3.5.6	关系和boolean运算符

***警告***

如果 == 比较的是对象，那么比较的是是否引用同一片空间（比较地址）

### 3.5.7	位运算符

### 3.5.8	括号与运算符级别

### 3.5.9	枚举类型

见第5章

## 3.6	字符串

### 3.6.1	子串

```java
String greeting="Hello!";
String s=greeting.substring(0,3);	//"Hel"
```

这样做有一个好处，那就是3-0=3，恰好就是新的字符串的长度

### 3.6.2	拼接

可以使用加号直接拼接

```java
String expletive="expletive";
String PG13="deleted";
String message=expletive+PG13;	//"expletivedeleted"
```

当一个非字符串的值与字符串相拼接，这个值会转换为字符串（**任何一个java对象都可以转换为字符串**）



将多个字符串放在一起，并且用分界符隔开：

```java
String all=String.join("/","a","b","c","d");	//"a/b/c/d"
```

### 3.6.3	不可变字符串

java中的字符串不可修改，但是可以通过现有的字符串进行操作

```java
String greeting="Hello!";
greeting=greeting.substring(0,3)+"p!";		//"Help!"
```

不变字符串：**String本质上是一种指针，而不是一个变量。**也就是说，如果多个String的内容是"Hello!",那么本质上他们指向同一个地址。

## 3.7	输入输出

### 3.7.1	读取输入

```java
import java.util.*;

public class InputTest
{
    public static void main(String[] arg)
    {
        //创建新的Scanner对象，并且将其与“标准输入流”System.in关联
        Scanner in=new Scanner(System.in);

        //first line
        System.out.println("Hello! What's your name?");
        String name=in.nextLine();

        //second line
        System.out.println("How old are you?");
        int age=in.nextInt();

        //display
        System.out.print("name:"+name+" age:"+age);
    }
}
```

### 3.7.2	格式化输出

### 3.7.3	文件输入与输出

==如果文件名中包含反斜杠，就要打两个：c:\\\mydirectory\\\myfile.txt==

```java
import java.util.*;

Scannet in = new Scanner(Paths.get("myfile.txt"),"UTF-8");
```

**写入文件**

```java
PrintWriter out = new PrintWriter("myfile.txt","UTF-8");
```

## 3.8	控制流程

### 3.8.1	块作用域

**java中不允许在嵌套的块中声明同名的变量**

### 3.8.2	条件语句——if

### 3.8.3	循环语句——while

程序清单3-3——while

程序清单3-4——do-while

### 3.8.4	确定循环——for

***增强for循环的弊端***

==对于基本类型与String类型，增强for循环无法修改值==

### 3.8.5	多重选择——switch

**cace 的内容可以是char,byte,int,String**

### 3.8.6	中断控制流程语句

**带标签的break语句**

```java
read_data:
while(true)
{
	for(;;)
    {
        while(true)
        {
            break read_data;
        }
    }
}
System.out.println("从第八行跳转到12");
```

## 3.9	大数值

```java
//任意精度整型
BigInteger a = BigInteger.valueOf(100);	//利用静态方法将普通数值转化为大数值
//任意精度浮点型
BigDecimal b = BigDecimal.valueOf(3.1415926);
```

**不能使用人们熟悉的算术运算符处理大数值，需要使用大数值类中的add和multiply方法**

```java
BigInteger d = c.multiply(b.add(BigInteger.valueOf(2)));	//d=c*(b+2)
```

## 3.10	数组

**1、数组定义：**

```java
int[] a=new int[100];
len=a.lenth;	//长度
```

**2、性质**

1）数组长度不要求是常量，new int[n]会创建一个长度为n的数组

2）创建一个数组时，所有元素都初始化为0。Boolean数组的元素会初始化为false，对象数组的元素则初始化为特殊值null

3）一旦创建了数组，就不能在改变它的大小

### 3.10.1	for each 循环——一次处理数组中的每个元素

***警告***

for each循环采用的是值传递，而不是引用传递，因此对于基本类型和String类型类数据无法进行修改

**语句格式：**

```java
//	for(variable:collection) statement //——>变量将会遍历数组中的每个元素，而不需要使用下标
int[] a=new int[100];
for(int element:a)		//for each element in a
{
    System.out.println(element);
}
```

****

**提示：**打印数组中的所有值

```java
System.out.println(Arrays.toString(a));	// [2,3,5,7,11,13]
```

### 3.10.2	数组初始化以及匿名数组

**1、创建数组对象并同时赋初值——不需要new**

```java
int[] smallPrime={2,3,5,7,11,13};
```

**2、初始化匿名数组——在不创建新变量的情况下重新初始化一个数组**

```java
smallPrime=new[] int {17,19,23,29,31,37}；
```

### 3.10.3	数组拷贝

**1、在java中，允许将一个数组变量拷贝给另一个数组变量。这时，两个变量将引用同一个数组：**

```java
int[] smallPrime={2,3,5,7,11,13};
int[] luckyNumbers = smallPrimes;
luckyNumbers[5]=12;		//now smallPrimes[5] is also 12
```

**2、将一个数组的所有值拷贝到另外一个数组去：**

如果数组元素是数值型，那么多余的元素将被赋值0；如果数组元素是布尔型，则将赋值为false。相反，如果长度小于原始数组长度，则只拷贝最前面的数组元素。

```java
int[] copiedLuckyNumbers = Arrays.copyOf(luckyNumbers,luckyNumbers.lenth);
```

### 3.10.4	命令行参数

### 3.10.5	数组排序——Arrays.sort(a)

### 3.10.6	多维数组

**声明：**

```java
double[][] balance=new double[][];
balance=new[][] double{....};
balance=
	{
    	{1,2,3}
         {4,5,6}
         {7,8,9}
	};
```

**提示：**

```java
double a=new double[5][6];
a.length=5;			//行数
a[0].length=6;		//列数
```

**快速打印：Arrays.deepToString()**

### 3.10.7	不规则数组

java其实并没有二维数组，只有数组嵌套。——>java数组给人的感觉更像是指针

**比较：同一个操作在不同语言下的实现**

java:

```java
double[][] balances = new double[10][6];
```

C++:

```c++
double** balances=new double*[10];
for(int i=0;i<10;i++)
{
	balances[i]=new double[6];
}
```

**重要程序：**

```java
import java.util.Arrays;

public class LotteryArray
{
    public static void main(String[] arg)
    {
        final int MAX=10;
        int[][] a=new int[MAX][];
        for(int i=0;i<MAX;i++)
        {
            a[i]=new int[i+1];
        }
        for(int i=0;i<MAX;i++)
        {
            for(int j=0;j<a[i].length;j++)
            {
                a[i][j]=j;
            }
        }
        for(int i=0;i<MAX;i++)
        {
            System.out.println(Arrays.toString(a[i]));
        }
    }
}
//output:
/*
[0]
[0, 1]
[0, 1, 2]
[0, 1, 2, 3]
[0, 1, 2, 3, 4]
[0, 1, 2, 3, 4, 5]
[0, 1, 2, 3, 4, 5, 6]
[0, 1, 2, 3, 4, 5, 6, 7]
[0, 1, 2, 3, 4, 5, 6, 7, 8]
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
*/
```

