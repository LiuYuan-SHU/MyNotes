package blog.csdn.SellTickets;

/**
 * @author Liu Yuan
 * @create 2022-02-26-16:49
 * @describe
 */
public class Main
{
    public static void main(String[] args) {
        //实例化站台对象，并为每一个站台取名字
        SellTickets station1=new SellTickets("站台1");
        SellTickets station2=new SellTickets("站台2");
        SellTickets station3=new SellTickets("站台3");

        // 让每一个站台对象各自开始工作
        station1.start();
        station2.start();
        station3.start();
    }
}
