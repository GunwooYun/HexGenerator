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

    // connect(ui->te_HexValue, SIGNAL(textChanged()), this, SLOT(changeInput(QString)));
    // connect(ui->te_HexValue, &QTextEdit::textChanged, this, &MainWindow::changeInput);

    ui->rbtn_GenHex->setChecked(true);
    this->nMode = 0;

    ui->label_InputLen->clear();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getHexValue(void)
{
    QString strInput = ui->te_HexValue->toPlainText();

    Hex hex(strInput);

    if(nMode == 0)
    {
         hex.GenHexValue();
    }
    else if(nMode == 1)
    {
        hex.Put0x();
    }
    else /* nMode == 2 */
    {
        hex.Drop0x();
    }
    ui->label_InputLen->setText(QString("%1 Bytes").arg(hex.GetHexLen()));

    ui->te_HexValue->setText(hex.GetHexValue());
}

void MainWindow::switchMode()
{
    // ui->te_HexValue->clear();
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
}
/*
void MainWindow::changeInput()
{
    QString strInputValue = ui->te_HexValue->toPlainText();
    int nInputLength = strInputValue.length();
    ui->label_InputLen->setText(QString("%1").arg(nInputLength));
}
*/
