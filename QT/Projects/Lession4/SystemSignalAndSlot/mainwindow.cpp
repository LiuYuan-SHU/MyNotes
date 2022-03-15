#include "mainwindow.h"
#include "girlfriend.h"
#include "oneself.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //分配内存
    this->_girl = new GirlFriend(this);
    this->_self = new Oneself(this);
    //连接信号与槽
    //connect(this->_girl, GirlFriend::hungry, this->_self, Oneself::onHungry);
    connect(this->_girl, GirlFriend::hungry_1, this->_self, Oneself::onHungry_1);
    
    //通过一个按钮触发信号
    QPushButton* button_hungry = new QPushButton("我饿了",this);
    //将button连接到this->_girl->hungry，再通过另一个connect触发槽onHungry
    //connect(button_hungry, QPushButton::clicked, this, MainWindow::onHungry_clicked);
    
    //直接连接，不需要两个connect
    //信号不仅仅与槽建立关联，还可以与信号进行关联
    //connect(button_hungry, QPushButton::clicked, this->_girl, GirlFriend::hungry);
    //带参信号
    connect(button_hungry, QPushButton::clicked, this, MainWindow::onHungry_clicked);
}

MainWindow::~MainWindow()
{
}

void MainWindow::onHungry_clicked()
{
    //发送信号，就是调用信号函数是
    //发送信号一般会在发送之前加上一个宏，用来表示这是发送一个信号,emit
    //emit this->_girl->hungry();
    emit this->_girl->hungry_1("hamburger");
}

