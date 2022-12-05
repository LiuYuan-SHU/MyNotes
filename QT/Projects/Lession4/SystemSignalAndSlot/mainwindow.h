#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "girlfriend.h"
#include "oneself.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
public slots:
    void onHungry_clicked();
    
private:
    GirlFriend *_girl;
    Oneself    *_self;
};
#endif // MAINWINDOW_H
