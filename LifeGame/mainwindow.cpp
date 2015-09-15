#include "mainwindow.h"
#include "myfield.h"
#include <QLayout>
#include <QLabel>
#include <QColorDialog>


MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout* layoutH=new QHBoxLayout;
    QVBoxLayout* layoutV=new QVBoxLayout;

    MyField* field = new MyField;
    field->setMinimumSize(500,500);
    layoutH->addWidget(field);

    layoutH->addLayout(layoutV);

    dl = new QColorDialog();

    QLabel* lbl1=new QLabel("Set universe size");
    lbl1->setFixedHeight(10);
    layoutV->addWidget(lbl1);

    spinBox1 = new QSpinBox;
    spinBox1->setFixedSize(90,30);
    spinBox1->setValue(50);
    spinBox1->setMaximum(50);
    spinBox1->setMinimum(5);
    layoutV->addWidget(spinBox1);
    QObject::connect(spinBox1,SIGNAL(valueChanged(int)),field,SLOT(changeUniverseSize(int)));

    QLabel* lbl2=new QLabel("Set interval size");
    lbl2->setFixedHeight(10);
    layoutV->addWidget(lbl2);

    spinBox2 = new QSpinBox;
    spinBox2->setFixedSize(90,30);
    spinBox2->setValue(50);
    spinBox2->setMaximum(1000);
    spinBox2->setMinimum(10);
    layoutV->addWidget(spinBox2);
    QObject::connect(spinBox2,SIGNAL(valueChanged(int)),field,SLOT(changeInterval(int)));

    btnStart = new QPushButton("Start");
    btnStart->setFixedSize(90,30);
    QObject::connect(btnStart,SIGNAL(clicked()),field,SLOT(startGame()));
    layoutV->addWidget(btnStart);

    btnStop = new QPushButton("Stop");
    btnStop->setFixedSize(90,30);
    QObject::connect(btnStop,SIGNAL(clicked()),field,SLOT(stopGame()));
    layoutV->addWidget(btnStop);

    btnClear = new QPushButton("Clear");
    btnClear->setFixedSize(90,30);
    QObject::connect(btnClear,SIGNAL(clicked()),field,SLOT(clearUniverse()));
    layoutV->addWidget(btnClear);

    setColor = new QPushButton("Set color");
    setColor->setFixedSize(90,30);
    QObject::connect( setColor,SIGNAL(clicked()),this,SLOT(setCellColor()));
    QObject::connect(dl,SIGNAL(colorSelected(QColor)),field,SLOT(changeColor(QColor)));
    layoutV->addWidget( setColor);

    btnNewRules=new QPushButton("New Rules");
    btnNewRules->setFixedSize(90,30);
    QObject::connect(btnNewRules,SIGNAL(clicked()),field,SLOT(newRules()));
    layoutV->addWidget(btnNewRules);

    ResetRules=new QPushButton("Reset Rules");
    ResetRules->setFixedSize(90,30);
    QObject::connect(ResetRules,SIGNAL(clicked()),field,SLOT(resetRules()));
    layoutV->addWidget(ResetRules);


    this->setLayout(layoutH);
}

void MainWindow::setCellColor()
{
    dl->exec();

}

MainWindow::~MainWindow()
{}
