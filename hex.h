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
public:
    // Hex();
    Hex(QString strInputRandom = ""){ this->strHexValue = strInputRandom; }
    Hex(int nReqLen = 0){ this->nReqLen = nReqLen; }
    // Hex(QString strInputRandom = "", int nReqLen = 0){
    //     this->strHexValue = strInputRandom;
    //     this->nReqLen = nReqLen;
    // }
    QString GenRandomNumber();
    QString PutZeroX();
    QString DropZeroX();
};

#endif // HEX_H
