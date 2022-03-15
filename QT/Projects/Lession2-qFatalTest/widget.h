#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>

class widget : public QMainWindow
{
    Q_OBJECT

public:
    widget(QWidget *parent = nullptr);
    ~widget();
};
#endif // WIDGET_H
