#include "widget.h"
#include "mypushbutton.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->_button = new MyPushButton(this);
    this->_button->setText("press me");
    this->resize(640,480);
    
    connect(this->_button, &QPushButton::clicked, this, Widget::onClicked)
}

Widget::~Widget()
{
}

void Widget::onClicked()
{
    emit this->_button->selfClicked();
    emit this->_button->selfClicked("pressed me");
}

