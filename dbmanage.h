#ifndef DBMANAGE_H
#define DBMANAGE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "allstructs.h"

class DBManage: public QObject {
    Q_OBJECT // 必须包含这一行
public:
    explicit DBManage(QObject *parent = nullptr);

    void initDatabase();
    QList<Message> getAllMessages();
    QList<Message> getMessagesByReceiverId(const QString &receiveid);

public slots:

    bool insertMessage(const Message &msg);
    bool deleteMessageById(int id);
    QList<Message> searchMessagesByContent(const QString &keyword);

};

#endif // DBMANAGE_H
