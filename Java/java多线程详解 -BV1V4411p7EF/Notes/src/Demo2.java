import org.apache.commons.io.FileUtils;

import java.io.File;
import java.io.IOException;
import java.net.URL;

/**
 * @author Liu Yuan
 * @create 2021-11-29-16:23
 * @describe 练习Thread，实现多线程同步下载图片
 */
public class Demo2 extends Thread
{
    private String url;     //网络图片地址
    private String name;    //保存的文件名

    public Demo2(String url, String name)
    {
        this.url = url;
        this.name = name;
    }

    public void run()
    {
        /**
         * @function run
         * @param []
         * @return void
         * @description 下载图片线程的执行体
         * @author Liu Yuan
         * @time 16:34
         */
        WebDownloader webDownloader = new WebDownloader();
        webDownloader.downloader(url, name);
        System.out.println("下载了文件名为：" + name);
    }

    public static void main(String[] args)
    {
        //可能的运行结果
        /*
         * 下载了文件名为：1.jpg
         * 下载了文件名为：3.jpg
         * 下载了文件名为：2.jpg
         */
        Demo2 demo1 = new Demo2("https://p1.music.126.net/vmCcDvD1H04e9gm97xsCqg==/109951163350929740.jpg","1.jpg");
        Demo2 demo2 = new Demo2("https://p1.music.126.net/XPPeIZu7wgcGXZ0666mfFg==/109951164640697307.jpg","2.jpg");
        Demo2 demo3 = new Demo2("https://p2.music.126.net/Nl4mFBPeN4Lqtqn3KOAvXQ==/109951166171044898.jpg","3.jpg");

        demo1.start();
        demo2.start();
        demo3.start();
    }
}

class WebDownloader
{
    public void downloader(String url, String name)
    {
        /**
         * @function downloader
         * @param []
         * @return void
         * @description 下载方法
         * @author Liu Yuan
         * @time 16:24
         */
        try
        {
            FileUtils.copyURLToFile(new URL(url), new File(name));
        } catch (IOException e)
        {
            e.printStackTrace();
            System.out.println("IO异常，Downloader方法出现问题");
        }
    }
}
