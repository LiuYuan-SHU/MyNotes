#ifndef GIRLFRIEND_H
#define GIRLFRIEND_H

#include <QObject>
#include <QString>

class GirlFriend : public QObject
{
    //如果想要使用信号与槽机制，就需要加上这个宏
    Q_OBJECT
public:
    explicit GirlFriend(QObject *parent = nullptr);
    
//定义信号，必须在signals下定义
//信号只是函数的声明，但是不可以实现，Qt框架在预编译的时候自动为我们实现
signals:
    //饿了信号
    void hungry();   
    //带参信号
    void hungry_1(const QString& foodName);
    
};

#endif // GIRLFRIEND_H
