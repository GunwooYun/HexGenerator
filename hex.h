#ifndef HEX_H
#define HEX_H

#include <QString>
#include <QChar>

#include <QRandomGenerator>

class Hex
{
private:
    QString strHexValue;
    int nReqLen;
    bool bWrongInputValueFlag = false;
    bool chkInputHealthy();
public:
    Hex(QString strInputRandom = "");
    Hex(int nReqLen = 0);
    QString GenRandomNumber();
    QString PutZeroX();
    QString DropZeroX();
    bool isWrongInput();

};

#endif // HEX_H
