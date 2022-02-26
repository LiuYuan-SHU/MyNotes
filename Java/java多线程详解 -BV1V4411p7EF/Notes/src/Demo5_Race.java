/**
 * @author Liu Yuan
 * @create 2021-12-06-16:17
 * @describe 模拟归途赛跑
 */
public class Demo5_Race implements Runnable
{
    //胜利者
    private static String winner;

    @Override
    public void run()
    {
        for (int i = 0; i <= 100; i++)
        {
            //模拟兔子休息
            if(Thread.currentThread().getName() == "兔子" && i / 10 ==0)
            {
                try
                {
                    Thread.sleep(1);
                } catch (InterruptedException e)
                {
                    e.printStackTrace();
                }
            }

            //判断比赛是否结束
            boolean flag = gameOver(i);
            //如果比赛结束，停止程序
            if(flag)
            {
                break;
            }
            System.out.println(Thread.currentThread().getName() + "-->跑了" + i  + "步");
        }
    }

    private boolean gameOver(int steps)
    {
        /**
         * @function gameOver
         * @param []
         * @return boolean
         * @description 判断胜利者
         * @author Liu Yuan
         * @time 16:18
         */
        if(winner != null)
        {
            return true;
        }
        if(steps == 100)
        {
            winner = Thread.currentThread().getName();
            System.out.println("winner is " + winner);
            return true;
        }

        return false;
    }

    public static void main(String[] args)
    {
        Demo5_Race race = new Demo5_Race();

        new Thread(race,"兔子").start();
        new Thread(race,"乌龟").start();
    }
}
