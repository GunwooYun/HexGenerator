#include "hex.h"
#include <QRandomGenerator>

QString Hex::GenRandomNumber()
{
    // QString strRandomValue;
    unsigned char bytes[4] = {0x00, };
    quint32 nRandomValue32 = 0;
    int nCount = 0;
    bool flagFinish = false;

    QRandomGenerator *pRandomGenerator = QRandomGenerator::global();

    if(nReqLen == 0) return strHexValue;

    for(int i = 0; i < (nReqLen / 4) + 1; i++)
    {
        nRandomValue32 = pRandomGenerator->generate(); /* generate 32bit random number */

        for(int j = 0; j < 4; j++)
        {
            bytes[j] = (nRandomValue32 >> (24 - (j * 8))) & 0xFF;
            strHexValue.append(QString("0x")).append(QString("%1, ").arg((long)bytes[j], 2, 16, QChar('0')).toUpper()); nCount++;
            if(nCount >= nReqLen)
            {
                flagFinish = true;
                break;
            }
        }
        if(flagFinish) break;
    }

    strHexValue.chop(2); /*  Eliminate comma(,) + space */

    return strHexValue;
}

QString Hex::PutZeroX()
{
    QString strHexValue0x;
    // QString ret;
    // ret = QString("input length: %1").arg(strHexValue.length());
    nReqLen = strHexValue.length(); /* Input string length */

    if(nReqLen % 2) /* String length is odd */
    {
        strHexValue.append("0"); /* Put '0' */
        nReqLen += 1;
    }

    for(int i = 0; i < nReqLen; i += 2)
    {
        strHexValue0x.append("0x");
        strHexValue0x.append( strHexValue.mid(i, 2) );
        strHexValue0x.append(", ");
    }

    strHexValue0x.chop(2);

    return strHexValue0x;

}

QString Hex::DropZeroX()
{
    int nIndex = 0;
    QString strHexValueNo0x;
    QString strTemp;

    while(true){
        nIndex = strHexValue.indexOf("0x", nIndex, Qt::CaseInsensitive);
        if(nIndex < 0) break;
        nIndex += 2;
        strTemp = strHexValue.mid(nIndex, 2);
        if(strTemp.back() == ',')
        {
            strTemp.prepend("0");
            strTemp.chop(1);
        }
        strHexValueNo0x.append(strTemp);
    }

    return strHexValueNo0x;
}
