# 第六章	接口、lambda表达式与内部类

## 6.1	接口(interface)

### 6.1.1	接口概念

在java程序设计语言中，接口不是类，而是对类的一组需求描述，这些类要遵从接口描述的统一格式进行定义。

***重要程序***

***Employee***

```java
package interfaces;
/*
	Array.sort()要求对象要是可比较的(Comparable)，同时要求有compareTo方法
	称Comparable为一个接口
	为了实现接口，需要使用关键字implements
*/
public class Employee implements Comparable<Employee>
{
    private String name;
    private double salary;

    public Employee(String name,double salary)
    {
        this.name=name;
        this.salary=salary;
    }

    public String getName()
    {
        return name;
    }

    public double getSalary()
    {
        return salary;
    }

    public void raiseSalary(double byPercent)
    {
        salary+=salary*byPercent/100;
    }

    /**
     * Compares employees by salary
     * @param other another Employee object
     * @return a negative value if this employee has a lower salary than
     * otherObject, 0 if the salaries are the same, a positive value otherwise
     */
    public int compareTo(Employee other)
    {
        return Double.compare(salary,other.salary);
    }
}



```

***EmployeeSort***

```java
package interfaces;

import java.util.*;

public class EmployeeSort
{
    public static void main(String[] args)
    {
        Employee[] staff = new Employee[3];

        staff[0] = new Employee("Harry Hacker",35000);
        staff[1] = new Employee("Carl Cracker",75000);
        staff[2] = new Employee("Tony Tester",38000);

        Arrays.sort(staff);

        //print out information about all Employee objects
        for(Employee e:staff)
        {
            System.out.println("name="+e.getName()+"salary="+e.getSalary());
        }
    }
}

```

***注意***

如果子类之间的比较寒意不一样，那就属于不同类对象的非法比较。每个compareTo方法都应该在开始时进行下列检测：

```java
if(getClass()!=other.getClass())
{
    throw new ClassCastException();
}
```

如果存在一种通用算法，能够对不同的子类对象进行比较，则应该在超类中提供一个compareTo方法，并将这个方法声明为final。

### 6.1.2	接口的特性

1、接口中不能包含实例域或静态方法，但却可以包含常量

2、接口中的方法都自动被设为public，接口中的域都自动谁为public static final



尽管每个类只能拥有一个超类，但是可以实现多个接口。例如：

```java
class Employee implements Cloneable,Comparable
```

### 6.1.3	接口与抽象类

接口可以提供多重继承的大多数好书，同时还能避免多重继承的复杂性和低效性。

### 6.1.4	静态方法

Java SE 8中允许在接口中增加静态方法。因此在实现自己的接口时，不需要为实用工具方法另外提供一个伴随类。

### 6.1.5	默认方法

可以为接口方法提供一个默认实现。***default***修饰符

```java
public interface Comparable<T>
{
    default int compareTo(T other)
    {
        return 0;
    }
    //by default,all elements are the same
}
```

### 6.1.6	解决默认方法冲突

解决多次定义的二义性：

1）超类优先

2）接口冲突。如果一个超接口提供了一个默认方法，另一个接口提供了一个同名而且参数类型相同的方法，必须覆盖这个方法来解决冲突。

## 6.2	接口示例

### 6.2.1	接口与回调（callback）

*回调*指一种常见的程序设计模式。在这种模式中，可以指出某个特定时间发生时应该采取的动作。

***重要程序***

```java
package timer;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.Timer;

public class TimerTest
{
    public static void main(String[] args)
    {
        ActionListener listener = new TimePrinter();

        //construct a timer that calls the listener
        //once every 10 seconds
        Timer t = new Timer(10000,listener);    //设置定时器，每10000ms触发一次
        t.start();  //开始计时
        JOptionPane.showMessageDialog(null,"Quit program?");    //显示对话框
        System.exit(0);
    }
}

class TimePrinter implements ActionListener
{
    public void actionPerformed(ActionEvent event)
    {
        System.out.println("At the tone, the time is "+new Date());     //输出当前时间
        Toolkit.getDefaultToolkit().beep();     //发出蜂鸣
    }
}

```

### 6.2.2	comparator接口

***重要程序***

***StringComparator***

```java
package interfaces.comparator;

import java.util.*;

public class StringComparator implements Comparator<String>
{
    @Override
    public int compare(String first,String second)
    {
        return first.length()-second.length();
    }
}

```

***StringComparatorTest***

```java
package interfaces.comparator;

import java.util.*;

public class StringComparatorTest
{
    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);
        String string1 = in.nextLine();
        String string2 = in.nextLine();
        Comparator<String> comp = new StringComparator();
        if(comp.compare(string1,string2)>0)
        {
            String temp=string1;
            string1=string2;
            string2=temp;
        }
    }
}

```

### 6.2.3	对象克隆

***Cloneable***接口

通常的拷贝都是浅拷贝，但是如果涉及到了别的子类，并且这个子类是可变的（Date），那么就需要深拷贝（定义clone方法）

对于一个类，需要确定：

1. 默认的clone方法是否满足需求；
2. 是否可以在可变的子对象上调用clone来修补默认的clone方法
3. 是否不该使用clone

实际上第三个选项是默认选项。如果选择第一项或第二项，类必须：

1. 实现Cloneable接口
2. 重新定义clone方法，并制定public访问修饰符

***重要程序***

***Employee***

```java
package clone;

/*
为了表现深拷贝对可更改子类的重要性
使用的是Date而不是LocalDate
*/
import java.util.Date;
import java.util.GregorianCalendar;

public class Employee implements Cloneable
{
    private String name;
    private double salary;
    private Date hireDay;

    public Employee(String name,double salary)
    {
        this.name=name;
        this.salary=salary;
        this.hireDay=new Date();
    }

    //如果复制出现异常，那么就抛出异常CloneNotSupportedException
    public Employee clone() throws CloneNotSupportedException
    {
        //call Object.clone()
        //能够对基础数据类型和不可变子类进行克隆
        Employee cloned = (Employee) super.clone();

        //clone multable fields
        //需要对可变子类进行克隆
        cloned.hireDay = (Date) hireDay.clone();

        return cloned;
    }

    /**
     * Set the hire day to a given date
     * @param year the year of the hire day
     * @param month the month of the hire day
     * @param day the day of the hire day
     */
    public void setHireDay(int year,int month,int day)
    {
        Date newHireDay = new GregorianCalendar(year,month-1,day).getTime();
        //Example of instance field mutation
        hireDay.setTime(newHireDay.getTime());
    }

    public void raiseSalary(double byPercent)
    {
        salary+=salary*byPercent/100;
    }

    public String toString()
    {
        return "Employee[name="+name+",salary="+salary+",hireDay="+hireDay+"]";
    }
}

```

***CloneTest***

```java
package clone;

public class CloneTest
{
    public static void main(String[] args)
    {
        try
        {
            Employee original = new Employee("John Q. public",50000);
            original.setHireDay(2000,1,1);
            Employee copy = original.clone();
            copy.raiseSalary(10);
            copy.setHireDay(2002,12,31);
            System.out.println("original="+original);
            System.out.println("copy    ="+copy);
        }
        //如果抓到了异常CloneNotSupportedException，就在命令行中显示异常的位置
        catch (CloneNotSupportedException e)
        {
            e.printStackTrace();
        }
    }
}

```

## 6.3	lambda表达式

### 6.3.1	为什么引入lambda表达式

在java中传递一个代码段并不容易，不能直接传递代码段。

### 6.3.2	lambda表达式的语法

带参数变量的表达式称为λ表达式

一种***lambda***表达式形式：参数，箭头(->)以及一个表达式。如果代码要完成的计算无法放在一个表达式中，就可以像写方法一样，把这些代码放在{}中，并包含显式的return语句。

```java
(String first,String second)->
{
    if(first.length() < second.length)	return -1;
    else if(first.length > second.length)	return 1;
    else return 0;
}
```

即便lambda表达式没有参数，仍然要提供空括号，就像无参数方法一样：

```java
()->{for(int i = 100 ; i >= 0 ; i++ )	System.out.println(i);}
```

如果可以推导出一个lambda表达式的参数类型，则可以忽略其类型

在这里，编译器可以推导出first和second必然是字符串，因为这个lambda表达式将赋给一个字符串比较器

```java
Comparator<String> comp
	=(first,second)	//Same as (String first,String second)
	->first.length() - second.length();
```

如果方法只有一个参数，而且这个参数的类型可以推导得出，那么甚至还可以省略小括号

```java
ActionListener listener = event ->
	System.out.println("The time is "+new Date());
		//Instead of (event)-> ... or (ActionEvent event) -> ...
```

***重要程序***

```java
package lambda;

import java.util.*;
import javax.swing.*;
import javax.swing.Timer;

/**
 * This program demonstrates the use of lambda expressions.
 */

public class LambdaTest
{
    public static void main(String[] args)
    {
        String[] planets = new String[] {"Mercury","Venus","Earth","Mars",
                                            "Jupiter","Saturn","Uranus","Neptune"};
        System.out.println(Arrays.toString(planets));
        System.out.println("Sorted in dictionary order:");
        Arrays.sort(planets);
        System.out.println(Arrays.toString(planets));
        System.out.println("Sorted by length:");
        Arrays.sort(planets,(first,second)->first.length() - second.length());
        //等价于方法引用(method reference)
        //Arrays.sort(planets, Comparator.comparingInt(String::length));
        System.out.println(Arrays.toString(planets));

        Timer t = new Timer (1000,event->
                System.out.println("The time is " + new Date()));
        t.start();

        //keep program running until user selects "OK"
        JOptionPane.showMessageDialog(null,"Quit program?");
        System.exit(0);
    };
}

```

### 6.3.3	函数式接口

对于只有一个抽象方法的接口，需要这种接口的对象时，就可以提供一个lambda表达式。这种接口称为*函数式接口*(functional interface)。

最好把lambda表达式看做是一个函数，而不是一个对象，另外要接受lambda表达式可以传递到函数式接口。

### 6.3.4	方法引用

lambda表达式

```java 
Arrays.sort(planets,(String first,String second)->first.length() - second.length());
```

方法引用*method reference*

```java
Arrays.sort(planets, Comparator.comparingInt(String::length));
```

### 6.3.5	构造器引用

```java
Person::new
```

### 6.3.6	变量作用域

lambda表达式的三部分：

1. 一个代码块
2. 参数
3. 自由变量的值，这是指非参数而且不在代码中定义的变量

lambda表达式中捕获的变量必须实际上是最终变量（*effectively final*）。实际上的最终变量是指，这个变量初始化之后就不会再为它赋新值。

### 6.3.7	处理lambda表达式

### 6.3.8	再谈Comparator

## 6.4	内部类

内部类（inner class）是定义在另一个类中的类。

定义内部类的原因：

1. 内部类方法可以访问该类定义所在的作用域中的数据，包括私有的数据
2. 内部类可以对同一个包中的其他类隐藏起来
3. 当想要定义一个回调函数而不想编写大量代码时，使用*匿名*（anonymous）内部类比较便捷

嵌套类的好处

1. 命名控制

2. 访问控制

### 6.4.1	使用内部类访问对象状态

内部类既可以访问自己身的数据域，也可以访问创建它的外围类对象的数据域

***重要程序***

***InnerClassTest***

```java
package innerClass;

import java.awt.*;
import java.awt.event.*;
import java.sql.Time;
import java.util.*;
import javax.swing.*;
import javax.swing.Timer;

public class InnerClassTest
{
    public static void main(String[] args)
    {
        TalkingClock clock = new TalkingClock(1000,true);
        clock.start();

        //keep program running until user selects "OK;
        JOptionPane.showMessageDialog(null,"Quit program?");
        System.exit(0);
    }
}

/**
 * A clock that prints the time in regular intervals.
 */
class TalkingClock
{
    private int interval;
    private boolean beep;

    /**
     * Constructs a talking clock
     * @param interval the interval between messages (in milliseconds)
     * @param beep true if the clock should beep
     */
    public TalkingClock(int interval,boolean beep)
    {
        this.interval=interval;
        this.beep=beep;
    }

    /**
     * starts the clock
     */
    public void start()
    {
        ActionListener listener = new TimePrinter();
        Timer t = new Timer(interval,listener);
        t.start();
    }

    //inner class
    public class TimePrinter implements ActionListener
    {
        public void actionPerformed(ActionEvent event)
        {
            System.out.println("At the tone, the time is "+new Date());
            if(beep)
            {
                Toolkit.getDefaultToolkit().beep();
            }
        }
    }
}
```

### 6.4.2	内部类的特殊语法规则

1. 内部类的所有静态域都必须是final

2. 内部类不能有static方法

### 6.4.3	内部类是否有用、必要和安全

### 6.4.4	局部内部类

发现*TimerPrinter*类只在*start*方法中创建这个类型的对象时使用一次，因此可以定义局部类：

```java
public void start()
{
	class TimePrinter implements ActionListener
    {
        public void actionPerformed(ActionEvent event)
        {
            System.out.println("At the tone, the time is"+ new Date());
            if(beep)	Toolkit.getDefaultToolKit.beep();
        }
    }
}
```

优势：对外部世界完全隐藏起来

### 6.4.5	由外部方法访问变量

与其他内部类相比较，局部类还有一个有点。它们不仅能够访问包含它们的外部类，还可以访问局部变量。不过，那些局部变量必须为final。

```java
public void start(int interval,boolean beep)
{
    class TimePrinter implements ActionListener
    {
        public void actionPerformed(ActionEvent event)
        {
            System.out.println("At the tone, the time is "+new Date());
            if(beep)	Toolkit.getDefaultToolKit.beep();
        }
    }
    
    ActionListener listener = new TimePrinter();
    Timer t = new Timer(1000,listener);
    t.start();
}
```

### 6.4.6	匿名内部类

加入只创建局部内部类的一个对象，就不必命名了。这种类被称为*匿名内部类*（anonymous innerclass）

```java
public void start(int inerval,boolean beep)
{
    //省略类的命名，直接使用接口名称ActionListener
    ActionListener listener(int interval, boolean beep)
    {
        public void actionPerformed(Action event)
        {
            System.out.println("At the tone, the time is "+new Date());
            if(beep)	ToolKit.getDefaultToolKit.beep();
        }
    }
    
    Timer t = new Timer(interval,listener);
    t.start();
}
```

语法格式

```java
/**
*SuperType 可以是接口名称，例如ActionListener，于是内部类需要实现接口（重载actionPerformed）
*SuperType 可以是类名称，于是内部类就要拓展他
*/
new SuperType(construction parameters)
{
    inner class methods and data
}
```

由于构造器的名字必须与类名相同，而匿名类没有类名，所以，匿名类不能有构造器。取而代之的是，将构造器参数传递给*超类*（superclass）构造器。尤其是在内部类实现接口的时候，不能有任何构造参数。不仅如此，还要像下面这样提供一组括号

```java
new Interaface Type()
{
	methods and data
}
```

如果构造参数的闭小括号后面跟一个开大括号，正在定义的就是匿名内部类

```java
//an object of an inner class extending Person
Person count = new Person("Dracula"){...};
```

多年来，Java程序员习惯的做法是用***匿名内部类***实现事件监听和其他回调。如今最好还是使用lambda表达式。

***匿名内部类***

```java
package anonymousInnerClass;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Date;

public class AnonymousInnerClassTest
{
    public static void main(String[] args)
    {
        TimePrinter listener = new TimePrinter();
        listener.start(1000,true);

        JOptionPane.showMessageDialog(null,"Quit?");
        System.exit(0);
    }
}

class TimePrinter
{
    public void start(int delay,boolean beep)
    {
        ActionListener listener = new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("At the tone, the time is " + new Date());
                Toolkit.getDefaultToolkit().beep();
            }
        };
        Timer t = new Timer(delay,listener);
        t.start();
    }
}
```

***lambda表达式***

```java
package AnonymousInnerClass;

import javax.swing.*;
import java.awt.*;
import java.util.Date;

public class AnonymousInnerClassByLambda
{
    public static void main(String[] args)
    {
           TimePrinter printer = new TimePrinter();
           printer.start(1000,true);

           JOptionPane.showMessageDialog(null,"Quit?");
           System.exit(0);
    }
}

class TimePrinterByLambda
{
    public void start(int delay,boolean beep)
    {
        Timer t = new Timer(1000,event->
        {
            System.out.println("At the tone, the time is "+ new Date());
            if(beep)    Toolkit.getDefaultToolkit().beep();
        });
        t.start();
    }
}
```

用匿名方式构造一个数组列表，并将它传递到一个方法：***双括号初始化(double brace initialization)***

```java
//原始方法
ArrayList<String> friends = new ArrayList<>();
friends.add("Harry");
friends.add("Tony");
invite(friends);

//double brace initialization
/*
*外层括号建立ArrayList的一个子类
*内层括号运用了代码块初始化的方法（第四章）
*/
invite(new ArrayList<String>() {{add"Harry";add"Tony"}});
```

***警告***

这样的方法对于equals需要特别当心。对于匿名子类，针对equals的测试会失效：

```java
if(getClass() != other.getClass())	return false;
```

应当使用如下表达式：

```java
new Object(){}.getClass().getEnclosingClass()	//gets class of static method
```

### 6.4.7	静态内部类

有时候，使用内部类只是为了把一个类隐藏在另一个类的内部，并不需要内部类引用外部类对象。为此，可以将内部类声明为static，以便取消产生的引用。

***注释***

1. 在内部类不需要访问外围类对象的时候，应该使用静态内部类。
2. 与常规内部类不同，静态内部类可以有静态类和方法
3. 声明在接口中的内部类自动成为static和public类

***重要程序***

```java
package staticInnerClass;

import java.util.Arrays;

/**
 * This program demonstrates the use of static inner class
 */
public class StaticInnerClassTest
{
    public static void main(String[] args)
    {
        double[] d = new double[20];
        /*
         * for each循环的弊端：值传递
         * 因此使用常规的for循环
         */
        for(int i=0;i<d.length;i++)
        {
            d[i] = 100 * Math.random();
        }
        ArrayAlg.Pair p = ArrayAlg.minMax(d);

        int count = 0;
        for(double v:d)
        {
            System.out.printf(Double.toString(v)+"\t");

            if((++count)%3==0)  System.out.println();
        }
        System.out.println();

        System.out.println("min = "+p.getFirst());
        System.out.println("max = "+p.getSecond());
    }
}

class ArrayAlg
{
    /**
     * A pair of floating-point numbers
     */
    public static class Pair
    {
        private double first;
        private double second;

        /**
         * Constructs a pair from two floating-points numbers
         * @param f the first   number
         * @param s the second  number
         */
        public Pair(double f,double s)
        {
            this.first=f;
            this.second=s;
        }

        /**
         * Returns the first number of the pair
         * @return the first number
         */
        public double getFirst()
        {
            return first;
        }

        /**
         * Returns the second number of the pair
         * @return the second number
         */
        public double getSecond()
        {
            return second;
        }
    }

    /**
     * Computers both the minimum and the maximum of an array
     * @param values an array of floating-point numbers
     * @return a pair whose first element is the minimum and whose 
     *			second element
     * is the maximum
     */
    /*
     * 一个返回类型为Pair的函数
     */
    public static Pair minMax(double[] values)
    {
        double min = Double.POSITIVE_INFINITY;
        double max = Double.NEGATIVE_INFINITY;
        for(double v:values)
        {
            if(min>v)   min=v;
            if(max<v)   max=v;
        }
        return new Pair(min,max);
    }
}
```

## 6.5	代理

利用代理可以在运行时创建一个实现了一组给定接口的新类。这种功能只有在编译时无法确定需要实现哪个接口时才有必要使用。对于程序设计人员来说，遇到这种情况的机会很少。