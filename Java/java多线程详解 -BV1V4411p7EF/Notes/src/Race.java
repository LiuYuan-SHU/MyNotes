/**
 * @author Liu Yuan
 * @create 2021-12-06-16:53
 * @describe 重写Demo - Race
 */
public class Race implements Runnable
{
    private static String winner;

    @Override
    public void run()
    {
        for (int i = 0; i < 101; i++)
        {
            if(win(i))
            {
                System.out.println("到达终点");
                break;
            }

            System.out.println(Thread.currentThread().getName() + "-->跑了" + i + "步");

        }
    }

    private boolean win(int steps)
    {
        if(winner != null)
        {
            return true;
        }

        if(steps == 100)
        {
            return true;
        }
        return false;
    }

    public static void main(String[] args)
    {
        Race race = new Race();

        new Thread(race,"兔子").start();
        new Thread(race,"乌龟").start();


    }
}


