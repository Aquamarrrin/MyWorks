#ifndef MYCONVERTER_H
#define MYCONVERTER_H

#include <fstream>
#include <iostream>
#include <QMap>
#include <QString>

using namespace std;

class MyConverter
{
public:
    MyConverter(/*QString numTxtPath*/);

    QString finalConvert(QString str);

    void changeNds(int newValue);

    ~MyConverter();
private:
    QMap<int, QString> convNum;
    int ndsValue;

    void fillMap(QString str);

    QString tmpNums(QString str);
    QString showNums(QString str);
    QString rubles (QString str, int i);

    int firstLetter(QString str, int index);
};

#endif // MYCONVERTER_H
