#ifndef MYFIELD_H
#define MYFIELD_H

#include <QWidget>
#include <QPushButton>
#include <QColor>
#include <QColorDialog>

class MyField : public QWidget
{
    Q_OBJECT
public:
    explicit MyField(QWidget *parent = 0);
    ~MyField();
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

signals:

public slots:
    void startGame();
    void stopGame();
    void clearUniverse();
    void changeUniverseSize(int newSize);
    void changeInterval(int newInterval);
    void changeColor(QColor newColor);
    void newRules();
    void resetRules();

private slots:
    void paintGrid(QPainter &p);
    void newGeneration();
    void paintUniverse(QPainter &p);

private:
    QColor mainColor;
    QTimer* timer;
    bool isAlive(int k, int j);
    bool newFig(int k, int j);
    bool newGlade(int k, int j);
    void setFig(int k, int j);
    void setGlade(int k, int j);
    bool** universe;
    bool** next;
    bool newRu;
    double cellW, cellH;
    int universeSize;

};

#endif // MYFIELD_H
