#ifndef HEX_H
#define HEX_H

#include <QString>
#include <QChar>

#include <QRandomGenerator>

class Hex
{
private:
    QString strInputValue; /* User input hex value */
    QString strHexValue;
    int nReqLen; /* User require hex value length */
    // bool bWrongInputFlag = false;
    int nMode;

    bool isStringHex(void);
    bool isNumber(void); /* Check input has only numbers */

public:
    // Hex(int nMode = 0, QString strInputValue = "");
    Hex(QString strInputValue = "");
    void GenHexValue();
    void Put0x();
    void Drop0x();
    QString GetHexValue();
    int GetHexLen();
};

#endif // HEX_H
