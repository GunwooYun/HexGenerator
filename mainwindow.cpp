#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "hex.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btn_show, SIGNAL(clicked()), this, SLOT(getInputValue()));
    connect(ui->btn_putZeroX, SIGNAL(clicked()), this, SLOT(PutZeroX()));
    connect(ui->btn_delZeroX, SIGNAL(clicked()), this, SLOT(DelZeroX()));
    connect(ui->btn_ClearTextEditAbove, SIGNAL(clicked()), this, SLOT(clearTextEditAbove()));
    connect(ui->btn_ClearTextEditBelow, SIGNAL(clicked()), this, SLOT(clearTextEditBelow()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getInputValue(void)
{
    int nLen = ui->le_RandLen->text().toInt();
    Hex hex(nLen);

    strHexValue = hex.GenRandomNumber();

    ui->te_outputRandom->setText(strHexValue);

}

void MainWindow::PutZeroX(void)
{
    QString strInputHexValue = ui->te_inputRandom->toPlainText();
    Hex hex(strInputHexValue);

    QString strInputHex = hex.PutZeroX();

    ui->te_outputRandom->setText(strInputHex);

}

void MainWindow::DelZeroX(void)
{
    ui->te_inputRandom->clear();
}

void MainWindow::clearTextEditAbove(void)
{
    ui->te_inputRandom->clear();
}

void MainWindow::clearTextEditBelow(void)
{
    ui->te_outputRandom->clear();
}
