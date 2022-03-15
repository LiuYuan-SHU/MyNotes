#ifndef ONESELF_H
#define ONESELF_H

#include <QObject>
#include <QString>

class Oneself : public QObject
{
    Q_OBJECT
public:
    explicit Oneself(QObject *parent = nullptr);
    
//自定义槽函数，一般会写在public slots下面
public slots:
    //槽的名字是信号的名字前加on
    void onHungry();
    void onHungry_1(const QString& foodName);
signals:
    
};

#endif // ONESELF_H
