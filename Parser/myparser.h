#ifndef MYPARSER_H
#define MYPARSER_H

#include <iostream>
#include <fstream>
#include <QString>
#include <QVector>
#include <QMap>
#include <QtDebug>

using namespace std;


class MyParser
{
public:
    MyParser(QString filePath);
    void runProg();
    void shV();
private:
    QVector<QString> progTxt;
    QMap<QString, float> varPr;
    QMap<QString,int> loops;

    void newVar(QString str, int index);
    void operaton(QString str, char op, int index);
    void sqrtV(QString str, int index);
    void coutThisVar(QString str, int index);
    void cinThisVar(QString str, int index);
    void condition(QString str, int index, int size);
    void doOperations(int index, int size);

    int firstLetter(QString str, int index);
};

#endif // MYPARSER_H
