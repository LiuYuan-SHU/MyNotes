#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QWidget>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    MyPushButton(QWidget* parent = nullptr);
    
signals:
    void selfClicked();
    void selfClicked(const QString& test);
};

#endif // MYPUSHBUTTON_H
