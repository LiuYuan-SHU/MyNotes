#include "oneself.h"
#include <QDebug>

Oneself::Oneself(QObject *parent)
    : QObject{parent}
{
    
}

void Oneself::onHungry()
{
    qDebug() << "多喝热水";
}

void Oneself::onHungry_1(const QString &foodName)
{
    qDebug() << "走，我们去吃" << foodName.toUtf8().data();
}
