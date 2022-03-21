#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mypushbutton.h"

class Widget : public QWidget
{
    Q_OBJECT
private:
    MyPushButton *_button;
    
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    
public slots:
    void onClicked();
};
#endif // WIDGET_H
