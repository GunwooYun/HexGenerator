#include "hex.h"
#include <QRandomGenerator>

#include <openssl/rand.h>

Hex::Hex(QString strInput)
{
    this->strInputValue = strInput;
    this->nReqLen = 0;
}

bool Hex::isDecNumber(void)
{
    int nAsciiValue;
    /* Check normal input */
    for(int i = 0; i < strInputValue.length(); i++)
    {
        nAsciiValue = strInputValue.at(i).toLatin1(); /* Get ASCII code of each character */
        if((nAsciiValue >= 48) && (nAsciiValue <= 57)) /* 0-9 */
        {
            continue;
        }
        else
        {
            return false;
        }
    }

    return true;
}

bool Hex::isHexNumber(void)
{
    int nAsciiValue;

    /* Check normal input */
    for(int i = 0; i < strInputValue.length(); i++)
    {
        nAsciiValue = strInputValue.at(i).toLatin1(); /* Get ASCII code of each character */
        if((nAsciiValue >= 65 && nAsciiValue <= 70) || (nAsciiValue >= 97 && nAsciiValue <= 102) || /* A-F || a-f */
            (nAsciiValue >= 48 && nAsciiValue <= 57)) /* 0-9 || x || X || ' ' */
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

#if 1
bool Hex::isHexFormat(void)
{
    int nAsciiValue;

    /* Check normal input */
    for(int i = 0; i < strInputValue.length(); i++)
    {
        nAsciiValue = strInputValue.at(i).toLatin1(); /* Get ASCII code of each character */
        if((nAsciiValue >= 65 && nAsciiValue <= 70) || (nAsciiValue >= 97 && nAsciiValue <= 102) || /* A-F || a-f */
            (nAsciiValue >= 48 && nAsciiValue <= 57) || (nAsciiValue == 120) || (nAsciiValue == 88) || (nAsciiValue == 32)) /* 0-9 || x || X || ' ' */
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
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

    if(!isDecNumber())
    {
        strHexValue = QString("Input only decimal number!!");
        return;
    }

    nReqLen = strInputValue.toInt();
    if(nReqLen == 0)
    {
        strHexValue.clear();
        return;
    }

    QRandomGenerator *pRandomGenerator = QRandomGenerator::global();
    if(pRandomGenerator == nullptr)
    {
        strHexValue = QString("Internal error!!");
        return;
    }

    for(int i = 0; i < (nReqLen / 4) + 1; i++)
    {
        nRandomValue32 = pRandomGenerator->generate(); /* generate 32bit random number */

        for(int j = 0; j < 4; j++)
        {
            bytes[j] = (nRandomValue32 >> (24 - (j * 8))) & 0xFF;
            strHexValue.append(QString("0x")).append(QString("%1, ").arg((long)bytes[j], 2, 16, QChar('0')).toUpper());
            nCount++;
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

    /* Remove space */
    while(true)
    {
        nIndex = strInputValue.indexOf(' '); /* Get index of ' ' */
        if(nIndex < 0) break; /* No more "0x" */

        strInputValue.remove(nIndex, 1); /* Remove "0x" */
    }

    if(!isHexNumber())
    {
        strHexValue = QString("Input only Hex number!!");
        return;
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

    nReqLen /= 2; /* Convert length to bytes */
}

void Hex::Drop0x()
{
    int nIndex = 0;
    QString strTemp;

    while(true)
    {
        nIndex = strInputValue.indexOf("0x", nIndex, Qt::CaseInsensitive); /* Get index */
        if(nIndex < 0)
        {
            if(strTemp.isEmpty()) /* Did nothing because of processed input */
            {
                strHexValue = strInputValue;
            }
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

    nReqLen = strHexValue.length() / 2; /* Convert length to bytes */
}

void Hex::DecToHex()
{
    unsigned int nDecimal;
    if(!isDecNumber())
    {
        strHexValue = QString("No Decimal number!!");
        return;
    }
    nDecimal = strInputValue.toInt();

    // strHexValue = QString::number(nDecimal, 16); /* Convert decimal to hexadecimal */
    strHexValue = QString("%1").arg(nDecimal, 0, 16).toUpper();
    if(strHexValue.length() % 2)
    {
        strHexValue.prepend('0');
    }

    // unsigned char randArr[1024] = {0x00, };
    // RAND_bytes(randArr, 1024);

    // std::string test= (char*)randArr;
    // strHexValue = QString::fromStdString(test);

    // strHexValue = QString("%1").arg()


}
