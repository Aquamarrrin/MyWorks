#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QColorDialog>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:

public slots:

private slots:
    void setCellColor();


private:
    QPushButton* btnStart;
    QPushButton* btnStop;
    QPushButton* btnClear;
    QPushButton* btnNewRules;
    QPushButton* ResetRules;
    QPushButton* setColor;
    QSpinBox* spinBox1;
    QSpinBox* spinBox2;
    QColorDialog * dl;

};

#endif // MAINWINDOW_H
