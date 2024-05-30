#ifndef HEX_H
#define HEX_H

#include <QString>
#include <QChar>

#include <QRandomGenerator>

class Hex
{
private:
    // int nMode; /* Mode: Gen hex, Put '0x', Drop '0x' */
    QString strInputValue; /* User input hex value */
    QString strHexValue;
    int nReqLen; /* User require hex value length */
    // bool bWrongInputValueFlag = false;

    bool isHexadecimal(void);
    bool isNumber(void);

public:
    // Hex(QString strInputRandom = "");
    //Hex(int nMode = 0, int nReqLen = 0, QString strInputValue = "");
    Hex(int nMode = 0, QString strInputValue = "");
    void GenHexValue();
    void Put0x();
    void Drop0x();
    // bool isWrongInput();
    QString GetHexValue();

};

#endif // HEX_H
