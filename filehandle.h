#ifndef FILEHANDLE_H
#define FILEHANDLE_H

#include <QString>
#include <QSharedPointer>
#include <QDateTime>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>
#include <QTextStream>
#include <QJsonArray>

#include "allstructs.h"

class fileHandle
{
public:

    fileHandle();
/*
    void appendTextToFile(const QString &text, const QString &senderIp, const QString &receiverIp,const bool sended);
    QString readTextFile();
    void clearTextFile();
    bool writeTextFile(const QString &content);
*/
    QJsonObject messageToJson(const Message &msg);
    Message* jsonToMessage(const QJsonObject &json);

    //QString recordFilePath;

};

#endif // FILEHANDLE_H
