#include "hex.h"
#include <QRandomGenerator>

Hex::Hex(int nMode, QString strInput)
{
    this->strInputValue = strInput;
    this->nMode = nMode;

#if 0
    if(nMode == 0) /* Generate hex value */
    {
        if(isNumber())
        {
            nReqLen = this->strInputValue.toInt();
        }
        else
        {
            nReqLen = 0;
        }
    }
    else if(nMode == 1) /* Put prefix "0x" */
    {
        /* not yet.. */
    }
    else /* Drop "0x" */
    {
        /* not yet.. */
    }
#endif
}

bool Hex::isNumber(void)
{
    if(!strInputValue.contains('0') && !strInputValue.contains('1') && !strInputValue.contains('2') &&
       !strInputValue.contains('3') && !strInputValue.contains('4') && !strInputValue.contains('5') &&
       !strInputValue.contains('6') && !strInputValue.contains('7') && !strInputValue.contains('8') &&
       !strInputValue.contains('9'))
    {
        return false;
    }

    return true;
}
#if 1
bool Hex::isStringHex(void)
{
    int nAsciiValue;

    /* Check normal input */
    for(int i = 0; i < strInputValue.length(); i++)
    {
        nAsciiValue = strInputValue.at(i).toLatin1(); /* Get ASCII code of each character */
        if((nAsciiValue >= 65 && nAsciiValue <= 70) || (nAsciiValue >= 97 && nAsciiValue <= 102) || /* A-F || a-f */
            (nAsciiValue >= 48 && nAsciiValue <= 57) || (nAsciiValue == 120) || (nAsciiValue == 88)) /* 0-9 || x || X */
        {
            continue;
        }
        else
        {
            bWrongInputFlag = true;
            break;
        }
    }

    return bWrongInputFlag;
}
#endif

QString Hex::GetHexValue()
{
    return strHexValue;
}

int Hex::GetHexLen()
{
    return nReqLen;
}

void Hex::GenHexValue()
{
    unsigned char bytes[4] = {0x00, };
    quint32 nRandomValue32 = 0;
    int nCount = 0;
    bool bFinishFlag = false;

    QRandomGenerator *pRandomGenerator = QRandomGenerator::global();
    if(pRandomGenerator == nullptr)
    {
        // do something
    }

    if(nReqLen == 0)
    {
        strHexValue.clear();
        return;
    }

    for(int i = 0; i < (nReqLen / 4) + 1; i++)
    {
        nRandomValue32 = pRandomGenerator->generate(); /* generate 32bit random number */

        for(int j = 0; j < 4; j++)
        {
            bytes[j] = (nRandomValue32 >> (24 - (j * 8))) & 0xFF;
            strHexValue.append(QString("0x")).append(QString("%1, ").arg((long)bytes[j], 2, 16, QChar('0')).toUpper()); nCount++;
            if(nCount >= nReqLen)
            {
                bFinishFlag = true;
                break;
            }
        }
        if(bFinishFlag)
        {
            break;
        }
    }

    strHexValue.chop(2); /*  Eliminate comma(,) + space */

    delete pRandomGenerator;
}

void Hex::Put0x()
{
    int nIndex = 0;

    /* Remove "0x" */
    while(true)
    {
        nIndex = strInputValue.indexOf("0x", nIndex, Qt::CaseInsensitive); /* Get index of '0x' */
        if(nIndex < 0) break; /* No more */

        strInputValue.remove(nIndex, 2); /* Remove "0x" */
    }

    /* Remove comma */
    while(true)
    {
        nIndex = strInputValue.indexOf(','); /* Get index of ',' */
        if(nIndex < 0) break; /* No more "0x" */

        strInputValue.remove(nIndex, 1); /* Remove "0x" */
    }

    while(true)
    {
        nIndex = strInputValue.indexOf(' '); /* Get index of ',' */
        if(nIndex < 0) break; /* No more "0x" */

        strInputValue.remove(nIndex, 1); /* Remove "0x" */
    }

    nReqLen = strInputValue.length(); /* Input string length */

    if(nReqLen % 2) /* String length is odd */
    {
        strInputValue.append("0"); /* Put '0' */
        nReqLen += 1;
    }

    for(int i = 0; i < nReqLen; i += 2)
    {
        strHexValue.append("0x");
        strHexValue.append( strInputValue.mid(i, 2) );
        strHexValue.append(", ");
    }

    strHexValue.chop(2); /* Remove ", " */
}

void Hex::Drop0x()
{
    int nIndex = 0;
    // QString strHexValueNo0x;
    QString strTemp;

    while(true)
    {
        nIndex = strInputValue.indexOf("0x", nIndex, Qt::CaseInsensitive); /* Get index */
        if(nIndex < 0)
        {
            break; /* No more "0x" */
        }

        nIndex += 2; /* Move index */
        strTemp = strInputValue.mid(nIndex, 2); /* From index get 2 character */
        if(strTemp.back() == ',') /* ex) 0x7, */
        {
            strTemp.prepend("0"); /* 07, */
            strTemp.chop(1); /* 07 */
        }
        strHexValue.append(strTemp); /* Append only hex value */
    }

    // strInputValue = strHexValueNo0x;
}
