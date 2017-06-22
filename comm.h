#ifndef COMM_H
#define COMM_H
#include <QString>
#include <QByteArray>

namespace BgComm
{
    QString ByteArrayToHexString(QByteArray ascii);
    QByteArray HexStringToByteArray(QString hex, bool *ok);
}

#endif // COMM_H
