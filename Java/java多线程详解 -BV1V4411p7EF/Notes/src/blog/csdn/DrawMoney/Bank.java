package blog.csdn.DrawMoney;

/**
 * @author Liu Yuan
 * @create 2022-02-26-16:52
 * @describe
 */
public class Bank
{
    // 假设一个账户有1000块钱
    static int money = 1000;

    // 柜台Counter取钱的方法
    public void Counter(int money) {// 参数是每次取走的钱
        Bank.money -= money;//取钱后总数减少
        System.out.println("A取走了" + money + "还剩下" + (Bank.money));
    }

    // ATM取钱的方法
    public void ATM(int money) {// 参数是每次取走的钱
        Bank.money -= money;//取钱后总数减少
        System.out.println("B取走了" + money + "还剩下" + (Bank.money));
    }
}
