//
// Created by Liu Yuan on 2023/6/27.
//
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  mainwindow window;
  window.show();

  return app.exec();
}