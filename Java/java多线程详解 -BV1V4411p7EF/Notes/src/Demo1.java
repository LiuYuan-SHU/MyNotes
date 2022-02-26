/**
 * @author Liu Yuan
 * @create 2021-11-29-15:37
 * @describe 创建线程方式一：继承Thread类
 * （1）重写run()方法
 * （2）调用start开启线程
 */
public class Demo1 extends Thread
{
    public void run()
    {
        /**
         * @function run
         * @param []
         * @return void
         * @description run()函数是开辟一个新的线程，而start()和正常运行没有区别
         * @author Liu Yuan
         * @time 16:13
         */
        //run方法线程体
        for (int i = 0; i < 20; i++)
        {
            System.out.println("我在看代码" + i);
        }
    }

    //main函数，主线程
    public static void main(String[] args)
    {
        test1();
    }

    public static void test1()
    {
        //可能的输出：
        /*
         * 我在看代码10
         * 我在看代码11
         * 我在看代码12
         * 我在学习多线程--4
         * 我在学习多线程--5
         * 我在学习多线程--6
         * 我在学习多线程--7
         * 我在学习多线程--8
         * 我在学习多线程--9
         * 我在学习多线程--10
         * 我在学习多线程--11
         * 我在看代码13
         * 我在学习多线程--12
         */

        //创建一个线程对象
        Demo1 demo1 = new Demo1();
        //调用start()方法开启线程
        demo1.start();

        for (int i = 0; i < 200; i++)
        {
            System.out.println("我在学习多线程--" + i);
        }
    }
}
