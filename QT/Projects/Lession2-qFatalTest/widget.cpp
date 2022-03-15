#include "widget.h"
#include <QDebug>

widget::widget(QWidget *parent)
    : QMainWindow(parent)
{
    qDebug() << "你好";

    qFatal("erroqr");
}

widget::~widget()
{
}

