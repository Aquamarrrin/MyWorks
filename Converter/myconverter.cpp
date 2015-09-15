#include "myconverter.h"
#include <math.h>
#include <QFile>
#include <QTextStream>

MyConverter::MyConverter()
{
    QFile myFile("D:\\Qt\\Qt5.1.1\\Tools\\QtCreator\\bin\\Converter\\nums.txt");
    if(!myFile.open(QFile::ReadOnly | QFile::Text))
    {

    }
    QTextStream myText(&myFile);
    while (myText.atEnd() == false)
    {
        QString strTxt=myText.readLine();
        fillMap(strTxt);
    }
    myFile.close();

    ndsValue=18;

}



void MyConverter::changeNds(int newValue)
{
    ndsValue=newValue;
}


void MyConverter::fillMap(QString str)
{
    int i=firstLetter(str,0);
    int num;
    QString tmp="";
    while(str[i]!=' ' && str[i]!='-' && i!=str.size())
    {
        tmp+=str[i];
        i++;
    }
    num=tmp.toInt();
    tmp="";
    i=firstLetter(str,i+1);
    if(str[i]=='-')
        i=firstLetter(str,i+1);
    while(i<str.size())
    {
        tmp+=str[i];
        i++;
    }
    convNum[num]=tmp;
}



QString MyConverter::finalConvert(QString str)
{
    int i=0;
    while(str[i]!=',' && str[i]!='.' && i<str.size()) i++;
    if(i!=0) str[i]='.';
    if(i==str.size()-1) str+="00";

    float num=str.toDouble();
    float j=(num*ndsValue);
    QString tmp=str;
    QString nds=QString::number(j/100,'f',2);
    QString sum=QString::number(num+j/100,'f',2);
    tmp=tmp+" "+rubles(str,i-1)+" ("+showNums(str)+"), \nкроме того НДС("+QString::number(ndsValue)+"%) " + nds+" ("+showNums(nds)+"), \nа всего с НДС("+QString::number(ndsValue)+"%) "+sum+" ("+showNums(sum)+")";


    return tmp;
}

QString MyConverter::showNums(QString str)
{
    QString tmp="";
    QString tmp2="";
    QString tmp3="";
    int numsCount=0;
    int num;
    int i=firstLetter(str,0);
    int j=0;
    while(str[i].isNumber() && i!=str.size())
    {
        tmp2+=str[i];
        numsCount++;
        i++;
    }
    num=tmp2.toInt();
    tmp3=tmp2.mid(0,numsCount%3);
    tmp2.remove(0,numsCount%3);
    tmp+=tmpNums(tmp3);
    tmp+=" ";
    if (tmp2.size()!=0)
    {
        for (int k=numsCount%3;k<numsCount;k+=3)
        {
            if(k!=0)
            {
                QCharRef a=tmp3[tmp3.size()-1];
                if(numsCount-k==3 && num%1000000!=0 && num%1000000000!=0)
                {
                    if(a=='5' || a=='6' || a=='7' || a=='8' || a=='9' || a=='0' || (tmp3.size()-1!=0 && tmp3[tmp3.size()-2]=='1'))
                        tmp+="тысяч ";
                    else
                    if(a=='1')
                        tmp+="тысячa ";
                    else
                    if(a=='2' || a=='3' || a=='4' )
                        tmp+="тысячи ";
                }
                if(numsCount-k==6 && num%1000000000!=0)
                {
                    if(a=='5' || a=='6' || a=='7' || a=='8' || a=='9' || a=='0' || (tmp3.size()-1!=0 && tmp3[tmp3.size()-2]=='1'))
                        tmp+="миллионов ";
                    else
                        if(a=='1')
                            tmp+="миллион ";
                    else
                    if(a=='2' || a=='3' || a=='4')
                       tmp+="миллиона ";
                }
                if(numsCount-k==9)
                {
                    if(a=='5' || a=='6' || a=='7' || a=='8' || a=='9' || a=='0' || (tmp3.size()-1!=0 && tmp3[tmp3.size()-2]=='1'))
                        tmp+="миллиардов ";
                    else
                    if(a=='1')
                        tmp+="миллиард ";
                    else
                    if(a=='2' || a=='3' || a=='4' )
                        tmp+="миллиарда ";
                }
            }
            tmp3=tmp2.mid(0,3);
            tmp2.remove(0,3);
            tmp+=tmpNums(tmp3);
        }
    }

    if(tmp3.size()!=0)
    {
        tmp=tmp+rubles(tmp3,tmp3.size()-1)+", ";
    }
    tmp2="";
    i++;
    if (i!=str.size())
    {
        while(i<str.size() && j<2)
        {
            tmp2+=str[i];
            j++;
            i++;
        }
        if (j==1)
            tmp2+="0";
        if(j==0)
            tmp2="00";
    }
    else tmp2="00";

    tmp+=tmp2;
    tmp+=" копеек";

    return tmp;
}


QString MyConverter::tmpNums(QString str)
{
    QString tmp="";
    int num;
    int s=str.size();
    for (int k=1;k<=s;k++)
    {
        num=str.toInt();
        if(num!=0)
        {
            int someV=num/pow(10,s-k);
            int keyN=pow(10,s-k)*(someV);
            if(keyN==10)
            {
                keyN=num;
                tmp+=convNum[keyN];
                tmp+=" ";
                break;
            }
            tmp+=convNum[keyN];
            tmp+=" ";
        }
        str.remove(0,1);

    }
    return tmp;
}


QString MyConverter::rubles(QString str, int i)
{
    if(str[i]=='5' || str[i]=='6' || str[i]=='7' || str[i]=='8' || str[i]=='9' || str[i]=='0' || (i-1>=0 && str[i-1]=='1'))
        return "рублей";
    else
        if(str[i]=='2' || str[i]=='3' || str[i]=='4')
            return "рубля";
    else
            if(str[i]=='1')
                return "рубль";
}


int MyConverter::firstLetter(QString str,int index)
{
    int i=0;
    for(i=index;i<str.size();i++)
    {
        if(str[i]!=' ')
            return i;
    }
    return index;
}


MyConverter::~MyConverter()
{}
