#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "hex.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btn_Get, SIGNAL(clicked()), this, SLOT(getHexValue()));
    connect(ui->rbtn_GenHex, SIGNAL(clicked()), this, SLOT(switchMode()));
    connect(ui->rbtn_Put0x, SIGNAL(clicked()), this, SLOT(switchMode()));
    connect(ui->rbtn_Drop0x, SIGNAL(clicked()), this, SLOT(switchMode()));
    // connect(ui->btn_putZeroX, SIGNAL(clicked()), this, SLOT(PutZeroX()));
    // connect(ui->btn_delZeroX, SIGNAL(clicked()), this, SLOT(DelZeroX()));
    // connect(ui->btn_ClearTextEditAbove, SIGNAL(clicked()), this, SLOT(clearTextEditAbove()));
    // connect(ui->btn_ClearTextEditBelow, SIGNAL(clicked()), this, SLOT(clearTextEditBelow()));

    // connect( mDText, SIGNAL(textChanged(QString)), this, SLOT(changeD(QString)));

    ui->rbtn_GenHex->setChecked(true);
    this->nMode = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getHexValue(void)
{
    QString strInput = ui->te_HexValue->toPlainText();
    Hex hex(this->nMode, strInput);

    ui->te_HexValue->setText(hex.GenRandomNumber());
#if 0
    int nMode;
    if(ui->rbtn_GenHex->isChecked())
    {
        nMode = 0;
    }
    else if(ui->rbtn_Put0x->isChecked())
    {
        nMode = 1;
    }
    else
    {
        nMode = 2;
    }
    // int nLen = ui->le_RandLen->text().toInt();
    Hex hex(nLen);

    strHexValue = hex.GenRandomNumber();

    ui->te_outputRandom->setText(strHexValue);

    if(nMode == 0)
    {
        ui->te_HexValue->setText(QString("Mode %1: Generate Hex").arg(nMode));
    }
    else if(nMode == 1)
    {
        ui->te_HexValue->setText(QString("Mode %1: put 0x").arg(nMode));
    }
    else
    {
        ui->te_HexValue->setText(QString("Mode %1: drop 0x").arg(nMode));
    }
#endif
}

void MainWindow::switchMode()
{
    ui->te_HexValue->clear();
    if(ui->rbtn_GenHex->isChecked())
    {
        nMode = 0;
        // ui->te_HexValue->setText(QString("Mode %1: Generate Hex").arg(nMode));
    }
    else if(ui->rbtn_Put0x->isChecked())
    {
        nMode = 1;
        // ui->te_HexValue->setText(QString("Mode %1: put 0x").arg(nMode));
    }
    else
    {
        nMode = 2;
        // ui->te_HexValue->setText(QString("Mode %1: drop 0x").arg(nMode));
    }

}
#if 0
void MainWindow::PutZeroX(void)
{
    QString strInputHexValue = ui->te_inputRandom->toPlainText();
    Hex hex(strInputHexValue);

    if(hex.isWrongInput())
    {
        ui->te_outputRandom->setText(QString("Wrong"));
    }
    else
    {
        ui->te_outputRandom->setText(hex.PutZeroX());
    }
}

void MainWindow::DelZeroX(void)
{
    // ui->te_inputRandom->clear();
    QString strInputHexValue = ui->te_inputRandom->toPlainText();
    Hex hex(strInputHexValue);

    QString strInputHex = hex.DropZeroX();
    ui->te_outputRandom->setText(strInputHex);
}

void MainWindow::clearTextEditAbove(void)
{
    ui->te_inputRandom->clear();
}

void MainWindow::clearTextEditBelow(void)
{
    ui->te_outputRandom->clear();
}
#endif
