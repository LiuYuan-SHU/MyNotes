/**
 * @author Liu Yuan
 * @create 2021-11-29-16:44
 * @describe 创建线程方式2：
 *              （1）实现Runnable接口，重写run()方法
 *              （2）执行线程需要丢入Runnable接口实现类，调用start()方法
 */
public class Demo3 implements Runnable
{
    @Override
    public void run()
    {
        for (int i = 0; i < 100; i++)
        {
            System.out.println("我在看代码" + i);
        }
    }

    public static void main(String[] args)
    {
        //创建一个Runnable接口的实现类对象
        Demo3 demo = new Demo3();
        //创建线程对象，通过线程对象来开启线程，代理
//        Thread thread = new Thread(demo);
//        thread.start();
        new Thread(demo).start();

        for (int i = 0; i < 1000; i++)
        {
            System.out.println("我在学习多线程" + i);
        }
    }
}
