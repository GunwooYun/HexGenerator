#ifndef HEX_H
#define HEX_H

#include <QString>
#include <QChar>

#include <QRandomGenerator>

class Hex
{
private:
    // QString strInputHex;
    QString strRandom;
    int nReqLen;
public:
    // Hex();
    Hex(QString strInputRandom = ""){ this->strRandom = strInputRandom; }
    Hex(int nReqLen = 0){ this->nReqLen = nReqLen; }
    QString GenRandomNumber();
    QString PutZeroX();
    QString DropZeroX();
};

#endif // HEX_H
