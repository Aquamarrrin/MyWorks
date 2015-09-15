#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QLineEdit>
#include <QTextEdit>
#include "myconverter.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QPushButton* btnConvert;
    QLineEdit* number;
    QTextEdit* label;
    QSpinBox* nds;
    MyConverter conv;

public slots:
    void showConv();
    void changeNdsValue(int newV);
};

#endif // MAINWINDOW_H
