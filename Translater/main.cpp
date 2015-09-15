#include <words.h>
#include <QDebug>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    //setlocale(LC_ALL,"Russian");
    setlocale(LC_ALL,"Ukrainian");
    Words dict;

//    qDebug()<< dict.coutRusWord("We are what we repeatedly do")<<endl;
//    qDebug()<<dict.coutRusWord("A friend is a second self")<<endl;
//    qDebug()<<dict.coutRusWord("I always like to know everything about my new friends, and nothing about my old ones")<<endl;
//    qDebug()<<dict.coutRusWord("the gods are too fond of a joke")<<endl;
//    qDebug()<< dict.coutUkrWord(dict.coutRusWord("We are what we repeatedly do"))<<endl;
//    qDebug()<< dict.coutUkrWord(dict.coutRusWord("A friend is a second self"))<<endl;
//    qDebug()<< dict.coutUkrWord(dict.coutRusWord("I always like to know everything about my new friends, and nothing about my old ones"))<<endl;
//    qDebug()<< dict.coutUkrWord(dict.coutRusWord("The gods too are fond of a joke."))<<endl;
//    qDebug()<< dict.coutRusWord("My friend always forgive me for this words.")<<endl;
//    qDebug()<< dict.coutUkrWord(dict.coutRusWord("My friend always forgive me for this words."))<<endl;

    char* str;
    QString strTmp;
    cout<<"Please enter your phrase or \"no\":"<<endl;
    gets(str);
    strTmp=QString::fromLocal8Bit(str);
    while(strTmp!="no")
    {
        qDebug()<< dict.coutRusWord(strTmp)<<endl;
        qDebug()<< dict.coutUkrWord(dict.coutRusWord(strTmp))<<endl;
        cout<<"Continue?"<<endl;
        gets(str);
        strTmp=QString::fromLocal8Bit(str);
    }

    return 0;
}
