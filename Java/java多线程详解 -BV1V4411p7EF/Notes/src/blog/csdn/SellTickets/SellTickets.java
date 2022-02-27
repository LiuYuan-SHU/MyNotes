package blog.csdn.SellTickets;

/**
 * @author Liu Yuan
 * @create 2022-02-26-16:48
 * @describe
 */
public class SellTickets extends Thread
{
    // 通过构造方法给线程名字赋值
    public SellTickets(String name) {
        super(name);// 给线程名字赋值
    }

    // 为了保持票数的一致，票数要静态
    static int tick = 20;

    // 创建一个静态钥匙
    static Object ob = "aa";//值是任意的

    // 重写run方法，实现买票操作
    @Override
    public void run() {
        while (tick > 0) {
            synchronized (ob) {// 这个很重要，必须使用一个锁，
                // 进去的人会把钥匙拿在手上，出来后才把钥匙拿让出来
                if (tick > 0) {
                    System.out.println(getName() + "卖出了第" + tick + "张票");
                    tick--;
                } else {
                    System.out.println("票卖完了");
                }
            }
            try {
                sleep(1);//休息0.001秒
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

        }
    }
}
