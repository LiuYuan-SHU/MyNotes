#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QDebug>

using Qt::endl;

class MyPushButton:public QPushButton
{
public:
    using QPushButton::QPushButton;
    ~MyPushButton()
    {
        qDebug() << " button destruction" << endl;
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void onClicked();
};
#endif // MAINWINDOW_H
