#include "comm.h"
#include <QStringList>

QString BgComm::ByteArrayToHexString(QByteArray ascii)
{
    QString ret;

    for(int i = 0; i < ascii.count(); i++)
        ret.append(QString("%1 ").arg((uchar)ascii.at(i), 2, 16, (QChar)'0'));

    return ret.toUpper();
}

QByteArray BgComm::HexStringToByteArray(QString hex, bool *ok)
{
    int p;
    QByteArray ret;


    QStringList lst = hex.simplified().split(' ');
    ret.resize(lst.count());

    for(int i = 0; i < lst.count(); i++)
    {
        p = lst[i].toInt(ok, 16);
        if(!(*ok) || p > 255 )
        {
            return 0;
        }
        ret[i] = p;
    }

    return ret;
}
