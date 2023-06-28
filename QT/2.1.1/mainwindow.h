//
// Created by Liu Yuan on 2023/6/28.
//

#ifndef INC_2_1_1_2_1_1_MAINWINDOW_H_
#define INC_2_1_1_2_1_1_MAINWINDOW_H_

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE

class mainwindow : public QWidget {
 Q_OBJECT

 public:
  explicit mainwindow(QWidget *parent = nullptr);
  ~mainwindow() override;

 private:
  Ui::mainwindow *ui;
};

#endif //INC_2_1_1_2_1_1_MAINWINDOW_H_
