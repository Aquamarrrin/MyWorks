#include <QApplication>
#include "mainwindow.h"
#include "myfield.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mw;
    mw.show();
    return a.exec();
}
