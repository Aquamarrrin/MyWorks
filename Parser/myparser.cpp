#include "myparser.h"
#include <math.h>

MyParser::MyParser(QString filePath)
{
    fstream f;
    f.open(filePath.toStdString().c_str(),ios::in);
    if (f)
    {
        while (!f.eof())
        {
            char tmp[256];
            f.getline(tmp,256);
            progTxt.push_back(tmp);
        }
    }

    f.close();
}

int MyParser::firstLetter(QString str,int index)
{
    int i=0;
    for(i=index;i<str.size();i++)
    {
        if(str[i]!=' ')
            return i;
    }
    return index;
}

void MyParser::runProg()
{
    for(int i=0;i<progTxt.size();i++)
    {
        int tmp = firstLetter(progTxt[i],0);
        QString name;
        if(progTxt[i][tmp]==':')
        {
            tmp++;
            while(progTxt[i][tmp]!=' ' && tmp<progTxt[i].size())
            {
                name+=progTxt[i][tmp];
                tmp++;
            }
            loops[name]=i+1;
        }
    }
    doOperations(0,progTxt.size());

}


void MyParser::doOperations(int index,int size)
{
    if (index>size)
        size=progTxt.size();
    for(int i=index;i<size;i++)
    {
        int tmp = firstLetter(progTxt[i],0);
        if (progTxt[i][tmp]!=';')
        {
            if(progTxt[i][tmp]=='=')
            {
                newVar(progTxt[i], tmp+1);
            }
            if(progTxt[i][tmp]=='+')
            {
                operaton(progTxt[i],'+',tmp+1);
            }
            if(progTxt[i][tmp]=='-')
            {
                operaton(progTxt[i],'-',tmp+1);
            }
            if(progTxt[i][tmp]=='*')
            {
                operaton(progTxt[i],'*',tmp+1);
            }
            if(progTxt[i][tmp]=='/')
            {
                operaton(progTxt[i],'/',tmp+1);
            }

            if(progTxt[i][tmp]=='s' && progTxt[i][tmp+1]=='q')
            {
                sqrtV(progTxt[i],tmp+2);
            }
            if(progTxt[i][tmp]=='!')
            {
                coutThisVar(progTxt[i],tmp+1);
            }
            if(progTxt[i][tmp]=='.')
            {
                cinThisVar(progTxt[i],tmp+1);
            }
            if(progTxt[i][tmp]=='i' && progTxt[i][tmp+1]=='f')
            {
                condition(progTxt[i],tmp+2,i);
            }
        }
        if (i==progTxt.size())
            exit(0);
    }
}



void MyParser::operaton(QString str, char op, int index)
{
    //определяем переменные:
    int i=firstLetter(str, index);
    QString name1,name2, name3;
    while(str[i]!=' ')
    {
        name1+=str[i];
        i++;
    }
    if(varPr.value(name1,0)==0)
    {
            varPr[name1]=0;
    }
    i=firstLetter(str, i);
    while(str[i]!=' ')
    {
        name2+=str[i];
        i++;
    }
    if(varPr.value(name2,0)==0)
    {
            varPr[name2]=0;
    }
    i=firstLetter(str, i);
    while(str[i]!=' ' && i<str.size())
    {
        name3+=str[i];
        i++;
    }
    if(varPr.value(name3,0)==0)
    {
            varPr[name3]=0;
    }
    //далее сами операции:
    if(op=='+')
    {
        varPr[name3]=varPr[name1]+varPr[name2];
    }

    if(op=='-')
    {
        varPr[name3]=varPr[name1]-varPr[name2];
    }
    if(op=='*')
    {
        varPr[name3]=varPr[name1]*varPr[name2];
    }
    if(op=='/')
    {
        varPr[name3]=varPr[name1]/varPr[name2];
    }

}


void MyParser::sqrtV(QString str, int index)
{
    int i=firstLetter(str, index);
    QString name1,name2;
    while(str[i]!=' ')
    {
        name1+=str[i];
        i++;
    }
    if(varPr.value(name1,0)==0)
    {
            varPr[name1]=0;
    }
    i=firstLetter(str, i);
    while(str[i]!=' ' && i<str.size())
    {
        name2+=str[i];
        i++;
    }
    if(varPr.value(name2,0)==0)
    {
            varPr[name2]=0;
    }
    varPr[name2]=sqrt(varPr[name1]);

}


void MyParser::newVar(QString str, int index)
{
    int i=firstLetter(str, index);
    QString name,value;
    while(str[i]!=' ')
    {
        name+=str[i];
        i++;
    }
    i=firstLetter(str, i);
    while(i<str.size())
    {
        value+=str[i];
        i++;
    }
    varPr[name]=value.toFloat();
}


void MyParser::coutThisVar(QString str, int index)
{
    int i=firstLetter(str, index);
    QString name;
    while(str[i]!=' ' && i<str.size())
    {
        name+=str[i];
        i++;
    }
    if(varPr.value(name,0)==0)
    {
            varPr[name]=0;
    }
    cout<<name.toStdString().c_str()<<" = "<<varPr[name]<<endl;
}


void MyParser::cinThisVar(QString str, int index)
{
    int i=firstLetter(str, index);
    QString name;
    while(str[i]!=' ' && i<str.size())
    {
        name+=str[i];
        i++;
    }
    if(varPr.value(name,0)==0)
    {
            varPr[name]=0;
    }
    cout<<"Enter "<<name.toStdString().c_str()<<" :"<<endl;
    cin>>varPr[name];
}


void MyParser::condition(QString str, int index, int size)
{
    int i=firstLetter(str, index);
    bool cond=false;
    bool ok;
    QString name1,name2;
    float tmp;
    while(str[i]!=' ' && str[i]!='=' && str[i]!='!' && str[i]!='<' && str[i]!='>')
    {
        name1+=str[i];
        i++;
    }
    if(varPr.value(name1,0)==0)
    {
            varPr[name1]=0;
    }
    i=firstLetter(str, i);

    //УСЛОВИЯ:
    if(str[i]=='<'&& str[i+1]!='=')
    {
         i=firstLetter(str, i+1);
         while(str[i]!=' ')
         {
             name2+=str[i];
             i++;
         }
         tmp=name2.toFloat(&ok);
         if(!ok)
         {
             if(varPr.value(name2,0)==0)
             {
                     varPr[name2]=0;
             }
             cond=varPr[name1]<varPr[name2];
         }
         else
         {
             tmp=name2.toFloat();
             cond=varPr[name1]<tmp;
         }
    }
    else
    if(str[i]=='>'&& str[i+1]!='=')
    {
        i=firstLetter(str, i+1);
        while(str[i]!=' ')
        {
            name2+=str[i];
            i++;
        }
        tmp=name2.toFloat(&ok);
        if(!ok)
        {
            if(varPr.value(name2,0)==0)
            {
                    varPr[name2]=0;
            }
            cond=varPr[name1]>varPr[name2];
        }
        else
        {
            cond=varPr[name1]>tmp;
        }
    }
    else
    if(str[i]=='<' && str[i+1]=='=')
    {
        i=firstLetter(str, i+2);
        while(str[i]!=' ')
        {
            name2+=str[i];
            i++;
        }
        tmp=name2.toFloat(&ok);
        if(!ok)
        {
            if(varPr.value(name2,0)==0)
            {
                    varPr[name2]=0;
            }
            cond=varPr[name1]<=varPr[name2];
        }
        else
        {
            tmp=name2.toFloat();
            cond=varPr[name1]<=tmp;
        }
    }
    else
    if(str[i]=='>' && str[i+1]=='=')
    {
        i=firstLetter(str, i+2);
        while(str[i]!=' ')
        {
            name2+=str[i];
            i++;
        }
        tmp=name2.toFloat(&ok);
        if(!ok)
        {
            if(varPr.value(name2,0)==0)
            {
                    varPr[name2]=0;
            }
            cond=varPr[name1]>=varPr[name2];
        }
        else
        {
            tmp=name2.toFloat();
            cond=varPr[name1]>=tmp;
        }
    }
    else
    if(str[i]=='=' && str[i+1]=='=')
    {
        i=firstLetter(str, i+2);
        while(str[i]!=' ')
        {
            name2+=str[i];
            i++;
        }
        tmp=name2.toFloat(&ok);
        if(!ok)
        {
            if(varPr.value(name2,0)==0)
            {
                    varPr[name2]=0;
            }
            cond=varPr[name1]==varPr[name2];
        }
        else
        {
            tmp=name2.toFloat();
            cond=varPr[name1]==tmp;
        }
    }
    else
    if(str[i]=='!' && str[i+1]=='=')
    {
        i=firstLetter(str, i+2);
        while(str[i]!=' ')
        {
            name2+=str[i];
            i++;
        }
        tmp=name2.toFloat(&ok);
        if(!ok)
        {
            if(varPr.value(name2,0)==0)
            {
                    varPr[name2]=0;
            }
            cond=varPr[name1]!=varPr[name2];
        }
        else
        {
            tmp=name2.toFloat();
            cond=varPr[name1]!=tmp;
        }
    }
    else
        cond=varPr[name1];

    //ДЕЙСТВИЕ:
    if (cond)
    {
        i=firstLetter(str, i);
        name2="";
        while(str[i]!=' ' && i<str.size())
        {
            name2+=str[i];
            i++;
        }
        if(loops.value(name2,-1)==-1)
        {
            cout<<"ERROR. There is no such line in your program."<<endl;
        }
        else
           doOperations(loops[name2],size+1);
    }

}


void MyParser::shV()
{
    QMap<QString, float>::iterator i = varPr.begin();
    while (i != varPr.end()) {
        qDebug()<< i.key();
        qDebug()<<i.value();
        cout<<endl;
        ++i;
    }
}
