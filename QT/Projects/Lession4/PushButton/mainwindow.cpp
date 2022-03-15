#include "mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //不要创建栈区的变量，因为构造函数执行完毕，内存立马会释放
    //empty construction
    QPushButton* btn = new QPushButton();
    //以独立窗口进行显示组件，如果没有设置父对象，那么会创建独立的按钮
    //btn->show();
    //设置父对象，如果父对象显示，那么该组件也会自动显示
    btn->setParent(this);
    btn->setText("第一个按钮");

    //通过构造函数设置父对象，会使窗口以字组件的大小进行调整
    QPushButton* btn2 = new MyPushButton("第二个按钮",this);
    //第一个按钮和第二个按钮会发生重叠，因此要进行移动
    btn2->move(100,0);
    //重新设置窗口的大小
    this->setWindowTitle("按钮测试");
    this->resize(640,480);

    //关联信号与槽
    /*
     * sender   信号的发出者
     * signal   什么信号
     * receiver 信号接收者
     * method   对应的信号处理函数
     */
    connect(btn2, QPushButton::clicked, this, MainWindow::onClicked);
    connect(btn2, QPushButton::pressed, this, MainWindow::onClicked);
}

MainWindow::~MainWindow()
{
}


void MainWindow::onClicked()
{
    qDebug() << "button pressed";
}
