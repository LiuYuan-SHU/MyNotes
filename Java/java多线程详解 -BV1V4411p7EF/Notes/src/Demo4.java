/**
 * @author Liu Yuan
 * @create 2021-11-29-19:09
 * @describe 多个线程同时操作同一个对象：买火车票
 */
public class Demo4 implements Runnable
{
    private int ticketNums = 10;

    @Override
    public void run()
    {
        while (true)
        {
            if (ticketNums <= 0)
            {
                break;
            }

            //模拟延时
            try
            {
                Thread.sleep(200);
            } catch (InterruptedException e)
            {
                e.printStackTrace();
            }

            System.out.println(Thread.currentThread().getName() + "拿到了第" + ticketNums-- + "票");
        }
    }

    public static void main(String[] args)
    {
        //可能的结果：——并发问题
        /*
         * 小明拿到了第10票
         * 黄牛党拿到了第9票
         * 老师拿到了第8票
         * 老师拿到了第7票
         * 小明拿到了第7票
         * 黄牛党拿到了第7票
         * 小明拿到了第6票
         * 老师拿到了第6票
         * 黄牛党拿到了第6票
         * 小明拿到了第5票
         * 老师拿到了第5票
         * 黄牛党拿到了第5票
         * 老师拿到了第4票
         * 黄牛党拿到了第4票
         * 小明拿到了第4票
         * 老师拿到了第3票
         * 黄牛党拿到了第2票
         * 小明拿到了第3票
         * 小明拿到了第1票
         * 黄牛党拿到了第1票
         * 老师拿到了第1票
         */
        Demo4 demo = new Demo4();

        new Thread(demo, "小明").start();
        new Thread(demo, "老师").start();
        new Thread(demo, "黄牛党").start();
    }


}
