#include "dbmanage.h"

DBManage::DBManage(QObject *parent ):QObject(parent) {}

void DBManage::initDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("chat.db"); // 数据库文件名

    if (!db.open()) {
        qDebug() << "无法打开数据库";
        return;
    }

    // 创建表（如果不存在）
    QSqlQuery query;
    bool ok = query.exec(
        "CREATE TABLE IF NOT EXISTS chatlog ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "sendid varchar(20), "
        "receiveid varchar(20), "
        "content TEXT, "
        "sendTime varchar(20)"
        ");");
    if (!ok) {
        qDebug() << "创建表失败：" << query.lastError();
    }
}

bool DBManage::insertMessage(const Message &msg)
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO chatlog (sendid, receiveid, content, sendTime) "
        "VALUES (:sendid, :receiveid, :content, :sendTime)"
        );

    query.bindValue(":sendid", msg.sendid);
    query.bindValue(":receiveid", msg.receiveid);
    query.bindValue(":content", msg.content);
    query.bindValue(":sendTime", msg.sendTime.toString(Qt::ISODateWithMs));

    if (!query.exec()) {
        qDebug() << "插入消息失败：" << query.lastError();
        return false;
    }

    return true;
}

bool DBManage::deleteMessageById(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM chatlog WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "删除消息失败：" << query.lastError();
        return false;
    }

    return true;
}

QList<Message> DBManage::getAllMessages()
{
    QList<Message> messages;

    QSqlQuery query("SELECT id, sendid, receiveid, content, sendTime FROM chatlog ORDER BY sendTime");

    while (query.next()) {
        Message msg;
        msg.sendid = query.value("sendid").toString();
        msg.receiveid = query.value("receiveid").toString();
        msg.content = query.value("content").toString();
        msg.sendTime = QDateTime::fromString(query.value("sendTime").toString(), Qt::ISODateWithMs);

        messages.append(msg);
    }

    return messages;
}

//查询聊天记录
QList<Message> DBManage::searchMessagesByContent(const QString &keyword) {
    QList<Message> messages;

    QSqlQuery query;
    // 使用 LIKE 进行模糊搜索，并且两边加上 % 表示任意字符序列
    query.prepare("SELECT id, sendid, receiveid, content, sendTime"
                  "FROM chatlog WHERE content LIKE :keyword");
    query.bindValue(":keyword", "%" + keyword + "%");

    if (!query.exec()) {
        qDebug() << "模糊搜索失败：" << query.lastError();
        return messages;
    }

    while (query.next()) {
        Message msg;
        msg.sendid = query.value("sendid").toString();
        msg.receiveid = query.value("receiveid").toString();
        msg.content = query.value("content").toString();
        msg.sendTime = QDateTime::fromString(query.value("sendTime").toString(), Qt::ISODateWithMs);

        messages.append(msg);
    }

    return messages;
}

//根据接收方id（即好友id）查询聊天记录
QList<Message> DBManage::getMessagesByReceiverId(const QString &receiveid) {
    QList<Message> messages;

    QSqlQuery query;
    query.prepare("SELECT id, sendid, receiveid, content, sendTime "
                  "FROM chatlog WHERE receiveid = :receiveid");
    query.bindValue(":receiveid", receiveid);

    if (!query.exec()) {
        qDebug() << "根据接收方ID查询失败：" << query.lastError();
        return messages;
    }

    while (query.next()) {
        Message msg;
        msg.sendid = query.value("sendid").toString();
        msg.receiveid = query.value("receiveid").toString();
        msg.content = query.value("content").toString();
        msg.sendTime = QDateTime::fromString(query.value("sendTime").toString(), Qt::ISODateWithMs);

        messages.append(msg);
    }

    return messages;
}
