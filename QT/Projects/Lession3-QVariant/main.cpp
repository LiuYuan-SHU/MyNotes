#include <iostream>
#include <QCoreApplication>
#include <QVariant>
#include <QDebug>
#include <QString>

using namespace Qt;
using std::cout;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QVariant v(2);
    QVariant v1("hellow");
    QVariant v2(QByteArray("hello"));

    qDebug() << v
             << v1
             << v2;

    int temp = v.toInt();
    qDebug() << temp << endl;

    qDebug() << v.value<int>() << endl;
    //cout << v.metaType().id() << endl;
    //qDebug() << v.metaType().id() << endl;
    qDebug() << v.typeName();

    return a.exec();
}
