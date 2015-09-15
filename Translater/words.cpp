#include "words.h"

Words::Words()
{
    QFile myFile("D:\\Qt\\Qt5.1.1\\Tools\\QtCreator\\bin\\Translater\\engrus.txt");
    if(!myFile.open(QFile::ReadOnly | QFile::Text))
    {

    }
    QTextStream myText(&myFile);
    while (myText.atEnd() == false)
    {
        QString strTxt=myText.readLine();
        fillMapEng(strTxt);
    }
    myFile.close();

    QFile myFile1("D:\\Qt\\Qt5.1.1\\Tools\\QtCreator\\bin\\Translater\\ukrrus.txt");
    if(!myFile1.open(QFile::ReadOnly | QFile::Text))
    {

    }
    QTextStream myText1(&myFile1);
    while (myText1.atEnd() == false)
    {
        QString strTxt=myText1.readLine();
        fillMapUkr(strTxt);
    }
    myFile1.close();
}

void Words::fillMapEng(QString str)
{
    int i=firstLetter(str,0);
    QString tmp;
    QString tmpStr="";
    while(str[i]!=' ' || str[i+1]!='-')
    {
        tmpStr+=str[i];
        i++;
    }
    tmp=tmpStr;
    tmpStr="";
    i=firstLetter(str,i+2);
    while(str[i]!=' ' && i!=str.size())
    {
        tmpStr+=str[i];
        i++;
    }
    i=0;
    dictionaryEng[tmp]=tmpStr;
    //qDebug()<<tmp<<" : "<<dictionaryEng[tmp]<<endl;
}

void Words::fillMapUkr(QString str)
{
    int i=firstLetter(str,0);
    QString tmp="";
    QString tmpStr="";
    while(str[i]!=' ' && str[i+1]!='-')
    {
        tmpStr+=str[i];
        i++;
    }
    tmp=tmpStr;
    tmpStr="";
    i=firstLetter(str,i+2);
    while(str[i]!=' ' && i!=str.size())
    {
        tmpStr+=str[i];
        i++;
    }
    i=0;
    dictionaryUkr[tmpStr]=tmp;
    listOfRus.push_back(tmpStr);
    //qDebug()<<tmpStr<<endl;
    //qDebug()<<tmpStr<<" : "<<dictionaryUkr[tmpStr]<<endl;
}


QString Words::coutRusWord(QString str)
{
    setlocale(LC_ALL,"Russian");
    int i=firstLetter(str,0);
    int j=i;
    QString tmp="";
    QVector<MyWord> rusSent;
    QVector<QString> sent;
    QString tmpRus="";
    str=delAllSpAfWord(str);
    while(j!=str.size() && str[j]!='.')
    {
        j++;
        tmp="";
        while(str[i]!=' ' && i!=str.size() && str[i]!='.' && str[i]!=',')
        {
            tmp+=str[i].toLower();
            i++;
        }
        j=i;
        i=firstLetter(str,i);
        sent.push_back(tmp);
    }

    tmpRus="";
    for(int k=0;k<sent.size();k++)
    {
        if (k==-1)
            k=0;
        MyWord rw;
        if(sent[k]!="a" && sent[k]!="the")
        {
            if (sent[k]=="fond" || sent[k]=="like" || (sent[k]=="do" && k!=sent.size()-1 && sent[k+1]=="not"))
            {
                sent[k]=sent[k]+" "+sent[k+1];
                sent.remove(k+1);
            }
            if( sent[k]=="are" && k!=sent.size()-1 && sent[k+1]=="what")
            {
                dictionaryEng[sent[k]]="то";
            }
            else
                if(sent[k]=="are" && k!=sent.size()-1 && sent[k+1]!="what")
            {
                    sent.remove(k);
                    k--;
                continue;
            }

            if (sent[k]=="is")
            {
                if(k!=0)
                        dictionaryEng[sent[k]]="- это";
                else
                        dictionaryEng[sent[k]]="это";
             }
            if(sent[k]=="ones")
            {
                int countOfIt=0;
                while(countOfIt<rusSent.size() && sent[findRusN(rusSent,countOfIt,1)][sent[findRusN(rusSent,countOfIt,1)].size()-1]!='s')
                    countOfIt=findRusN(rusSent,countOfIt+1,1);
                if( sent[findRusN(rusSent,countOfIt,1)][sent[findRusN(rusSent,countOfIt,1)].size()-1]=='s')
                    sent[k]= sent[findRusN(rusSent,countOfIt,1)];
            }

            rw.value=dictionaryEng[sent[k]];
            if((k!=0 && (sent[k-1]!="like to" && sent[k-1]!="fond of")) || k==0)
                rw.part=partOfRus(dictionaryEng[sent[k]]);
            if (rw.value!="")
                rusSent.push_back(rw);
        }
        else
        {
            sent.remove(k);
            k--;
        }
    }
    int countOfPril=0;
    for(int k=0;k<rusSent.size();k++)
    {
        //qDebug()<<rusSent[k].value<<endl;
        //ГЛАГОЛЫ
        if(rusSent[k].part==2)
        {
            QString tmpNoun=rusSent[findRusN(rusSent,0,1)].value;
            QString tmpMest=rusSent[findRusN(rusSent,0,5)].value;
            if(k!=0 && sent[k-1]=="always")
            {
                rusSent[k].value[rusSent[k].value.size()-2].unicode()=1083; //1083-л
                rusSent[k].value.remove(rusSent[k].value.size()-1,1);
            }
            if(rusSent[k].value[rusSent[k].value.size()-3].unicode()==1080)
            {
                if(tmpNoun[tmpNoun.size()-1].unicode()== 1080 || sent[findRusN(rusSent,0,1)][sent[findRusN(rusSent,0,1)].size()-1]=='s') //1080-и
                {
                   // qDebug()<<sent[findRusN(rusSent,0,1)]<<endl;
                    rusSent[k].value[rusSent[k].value.size()-3].unicode()=1103; //1103-я
                    rusSent[k].value[rusSent[k].value.size()-2].unicode()=1090; //1090-т
                    rusSent[k].value.remove(rusSent[k].value.size()-1,1);
                }
                else
                if(rusSent[k].value=="любить")
                {
                    rusSent[k].value[rusSent[k].value.size()-3].unicode()=1083; //1083-л
                    rusSent[k].value[rusSent[k].value.size()-2].unicode()=1102; //1102-ю
                    rusSent[k].value.remove(rusSent[k].value.size()-1,1);
                }
                else
                    rusSent[k].value.remove(rusSent[k].value.size()-1,1);
            }
            if(rusSent[k].value[rusSent[k].value.size()-3].unicode()==1072) //1072-a
            {
                if(tmpMest=="мы")
                {
                    rusSent[k].value[rusSent[k].value.size()-2].unicode()=1077; //1077-е
                    rusSent[k].value[rusSent[k].value.size()-1].unicode()=1084; //1084-м
                }
                if(tmpMest=="я")
                {
                    rusSent[k].value[rusSent[k].value.size()-2].unicode()=1102; //1102-ю
                    rusSent[k].value.remove(rusSent[k].value.size()-1,1);
                }
            }
        }

        //ПРИЛАГАТЕЛЬНЫЕ
        if(rusSent[k].part==3)
        {
            if (k!=0 && rusSent[k-1].part!=3)
                countOfPril=0;
            countOfPril++;
            int tmpNounIndex=0;
            if (k!=rusSent.size()-1)
                tmpNounIndex=findRusN(rusSent,k+1,1);
            QString tmpNoun=rusSent[tmpNounIndex].value;
            QString tmpPr="";
            int tmpPrInd=0;
            if(k-countOfPril>=0)
            {
                tmpPrInd=findRusN(rusSent,k-countOfPril,7);
                tmpPr=rusSent[tmpPrInd].value;
            }

            if(rusSent[tmpNounIndex].part==1)
            {
                if(tmpNoun[tmpNoun.size()-1].unicode()==1072) //1072-а
                {
                    if(rusSent[k].value[rusSent[k].value.size()-2].unicode()!=1086) //1086-о
                        rusSent[k].value[rusSent[k].value.size()-2].unicode()=1072; //1072-а
                    rusSent[k].value[rusSent[k].value.size()-1].unicode()=1103; //1103-я
                }
                if(tmpNoun[tmpNoun.size()-1].unicode()==1086) //1086-о
                {
                    if(rusSent[k].value[rusSent[k].value.size()-2].unicode()!=1086)
                       rusSent[k].value[rusSent[k].value.size()-2].unicode()=1086;
                    rusSent[k].value[rusSent[k].value.size()-1].unicode()=1077; //1077-е
                }
                if(tmpNoun[tmpNoun.size()-1].unicode()==1080 || sent[tmpNounIndex][sent[tmpNounIndex].size()-1]=='s') //1080-и
                {
                    if(rusSent[k].value[rusSent[k].value.size()-2].unicode()!=1086)
                    {
                       rusSent[k].value[rusSent[k].value.size()-2].unicode()=1099; //1099-ы
                       rusSent[k].value[rusSent[k].value.size()-1].unicode()=1077; //1077-е
                    }
                    else
                       rusSent[k].value[rusSent[k].value.size()-1].unicode()=1080; //1080-и
                }
                if(rusSent[tmpPrInd].part==7)
                {
                    if(tmpPr=="о")
                    {
                        if(tmpNoun[tmpNoun.size()-1].unicode()==1080 || sent[tmpNounIndex][sent[tmpNounIndex].size()-1]=='s') //1080-и
                        {
                            if(rusSent[k].value[rusSent[k].value.size()-2].unicode()!=1086)
                            {
                               rusSent[k].value[rusSent[k].value.size()-2].unicode()=1099; //1099-ы
                               rusSent[k].value[rusSent[k].value.size()-1].unicode()=1093; //1093-х
                            }
                            else
                                rusSent[k].value+="x";
                        }
                    }
                }
            }
        }

        //СУЩЕСТВИТЕЬНЫЕ
        if(rusSent[k].part==1)
        {
            QString tmpPr="";
            int tmpPrInd=0;
            if(k-countOfPril-1>=0)
            {
                tmpPrInd=findRusN(rusSent,k-countOfPril-1,7);
                tmpPr=rusSent[tmpPrInd].value;
            }

            if(rusSent[tmpPrInd].part==7)
            {
                if(tmpPr=="о")
                {
                    if(rusSent[k].value[rusSent[k].value.size()-1].unicode()!=1072 && rusSent[k].value[rusSent[k].value.size()-1].unicode()!=1103) //1072-а 1103-я
                        rusSent[k].value[rusSent[k].value.size()-1].unicode()=1072;
                    rusSent[k].value+="x"; //1093-х
                }
            }
        }

        //МЕСТОИМЕНИЯ
        if(rusSent[k].part==5)
        {
            QString tmpPr="";
            int tmpPrInd=0;
            int tmpNounIndex=0;
            if (k!=rusSent.size()-1)
                tmpNounIndex=findRusN(rusSent,k+1,1);
            QString tmpNoun=rusSent[tmpNounIndex].value;
            if(k-countOfPril>=0)
            {
                tmpPrInd=findRusN(rusSent,k-countOfPril,7);
                tmpPr=rusSent[tmpPrInd].value;
            }


            if(rusSent[tmpPrInd].part==7)
            {
                if(rusSent[k].value=="это")
                {
                    if(tmpPr=="за")
                    {
                        if(tmpNoun[tmpNoun.size()-1].unicode()==1080 || sent[tmpNounIndex][sent[tmpNounIndex].size()-1]=='s') //1080-и
                            rusSent[k].value[rusSent[k].value.size()-1].unicode()=1080;
                    }
                }
            }
        }

        tmpRus=tmpRus+rusSent[k].value+' ';
    }


    tmpRus[0]=tmpRus[0].toUpper();
    tmpRus+=".";
    return tmpRus;
}




QString Words::coutUkrWord(QString str)
{
    setlocale(LC_ALL,"Ukrainian");
    int i=firstLetter(str,0);
    int j=i;
    QString tmp="";
    QVector<QString> sent;
    QVector<MyWord> ukrSent;
    QString tmpUkr="";
    str=delAllSpAfWord(str);
    while(j!=str.size() && str[j]!='.')
    {
        j++;
        tmp="";
        while(str[i]!=' ' && i!=str.size() && str[i]!='.' && str[i]!=',')
        {
            tmp+=str[i].toLower();
            i++;
        }
        j=i;
        i=firstLetter(str,i);
        sent.push_back(resetToDef(tmp,2));
        //qDebug()<<resetToDef(tmp,2)<<endl;
    }

    tmpUkr="";
    for(int k=0;k<sent.size();k++)
    {
        MyWord uw;/*
        if (sent[k]=="это")
        {
            if(k!=0)
                    dictionaryUkr[sent[k]]="- "+dictionaryUkr[sent[k]];
            //qDebug()<<dictionaryUkr[sent[k]]<<endl;
        }*/
        uw.value=dictionaryUkr[sent[k]];
        if((k!=0 && (sent[k-1]!="хотеть" && sent[k-1]!="любить")) || k==0)
            uw.part=partOfRus(sent[k]);
        if(k!=0 && sent[k-1]=="бог" && sent[k]=="простить")
        {
            uw.value=sent[k];
            uw.part=0;
        }
        ukrSent.push_back(uw);
        //tmpUkr=tmpUkr+dictionaryUkr[sent[k]]+' ';
    }



    int countOfPril=0;
    for(int k=0;k<ukrSent.size();k++)
    {
        //ГЛАГОЛЫ
        if(ukrSent[k].part==2)
        {
            int tmpNounNum=findRusN(ukrSent,0,1);
           // qDebug()<<sent[tmpNounNum]<<endl;
            //qDebug()<<ukrSent[tmpNounNum].value<<endl;
            QString tmpMest=ukrSent[findRusN(ukrSent,0,5)].value;
            if(k!=0 && sent[k-1]=="всегда")
            {
                ukrSent[k].value[ukrSent[k].value.size()-2].unicode()=1074; //1074-в
                ukrSent[k].value.remove(ukrSent[k].value.size()-1,1);
            }
            if(ukrSent[k].value[ukrSent[k].value.size()-3].unicode()==1080)
            {
                if(ukrSent[tmpNounNum].value[ukrSent[tmpNounNum].value.size()-1]=='i' || sent[tmpNounNum][sent[tmpNounNum].size()-1].unicode()==1080) //1080-и
                {
                    ukrSent[k].value[ukrSent[k].value.size()-3].unicode()=1083; //1083-л
                    ukrSent[k].value[ukrSent[k].value.size()-2].unicode()=1103; //1103-я
                    ukrSent[k].value[ukrSent[k].value.size()-1].unicode()=1090; //1090-т
                    ukrSent[k].value+="ь";
                }/*
                else
                    ukrSent[k].value.remove(ukrSent[k].value.size()-1,1);*/
            }
            if(ukrSent[k].value[ukrSent[k].value.size()-3].unicode()==1080) //1080-и
            {
                if(tmpMest=="ми")
                {
                    ukrSent[k].value[ukrSent[k].value.size()-1].unicode()=1086; //1086-о
                    ukrSent[k].value[ukrSent[k].value.size()-2].unicode()=1084; //1084-м
                }
            }
            if(ukrSent[k].value[ukrSent[k].value.size()-3].unicode()==1072) //1072-a
            {
                if(tmpMest=="я")
                {
                    ukrSent[k].value[ukrSent[k].value.size()-2].unicode()=1102; //1102-ю
                    ukrSent[k].value.remove(ukrSent[k].value.size()-1,1);
                }
            }
        }

        //qDebug()<<ukrSent[k].value<<" : "<<ukrSent[k].part<<endl;

        //ПРИЛАГАТЕЛЬНЫЕ
        if(ukrSent[k].part==3)
        {
            if (k!=0 && ukrSent[k-1].part!=3)
                countOfPril=0;
            countOfPril++;
            int tmpNounIndex=0;
            if(k!=ukrSent.size()-1)
                tmpNounIndex=findRusN(ukrSent,k+1,1);
            QString tmpNoun=ukrSent[tmpNounIndex].value;
            QString tmpPr="";
            int tmpPrInd=0;
            int tmpVerInd=0;
            if(k-countOfPril>=0)
            {
                tmpPrInd=findRusN(ukrSent,k-countOfPril,7);
                tmpVerInd=findRusN(ukrSent,k-countOfPril,2);
                tmpPr=ukrSent[tmpPrInd].value;
            }

            if(ukrSent[tmpNounIndex].part==1)
            {
                if(tmpNoun[tmpNoun.size()-1]=='i')
                {
                    if(ukrSent[k].value[ukrSent[k].value.size()-2]!='i') //1086-о
                    {
                        ukrSent[k].value[ukrSent[k].value.size()-2]='i';
                        ukrSent[k].value.remove(ukrSent[k].value.size()-1,1);
                    }
                    else
                    {
                        ukrSent[k].value[ukrSent[k].value.size()-2].unicode()=1086;
                        ukrSent[k].value[ukrSent[k].value.size()-1].unicode()=1111; //1111-i c 2мя точками =Р
                    }
                }
                if(ukrSent[tmpPrInd].part==7)
                {
                    if(tmpPr=="про")
                    {
                        if(tmpNoun[tmpNoun.size()-1]=='i')
                        {
                            if(ukrSent[k].value[ukrSent[k].value.size()-2].unicode()!=1086)
                            {
                               ukrSent[k].value[ukrSent[k].value.size()-1].unicode()=1080; //1080-и
                               ukrSent[k].value+="х";
                               //qDebug()<<ukrSent[k].value<<endl;
                            }
                            else
                                ukrSent[k].value+="x";
                        }
                    }
                }
                if(ukrSent[tmpVerInd].part==2)
                {
                            if(ukrSent[k].value[ukrSent[k].value.size()-2].unicode()!=1086)
                            {
                               ukrSent[k].value[ukrSent[k].value.size()-2].unicode()=1086; //1086-o
                               ukrSent[k].value[ukrSent[k].value.size()-1].unicode()=1075; //1075-г
                               ukrSent[k].value+="о";
                               //qDebug()<<ukrSent[k].value<<endl;
                            }/*
                            else
                                ukrSent[k].value+="го";*/
                }
            }
        }

        //СУЩЕСТВИТЕЬНЫЕ
        if(ukrSent[k].part==1)
        {
            QString tmpPr="";
            int tmpPrInd=0;
            int tmpVerInd=0;
            if(k-countOfPril-1>=0)
            {
                tmpPrInd=findRusN(ukrSent,k-countOfPril-1,7);
                tmpVerInd=findRusN(ukrSent,k-countOfPril-1,2);
                tmpPr=ukrSent[tmpPrInd].value;
            }

            if(ukrSent[tmpPrInd].part==7)
            {
                if(tmpPr=="про")
                {
                    if(ukrSent[k].value[ukrSent[k].value.size()-1]!='i')
                        ukrSent[k].value[ukrSent[k].value.size()-1]='i';
                    ukrSent[k].value+="в";
                }
            }
            if(ukrSent[tmpVerInd].part==2)
            {
                if(ukrSent[k].value[ukrSent[k].value.size()-2].unicode()!=1086)
                {
                   ukrSent[k].value[ukrSent[k].value.size()-2].unicode()=1086; //1086-o
                   ukrSent[k].value[ukrSent[k].value.size()-1].unicode()=1075; //1075-г
                   ukrSent[k].value+="о";
                   //qDebug()<<ukrSent[k].value<<endl;
                }
            }
        }

        //МЕСТОИМЕНИЯ
        if(ukrSent[k].part==5)
        {
            QString tmpPr="";
            int tmpPrInd=0;
            int tmpNounIndex=findRusN(ukrSent,k+1,1);
            if(k-countOfPril>=0)
            {
                tmpPrInd=findRusN(ukrSent,k-countOfPril,7);
                tmpPr=ukrSent[tmpPrInd].value;
            }


            if(ukrSent[tmpPrInd].part==7)
            {
                if(ukrSent[k].value=="це")
                {
                    if(tmpPr=="за")
                    {
                        if(sent[tmpNounIndex][sent[tmpNounIndex].size()-1].unicode()==1080 || sent[tmpNounIndex]=="слова") //1080-и
                            ukrSent[k].value[ukrSent[k].value.size()-1]='i';
                    }
                }
            }
        }

        tmpUkr=tmpUkr+ukrSent[k].value+' ';
        //qDebug()<<ukrSent[k].value;
    }



    tmpUkr[0]=tmpUkr[0].toUpper();
    tmpUkr+=".";
    return tmpUkr;
}




int Words::firstLetter(QString str,int index)
{
    int i=0;
    for(i=index;i<str.size();i++)
    {
        if(str[i]!=' ' && str[i]!=',')
            return i;
    }
    return index;
}

int Words::findRusN(QVector<MyWord> rusStr, int index, int wh)
{
    for(int i=index;i<rusStr.size();i++)
    {
        if(wh!=7 && rusStr[i].part==wh)
            return i;
        if(wh==7 && rusStr[i].part==wh && i==index)
            return i;
    }
    return index;
}

int Words::partOfRus(QString str) //1-сущ 2-глаг 3-прил 4-нар 5-мест 6-союз/част 7-предл
{
    //cout<<"Something wrong!!!"<<endl;
    int i=0;
    int size=str.size();
    if (size!=0)
    {
    if(str=="я" || str=="мы" || str=="меня" || str=="это")
        i=5;
    else
    if((str.size()==1 && str[size-1].unicode()==1080) || str=="тоже" || str=="что") //1080-и
        i=6;
    else
    if(str.size()<=2 && str[size-1].unicode()!=1080)
        i=7;
    else
    if(str[size-2].unicode()==1090 && str[size-1].unicode()==1100)//1100-ь 1090-т
        i=2;
    else
    if((str[size-2].unicode()==1086 || str[size-2].unicode()==1099 || str[size-2].unicode()==1080) && str[size-1].unicode()==1081)//1086-о 1081-й 1099-ы
        i=3;
    else
    if((str[size-2].unicode()==1085 && str[size-1].unicode()==1086) || str=="всегда") //1085-н 1086-о
        i=4;
    else
        i=1;
    }

    return i;
}


QString Words::resetToDef(QString str, int lan)
{
    QString strTmp="";
    int count=0;
    if(lan==2)
    {
        for(int j=0;j<listOfRus.size();j++)
        {
            for(int i=0;i<str.size();i++)
            {
                if ((i==0 && str[i]==listOfRus[j][i]) || (str[i]==listOfRus[j][i] && str[i-1]==listOfRus[j][i-1]))
                    count++;
                else
                    break;
            }
            if((str.size()>3 && count>=2)|| (str.size()==3 && count>=2 && listOfRus[j].size()<=3) || (str.size()>=1 && str.size()<3 && count>=1 && listOfRus[j].size()<3))
            {
                if(str!="что" && str!="это" && str!="друг")
                {
                    strTmp=listOfRus[j];
                }
                else
                    return str;
                return strTmp;
            }
            count=0;
        }
    }
    return str;
}

QString Words::delAllSpAfWord(QString str)
{
    int si=str.size();
    while(str[si-1]==' ' || str[si-1]=='.')
    {
            str.remove(si-1,1);
            si--;
    }
    return str;
}

Words::~Words()
{}
