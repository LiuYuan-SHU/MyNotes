#include "widget.h"

#include <vector>
#include <iostream>
#include <QApplication>
#include <QByteArray>

using std::vector;
using std::cout;
using std::cin;
using std::endl;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    widget w;
    w.show();
    return a.exec();
}
