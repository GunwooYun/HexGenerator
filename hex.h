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

    bool isHexadecimal(void);
    bool isNumber(void);

public:
    Hex(int nMode = 0, QString strInputValue = "");
    void GenHexValue();
    void Put0x();
    void Drop0x();
    QString GetHexValue();
    int GetHexLen();
};

#endif // HEX_H
