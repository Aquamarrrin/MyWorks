#ifndef WORD_H
#define WORD_H

#include <QString>
#include <QMap>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QVector>
#include <QDebug>
#include <QTextCodec>
#include "myword.h"

using namespace std;

class Words
{
public:
    Words();

    void fillMapEng(QString str);
    void fillMapUkr(QString str);

    QString coutRusWord(QString str);
    QString coutUkrWord(QString str);


    ~Words();
private:
    QMap<QString,QString> dictionaryEng;
    QMap<QString,QString> dictionaryUkr;

    QVector<QString> listOfRus;

    int firstLetter(QString str, int index);
    int findRusN(QVector<MyWord> rusStr, int index, int wh);
    int partOfRus(QString str);    //определяет часть речи 1-сущ 2-глаг 3-прил 4-нар 5-мест 6-союз/част 7-предл

    QString delAllSpAfWord(QString str);
    QString resetToDef(QString str,int lan);
};

#endif // WORD_H
