/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainwindow
{
public:
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QWidget *mainwindow)
    {
        if (mainwindow->objectName().isEmpty())
            mainwindow->setObjectName("mainwindow");
        mainwindow->resize(400, 300);
        label = new QLabel(mainwindow);
        label->setObjectName("label");
        label->setGeometry(QRect(100, 90, 111, 41));
        QFont font;
        font.setPointSize(30);
        label->setFont(font);
        pushButton = new QPushButton(mainwindow);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(220, 200, 141, 71));

        retranslateUi(mainwindow);
        QObject::connect(pushButton, &QPushButton::clicked, mainwindow, qOverload<>(&QWidget::close));

        QMetaObject::connectSlotsByName(mainwindow);
    } // setupUi

    void retranslateUi(QWidget *mainwindow)
    {
        mainwindow->setWindowTitle(QCoreApplication::translate("mainwindow", "mainwindow", nullptr));
        label->setText(QCoreApplication::translate("mainwindow", "Hello Qt", nullptr));
        pushButton->setText(QCoreApplication::translate("mainwindow", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainwindow: public Ui_mainwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
