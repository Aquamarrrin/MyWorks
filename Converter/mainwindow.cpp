#include "mainwindow.h"
#include <QLayout>
#include <QLabel>
#include <qvalidator.h>


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    this->setMaximumHeight(250);
    this->setMinimumWidth(500);
    QHBoxLayout* layoutH=new QHBoxLayout;
    QVBoxLayout* layoutV=new QVBoxLayout;
    number = new QLineEdit;
    label=new QTextEdit;
    nds= new QSpinBox;

    QLabel* lblMoney = new QLabel("Введите нужную сумму в \nрублях:");
    lblMoney->setFixedWidth(150);
    layoutV->addWidget(lblMoney);


    QRegExp regExp("[0-9]{,10}[,|.][0-9]{,2}");
    number->setValidator(new QRegExpValidator(regExp, number));
    number->setFixedSize(150,30);
    layoutV->addWidget(number);

    QLabel* lblNDS = new QLabel("Введите НДС:");
    lblNDS->setFixedWidth(150);
    layoutV->addWidget(lblNDS);

    nds->setFixedSize(150,30);
    nds->setMaximum(100);
    nds->setValue(18);
    nds->setSuffix("%");
    layoutV->addWidget(nds);
    QObject::connect(nds,SIGNAL(valueChanged(int)),this,SLOT(changeNdsValue(int)));

    layoutH->addLayout(layoutV);

    btnConvert= new QPushButton("->CONVERT->");
    btnConvert->setFixedSize(100,50);
    layoutH->addWidget(btnConvert);
    QObject::connect(btnConvert,SIGNAL(clicked()),this,SLOT(showConv()));

    label->setFontPointSize(10);
    label->setText("Здесь будет выводиться введённое вами значение.");
    layoutH->addWidget(label);

    this->setLayout(layoutH);

}

void MainWindow::showConv()
{
    label->setText(conv.finalConvert(number->text()));
}

void MainWindow::changeNdsValue(int newV)
{
    conv.changeNds(newV);
}


MainWindow::~MainWindow()
{

}
