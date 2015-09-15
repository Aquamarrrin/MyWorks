#include "myfield.h"
#include <QPainter>
#include <QTimer>
#include <qmath.h>
#include <QMouseEvent>
#include <QLayout>

MyField::MyField(QWidget *parent) :
    QWidget(parent),
    timer(new QTimer(this)),
    universeSize(50)
{
    timer->setInterval(50);
    mainColor = "#F00";
    newRu=false;
    universe = new bool*[(universeSize + 2)];
    for(int i=0;i<universeSize + 2;i++)
        universe[i]=new bool[universeSize + 2];
    next = new bool*[(universeSize + 2)];
    for(int i=0;i<universeSize + 2;i++)
        next[i]=new bool[universeSize + 2];
    connect(timer, SIGNAL(timeout()), this, SLOT(newGeneration()));
    clearUniverse();

}

void MyField::startGame()
{
    timer->start();
}

void MyField::stopGame()
{
    timer->stop();
}

void MyField::changeUniverseSize(int newSize)
{
    universeSize=newSize;
    update();
}

void MyField::clearUniverse()
{
    for(int k=1; k <= universeSize; k++)
        for(int j=1; j <= universeSize; j++)
            universe[k][j] = false;
    update();
}

void MyField::changeInterval(int newInterval)
{
    timer->setInterval(newInterval);
}

void MyField::changeColor(QColor newColor)
{
    mainColor=newColor;
    update();
}

void MyField::resetRules()
{
    newRu=false;
    update();
}

void MyField::newRules()
{
    for(int k=1; k <= universeSize; k++) {
        for(int j=1; j <= universeSize; j++)
        {
            if(newFig(k,j))
                setFig(k,j);
            else
                if(newGlade(k,j))
                    setGlade(k,j);
        }
    }
    newRu=true;
    update();
}

bool MyField::newGlade(int k, int j)
{
    int afJ,befJ,afK,befK;
    int power = 0;
    if (j==universeSize)
        afJ=1;
    else
        afJ=j+1;
    if(k==universeSize)
        afK=1;
    else
        afK=k+1;
    if(j==1)
        befJ=universeSize;
    else
        befJ=j-1;
    if(k==1)
        befK=universeSize;
    else
        befK=k-1;
    power += universe[afK][j];
    power += universe[befK][j];
    power += universe[k][afJ];
    power += universe[k][befJ];
    power += universe[afK][befJ];
    power += universe[befK][afJ];
    power += universe[befK][befJ];
    power += universe[afK][afJ];
    if ((universe[k][j] == false) && (power == 5) &&
            ((universe[befK][befJ]==0 && universe[befK][afJ]==0 && universe[afK][befJ]!=universe[afK][afJ])
             || (universe[befK][befJ]!=universe[befK][afJ] && universe[afK][befJ]==0 && universe[afK][afJ]==0)))
        return true;
    return false;
}


void MyField::setGlade(int k, int j)
{
    int afJ,befJ,afK,befK;
    if (j==universeSize)
        afJ=1;
    else
        afJ=j+1;
    if(k==universeSize)
        afK=1;
    else
        afK=k+1;
    if(j==1)
        befJ=universeSize;
    else
        befJ=j-1;
    if(k==1)
        befK=universeSize;
    else
        befK=k-1;

    if(universe[befK][befJ]==1)
    {
        universe[afK][j]=0;
        universe[afK][befJ]=1;
    }
    else
        if(universe[afK][afJ])
        {
            universe[befK][j]=0;
            universe[befK][afJ]=1;
        }
    else
        if(universe[afK][befJ])
        {
            universe[befK][j]=0;
            universe[befK][befJ]=1;
        }
    else
            if(universe[befK][afJ])
            {
                universe[afK][j]=0;
                universe[afK][afJ]=1;
            }
}

bool MyField::newFig(int k, int j)
{
    int afJ,befJ,afK,befK;
    int power = 0;
    int state =0;
    if (j==universeSize)
        afJ=1;
    else
        afJ=j+1;
    if(k==universeSize)
        afK=1;
    else
        afK=k+1;
    if(j==1)
        befJ=universeSize;
    else
        befJ=j-1;
    if(k==1)
        befK=universeSize;
    else
        befK=k-1;
    power += universe[afK][j];
    state += universe[befK][j];
    power += universe[k][afJ];
    state += universe[k][befJ];
    state += universe[afK][befJ];
    state += universe[befK][afJ];
    state += universe[k][afJ+1];
    state += universe[afK][afJ+1];
    state += universe[afK+1][j];
    state += universe[afK+1][afJ];
    power += universe[afK][afJ];
    if ((universe[k][j] == true) && (power == 3) && (!state))
        return true;
    return false;
}

void MyField::setFig(int k, int j)
{
    int afJ,befJ,afK,befK;
    if (j==universeSize)
        afJ=1;
    else
        afJ=j+1;
    if(k==universeSize)
        afK=1;
    else
        afK=k+1;
    if(j==1)
        befJ=universeSize;
    else
        befJ=j-1;
    if(k==1)
        befK=universeSize;
    else
        befK=k-1;
    universe[befK][befJ]=1;
    universe[befK][j]=1;
    universe[befK][afJ]=1;
    universe[befK][afJ+1]=1;
    universe[k][befJ]=1;
    universe[k][afJ+1]=1;
    universe[afK][befJ]=1;
    universe[afK][afJ+1]=1;
    universe[afK+1][befJ]=1;
    universe[afK+1][j]=1;
    universe[afK+1][afJ]=1;
    universe[afK+1][afJ+1]=1;
    universe[afK][j]=0;
    universe[k][afJ]=0;
    universe[afK][afJ]=0;
    universe[k][j]=0;
}

bool MyField::isAlive(int k, int j)
{
    int afJ,befJ,afK,befK;
    int power = 0;
    if (j==universeSize)
        afJ=1;
    else
        afJ=j+1;
    if(k==universeSize)
        afK=1;
    else
        afK=k+1;
    if(j==1)
        befJ=universeSize;
    else
        befJ=j-1;
    if(k==1)
        befK=universeSize;
    else
        befK=k-1;
    power += universe[afK][j];
    power += universe[befK][j];
    power += universe[k][afJ];
    power += universe[k][befJ];
    power += universe[afK][befJ];
    power += universe[befK][afJ];
    power += universe[befK][befJ];
    power += universe[afK][afJ];
    if (((universe[k][j] == true) && (power == 2)) || (power == 3))
        return true;
    return false;
}
void MyField::newGeneration()
{
    int notChanged=0;
    for(int k=1; k <= universeSize; k++) {
        for(int j=1; j <= universeSize; j++) {
            next[k][j] = isAlive(k, j);
            if(next[k][j] == universe[k][j])
                notChanged++;
            }
    }
    if(notChanged == universeSize*universeSize) {
        stopGame();
        return;
    }
    for(int k=1; k <= universeSize; k++) {
        for(int j=1; j <= universeSize; j++) {
            universe[k][j] = next[k][j];
        }
    }
    if(newRu==true)
        newRules();
    update();
}
void MyField::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    paintGrid(p);
    paintUniverse(p);
}
void MyField::mousePressEvent(QMouseEvent *e)
{
    cellW = (double)width()/universeSize;
    cellH = (double)height()/universeSize;
    int k = floor(e->y()/cellH)+1;
    int j = floor(e->x()/cellW)+1;
    universe[k][j] = !universe[k][j];
    update();
}
void MyField::mouseMoveEvent(QMouseEvent *e)
{
    if(e->y()<=this->height() && e->x()<=this->width() && e->y()>=0 && e->x()>=0)
    {
       cellW = (double)width()/universeSize;
       cellH = (double)height()/universeSize;
       int k = floor(e->y()/cellH)+1;
       int j = floor(e->x()/cellW)+1;
       if(!universe[k][j])
       {
           universe [k][j]= !universe[k][j];
           update();
       }
    }
}

void MyField::paintGrid(QPainter &p)
{
    cellW = (double)width()/universeSize;
    cellH = (double)height()/universeSize;
    QRect borders(0, 0, width()-1, height()-1);
    QColor gridColor = mainColor;
    gridColor.setAlpha(10);
    p.setPen(gridColor);
    for(double k = cellW; k <= width(); k += cellW)
        p.drawLine(k, 0, k, height());
    for(double k = cellH; k <= height(); k += cellH)
        p.drawLine(0, k, width(), k);
    p.drawRect(borders);
}
void MyField::paintUniverse(QPainter &p)
{
    cellW = (double)width()/universeSize;
    cellH = (double)height()/universeSize;
    for(int k=1; k <= universeSize; k++) {
        for(int j=1; j <= universeSize; j++) {
            if(universe[k][j] == true) {
                double left =(cellW*j-cellW);
                double top =(cellH*k-cellH);
                QRectF r(left, top, cellW, cellH);
                p.fillRect(r, QBrush(mainColor));
            }
        }
    }
}

MyField::~MyField()
{
    for(int i = 0; i < universeSize + 2; i++)
        delete [] universe[i];
    delete [] universe;
    for(int i=0;i<universeSize + 2;i++)
        delete [] next[i];
    delete [] next;
}
