#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QHostAddress>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSslSocket>
#include <QSslConfiguration>
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include "filehandle.h"
#include "allstructs.h"

class client : public QObject
{
    Q_OBJECT
public:

    explicit client(QObject *parent = nullptr);

    void startCommunication();
    void reconnect();
    void sendJsonMessage(const QJsonObject &jsonMsg);//发送json消息
    void sendfile(const QString filename,const QString sendid,const QString receiveid);//发送文件

    QList<Message*> msglist;
    QSslSocket *tcpSocket;
    fileHandle *files;
    FriendListMessage friendlist;//好友列表
    Message *message;//收到的消息
    bool isconnected;//连接状态
signals:
    void messageLogged(QString sendid,QString receiveid,QString content,QDateTime sendtime);// 展示信息到界面的信号
    void updatefriend(FriendListMessage message);
    void loginsucess(QString id);
    void loginfail(QString message);
    void fileReceived(const QString sendid,const QString filePath);
    void changepwdstatus(QString statu,QString msg);
    void changenamestatus(QString statu);
    void addfriendresult(bool ok,QString detail);
    void addfriendrequest(FriendInfo finfo);
    void acceptfriend(FriendInfo finfo);
    void registerSuccess(uint userid, QString message);
    void registerFail(QString message);
private:
    QString aimip;
    QString aimport;

    bool waitReconnect = false;

    //发送文件相关数据
    QFile *fileToSend;
    qint64 fileBytesSent;
    qint64 fileTotalSize;
    void sendFileHeader(const QString &fileName, qint64 fileSize,const QString sendid,const QString receiveid);
    void sendFileData();

    void loadrecord();
    FriendListMessage parseFriendListMessage(const QByteArray& jsonData);
    Message* parsetalkmessage(const QByteArray & jsonData);
    void logincheck(const QByteArray &jsonData);
    void registercheck(const QByteArray &jsonData);
    void changepwdcheck(const QByteArray & jsonData);
    void changenamecheck(const QByteArray & jsonData);

    void addfriendcheck(const QByteArray & jsonData);
    void addfriendnotify(const QByteArray & jsonData);
    void acceptfriendresponse(const QByteArray & jsonData);

    QFile* fileToReceive;          // 正在接收的文件
    qint64 fileTotalSizeToReceive; // 要接收的文件总大小
    qint64 fileBytesReceived;      // 已接收的字节数
    QString sendid;//发送人
    void readfile(const QByteArray &jsonData);//接收文件

private slots:
    void handleError(QAbstractSocket::SocketError socketError);
    void readData();
    void receiveFileData();




};

#endif // CLIENT_H
