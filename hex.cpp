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

    if(nReqLen == 0) return strRandom;

    for(int i = 0; i < (nReqLen / 4) + 1; i++)
    {
        nRandomValue32 = pRandomGenerator->generate(); /* generate 32bit random number */

        for(int j = 0; j < 4; j++)
        {
            bytes[j] = (nRandomValue32 >> (24 - (j * 8))) & 0xFF;
            strRandom.append(QString("0x")).append(QString("%1, ").arg((long)bytes[j], 2, 16, QChar('0')).toUpper()); nCount++;
            if(nCount >= nReqLen)
            {
                flagFinish = true;
            }
        }
        if(flagFinish) break;
    }

    strRandom.chop(2); /*  Eliminate comma(,) + space */

    return strRandom;
}

QString Hex::PutZeroX()
{

    return strRandom;

}

QString Hex::DropZeroX()
{

}
