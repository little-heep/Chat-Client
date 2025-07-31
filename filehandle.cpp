#include "filehandle.h"

fileHandle::fileHandle() {}

/*
void fileHandle::appendTextToFile(const QString &text, const QString &senderIp, const QString &receiverIp, const bool sended) {

    QFile recordfile(recordFilePath);

    // 读取现有的文件内容
    QByteArray jsonData;
    QJsonArray jsonArray;

    if (recordfile.exists() && recordfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        jsonData = recordfile.readAll();
        recordfile.close();

        // 解析现有的JSON数据
        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
        if (parseError.error == QJsonParseError::NoError) {
            if (jsonDoc.isArray()) {
                jsonArray = jsonDoc.array();
            } else {
                qWarning("文件内容不是有效的JSON数组.");
                // 如果文件不是有效的JSON数组，则清空并初始化为一个新数组
                jsonArray = QJsonArray();
            }
        } else {
            qWarning("解析JSON数据失败: %s", qPrintable(parseError.errorString()));
            // 如果解析失败，则初始化为一个新的数组
            jsonArray = QJsonArray();
        }
    }

    // 创建新的消息对象
    auto now = QDateTime::currentDateTime();
    QJsonObject newMessage = messageToJson(senderIp, receiverIp, text, now, sended);

    // 将新的消息对象添加到数组中
    jsonArray.append(newMessage);

    // 创建新的JSON文档并格式化输出
    QJsonDocument updatedJsonDoc(jsonArray);
    QByteArray formattedJson = updatedJsonDoc.toJson(QJsonDocument::Indented);

    // 写入更新后的JSON数组到文件
    if (!recordfile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qWarning("无法打开记录文件进行写入操作.");
        return;
    }

    recordfile.write(formattedJson);
    recordfile.close();
}

QString fileHandle::readTextFile() {
    QFile file(recordFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return "";
    }

    QString content = file.readAll();
    file.close();
    return content;
}

bool fileHandle::writeTextFile(const QString &content) {
    QFile file(recordFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {//会从最开始的地方开始写，即清空原先内容
        qDebug() << "无法打开文件进行写入.";
        return false;
    }

    QTextStream out(&file);
    out << content;
    file.close();
    return true;
}

void fileHandle::clearTextFile() {
    QFile file(recordFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    out << "";
    file.close();
}

*/

QJsonObject fileHandle::messageToJson(const Message &msg) {
    QJsonObject json;

    json["type"] = "message";           // 消息类型标识
    json["sendid"] = msg.sendid;
    json["receiveid"] = msg.receiveid;
    json["content"] = msg.content;
    json["sendTime"] = msg.sendTime.toString(Qt::ISODateWithMs); // ISO格式含毫秒

    return json;
}

// 从JSON对象转换回结构体
Message* fileHandle::jsonToMessage(const QJsonObject &json) {
    Message *message = new Message();
    message->sendid = json["sendid"].toString();
    message->receiveid = json["receiveid"].toString();
    message->content = json["content"].toString();
    QString sendTimeStr = json["sendTime"].toString();
    message->sendTime = QDateTime::fromString(sendTimeStr, Qt::ISODateWithMs);
    qDebug()<<message->sendTime;
    return message;
}
