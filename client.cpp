#include "client.h"
#include <QDebug>
#include <QFileInfo>
#include <QTimer>
#include <QDataStream>


client::client(QObject *parent)
    : QObject{parent}
{

}
void client::init()
{
    tcpSocket=new QSslSocket(this);
    //QHostAddress localhost = QHostAddress::LocalHost;
    aimip="120.76.136.246";
    aimport="12345";

    connect(tcpSocket, &QSslSocket::connected, this, [=]() {
        qDebug()<<"连接成功！\n";
        isconnected=true;
    });
    connect(tcpSocket, &QSslSocket::readyRead, this,&client::readData);
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleError(QAbstractSocket::SocketError)));
    connect(tcpSocket,&QSslSocket::disconnected,this,[=](){
        qDebug()<<"已断开连接\n";
        isconnected=false;
        if (waitReconnect)
        {
            waitReconnect = false;

            qDebug() << "重新连接服务器...";
            startCommunication();
        }
    });

    startCommunication();   // 开始连接服务器
}

//开始连接
void client::startCommunication() {
    // 关闭任何现有的连接
    tcpSocket->abort();

    // 将字符串形式的IP地址转换为QHostAddress对象
    QHostAddress address(aimip); // 直接使用构造函数
    if (address.isNull()) {
        qDebug() << "无效的IP地址:" << aimip;
        return;
    }

    // 将端口字符串转换为整数
    bool ok;
    quint16 port = aimport.toUInt(&ok);
    if (!ok) {
        qDebug() << "无效的端口号:" << aimport;
        return;
    }

    /*
    // 如果是自签名证书，需要预先加载CA证书
    QFile caFile(":/certs/ca.crt");
    if (caFile.open(QIODevice::ReadOnly)) {
        QList<QSslCertificate> caCerts = QSslCertificate::fromDevice(&caFile);
        tcpSocket->addCaCertificates(caCerts);
    }
*/
    // 连接到指定的主机和端口
    tcpSocket->connectToHost(address, port);
}

//错误处理
void client::handleError(QAbstractSocket::SocketError socketError) {
    QString errorMessage;

    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        errorMessage = "远程主机已关闭连接。";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        errorMessage = "连接被拒绝。请检查服务器是否正在运行并监听正确的端口。";
        break;
    case QAbstractSocket::HostNotFoundError:
        errorMessage = "无法找到主机。请检查服务器地址是否正确。";
        break;
    default:
        errorMessage = "未知错误: " + tcpSocket->errorString();
        break;
    }

    // 或者发送信号到其他模块
    qDebug()<<errorMessage;
}

//读取数据
void client::readData() {
    recvBuffer.append(tcpSocket->readAll());
    while (true)
    {
        // ===== 1. 先读 type + length =====
        if (state == ReadingHeader)
        {
            if (recvBuffer.size() < 8)
                return;

            QDataStream stream(&recvBuffer,QIODevice::ReadOnly);
            stream.setByteOrder(QDataStream::BigEndian);

            stream >> currentType;
            stream >> currentLength;

            recvBuffer.remove(0, 8);
            state = ReadingBody;
        }

        // ===== 2. body不够 =====
        if (recvBuffer.size() < currentLength)
            return;

        QByteArray body = recvBuffer.left(currentLength);
        recvBuffer.remove(0, currentLength);

        state = ReadingHeader;

        // ===== 3. 分发 =====
        handlePacket(currentType, body);
    }
}


void client::processMessage(const QByteArray &jsonData){
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (!doc.isObject()) {
        qWarning() << "Received data is not a valid JSON object.";
        return;
    }

    QJsonObject obj = doc.object();
    QString type = obj.value("type").toString();

    if (type == "friend_list") {
        friendlist = parseFriendListMessage(jsonData);
        friendlist.print();
        qDebug()<<"from client";
        emit updatefriend(friendlist);
    }
    else if(type=="message")
    {   //接收消息，处理json数据，然后显示
        message=parsetalkmessage(jsonData);
        qDebug()<<message->content+"\n"+message->sendTime.toString("yyyy-MM-dd hh:mm")+"\n";
        emit messageLogged(message->sendid,message->receiveid,message->content,message->sendTime);
    }
    else if(type=="login_response")
    {
        logincheck(jsonData);
    }
    else if(type=="file_notify")
        readfile(jsonData);
    else if (type=="changepwd_response")
        changepwdcheck(jsonData);
    else if (type=="changename_response")
        changenamecheck(jsonData);
    else if(type=="addfriend_response")
        addfriendcheck(jsonData);
    else if(type=="addfriend_request")
        addfriendnotify(jsonData);
    else if (type=="acceptfriend_response")
        acceptfriendresponse(jsonData);
    else if(type == "register_response")
    {
        registercheck(jsonData);
    }
    else if (type == "another_type") { // 对应于另一种消息类型的type值
        // 解析并处理另一种类型的消息
    }
    else {
        qDebug() << "Unknown message type:" << type;
    }
}


void client::acceptfriendresponse(const QByteArray & jsonData)
{
    QJsonParseError parseError;
    const QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);

    // 检查JSON解析是否出错
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "JSON解析错误:" << parseError.errorString();
        return ;
    }

    if (!doc.isObject()) {
        qWarning() << "JSON数据不是对象格式";
        return;
    }

    const QJsonObject jsonObj = doc.object();
    FriendInfo finfo;
    finfo.name=jsonObj["username"].toString();
    finfo.status=jsonObj["userstatus"].toInt();
    finfo.online=jsonObj["online"].toBool();
    finfo.userID=jsonObj["userid"].toString();
    emit acceptfriend(finfo);
}

void client::addfriendcheck(const QByteArray & jsonData)
{
    QJsonParseError parseError;
    const QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);

    // 检查JSON解析是否出错
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "JSON解析错误:" << parseError.errorString();
        return ;
    }

    if (!doc.isObject()) {
        qWarning() << "JSON数据不是对象格式";
        return;
    }

    const QJsonObject jsonObj = doc.object();
    if(jsonObj["status"]=="success")
        emit addfriendresult(true,jsonObj["message"].toString());
    else
        emit addfriendresult(false,jsonObj["message"].toString());

}

void client::addfriendnotify(const QByteArray & jsonData)
{
    QJsonParseError parseError;
    const QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);

    // 检查JSON解析是否出错
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "JSON解析错误:" << parseError.errorString();
        return ;
    }

    if (!doc.isObject()) {
        qWarning() << "JSON数据不是对象格式";
        return;
    }

    const QJsonObject jsonObj = doc.object();
    FriendInfo finfo;
    finfo.name=jsonObj["addname"].toString();
    finfo.status=jsonObj["status"].toInt();
    finfo.online=jsonObj["online"].toBool();
    finfo.userID=jsonObj["addid"].toString();
    emit addfriendrequest(finfo);
}


void client::changenamecheck(const QByteArray & jsonData)
{
    QJsonParseError parseError;
    const QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);

    // 检查JSON解析是否出错
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "JSON解析错误:" << parseError.errorString();
        return ;
    }

    if (!doc.isObject()) {
        qWarning() << "JSON数据不是对象格式";
        return;
    }

    const QJsonObject jsonObj = doc.object();
    QString status=jsonObj["status"].toString();
    emit changenamestatus(status);
}

void client::changepwdcheck(const QByteArray & jsonData)
{
    QJsonParseError parseError;
    const QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);

    // 检查JSON解析是否出错
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "JSON解析错误:" << parseError.errorString();
        return ;
    }

    if (!doc.isObject()) {
        qWarning() << "JSON数据不是对象格式";
        return;
    }

    const QJsonObject jsonObj = doc.object();
    QString status=jsonObj["status"].toString();
    QString msg=jsonObj["message"].toString();
    emit changepwdstatus(status,msg);

}

FriendListMessage client::parseFriendListMessage(const QByteArray& jsonData)
{
    FriendListMessage message;

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (!doc.isObject()) {
        qWarning() << "Invalid JSON object.";
        return message;
    }

    QJsonObject obj = doc.object();

    message.type = obj.value("type").toString();

    QJsonArray friendsArray = obj.value("friends").toArray();
    for (const QJsonValue& value : friendsArray) {
        QJsonObject friendObj = value.toObject();

        FriendInfo info;
        info.userID = friendObj.value("user_id").toString();
        info.name=friendObj.value("name").toString();
        info.status = friendObj.value("status").toInt();
        info.online = friendObj.value("online").toBool();

        message.friends.append(info);
    }

    return message;
}

//解析好友发来的聊天信息
Message* client::parsetalkmessage(const QByteArray & jsonData)
{
    Message *msg;
    QJsonParseError parseError;
    const QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);

    // 检查JSON解析是否出错
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "JSON解析错误:" << parseError.errorString();
        return NULL; // 返回空结构体
    }

    if (!doc.isObject()) {
        qWarning() << "JSON数据不是对象格式";
        return NULL;
    }

    const QJsonObject jsonObj = doc.object();

    msg=files->jsonToMessage(jsonObj);
    /*
    // 提取必填字段
    msg.type = jsonObj["type"].toString();
    msg.sendid = jsonObj["sendid"].toString();
    msg.receiveid = jsonObj["receiveid"].toString();
    msg.content = jsonObj["content"].toString();

    // 处理时间字段（支持时间戳或ISO格式字符串）
    if (jsonObj["sendTime"].isDouble()) {
        // 时间戳格式（毫秒级）
        const qint64 timestamp = static_cast<qint64>(jsonObj["sendTime"].toDouble());
        msg.sendTime = QDateTime::fromMSecsSinceEpoch(timestamp);
    } else {
        // ISO8601字符串格式
        msg.sendTime = QDateTime::fromString(jsonObj["sendTime"].toString(), Qt::ISODate);
    }
*/

    return msg;
}

//发送json数据
void client::sendJsonMessage(const QJsonObject &jsonMsg) {
    QJsonDocument doc(jsonMsg);
    QByteArray jsonData = doc.toJson(QJsonDocument::Compact);

    quint32 type = 1;
    quint32 len = jsonData.size();

    QByteArray block;
    QDataStream stream(&block, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::BigEndian);

    stream << type;
    stream << len;
    block.append(jsonData);

    tcpSocket->write(block);
}

void client::logincheck(const QByteArray &jsonData)
{
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug()<<"登录反馈解析错误";
        return;
    }

    QJsonObject obj = doc.object();
    bool success;
    success = obj["success"].toBool();
    QString m;
    m = obj["message"].toString();
    if(success)
    {
        QString id;
        id=m.mid(3);
        emit loginsucess(id);
    }
    else
    {
        emit loginfail(m);
    }

}

void client::sendfile(const QString filename,const QString sendid,const QString receiveid)
{
    if (!isconnected) {
        qDebug() << "未连接到服务器，无法发送文件";
        return;
    }

    // 打开文件
    fileToSend = new QFile(filename);
    if (!fileToSend->open(QIODevice::ReadOnly)) {
        qDebug() << "无法打开文件:" << filename;
        delete fileToSend;
        fileToSend = nullptr;
        return;
    }

    // 获取文件信息
    QFileInfo fileInfo(filename);
    QString fileName = fileInfo.fileName();
    fileTotalSize = fileInfo.size();
    fileBytesSent = 0;

    // 发送文件头信息
    sendFileHeader(fileName, fileTotalSize,sendid,receiveid);
}

// 发送文件头信息
void client::sendFileHeader(const QString &fileName, qint64 fileSize,QString sendid,QString receiveid)
{
    QJsonObject header;
    header["filename"] = fileName;
    header["size"] = fileSize;
    header["sendid"] = sendid;
    header["receiveid"] = receiveid;

    QJsonDocument doc(header);
    QByteArray data = doc.toJson(QJsonDocument::Compact);

    quint32 type = 3; // file header
    quint32 len = data.size();

    QByteArray block;
    QDataStream stream(&block, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::BigEndian);

    stream << type << len;
    block.append(data);

    tcpSocket->write(block);

    QTimer::singleShot(0,this,&client::sendFileData);
}

// 发送文件数据
void client::sendFileData()
{
    if (!fileToSend || !fileToSend->isOpen())
        return;

    const qint64 chunkSize = 64 * 1024;

    QByteArray chunk = fileToSend->read(chunkSize);
    if (chunk.isEmpty())
    {
        qDebug()<<"文件发送完成";
        fileToSend->close();
        delete fileToSend;
        fileToSend = nullptr;
        return;
    }

    quint32 type = 2; // file chunk
    quint32 len = chunk.size();

    QByteArray block;
    QDataStream stream(&block, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::BigEndian);

    stream << type << len;
    block.append(chunk);

    qint64 ret =tcpSocket->write(block);
    tcpSocket->flush();

    if(ret==-1)
    {
        qDebug()<<"发送失败";
    }

    QTimer::singleShot(0, this, &client::sendFileData);
}

//读取文件消息
void client::readfile(const QByteArray &jsonData)
{
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "文件通知JSON解析错误:" << parseError.errorString();
        return;
    }

    QJsonObject obj = doc.object();

    // 解析文件信息
    QString fileName = obj["filename"].toString();
    qint64 fileSize = obj["size"].toVariant().toLongLong();
    sendid = obj["sendid"].toString();
    qDebug()<<"client解析文件头时的sendid："<<sendid;

    // 设置保存路径
    QString saveDir = QCoreApplication::applicationDirPath() + "/ReceivedFiles/";
    QDir dir(saveDir);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QString filePath = saveDir + fileName;

    // 检查文件是否已存在，避免覆盖
    int counter = 1;
    while (QFile::exists(filePath)) {
        QFileInfo fileInfo(fileName);
        QString baseName = fileInfo.completeBaseName();
        QString extension = fileInfo.suffix();
        filePath = saveDir + baseName + "_" + QString::number(counter) + "." + extension;
        counter++;
    }

    // 准备接收文件
    fileToReceive = new QFile(filePath);
    if (!fileToReceive->open(QIODevice::WriteOnly)) {
        qWarning() << "无法创建文件:" << filePath;
        delete fileToReceive;
        fileToReceive = nullptr;
        return;
    }

    fileTotalSizeToReceive = fileSize;
    fileBytesReceived = 0;
}


void client::registercheck(const QByteArray &jsonData){
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "文件通知JSON解析错误:" << parseError.errorString();
        return;
    }

    QJsonObject obj = doc.object();

    QString status = obj["status"].toString();
    QString message = obj["message"].toString();

    if(status == "success")
    {
        waitReconnect = true;
        uint userid = obj["userid"].toInt();
        emit registerSuccess(userid, message);
    }
    else
    {
        emit registerFail(message);
    }
}

void client::reconnect()
{
    qDebug() << "开始重新连接服务器...";

    if (tcpSocket->state() != QAbstractSocket::UnconnectedState)
    {
        tcpSocket->abort();
    }

    startCommunication();
}


void client::handleFileData(const QByteArray &data)
{
    if (!fileToReceive)
        return;

    fileToReceive->write(data);
    fileBytesReceived += data.size();

    if (fileBytesReceived >= fileTotalSizeToReceive)
    {
        fileToReceive->close();

        emit fileReceived(sendid, fileToReceive->fileName());

        delete fileToReceive;
        fileToReceive = nullptr;

        qDebug() << "文件接收完成";
    }
}

void client::handlePacket(quint32 type, const QByteArray &data)
{
    switch (type)
    {
    case 1: // JSON
        processMessage(data);
        break;

    case 2: // 文件数据
        handleFileData(data);
        break;

    case 3: // 文件头（可选）
        readfile(data);
        break;

    default:
        qDebug() << "unknown type:" << type;
        break;
    }
}


void client::onrestart(){
    startCommunication();
}

void client::onsendmessage(QJsonObject user){
    sendJsonMessage(user);
}
