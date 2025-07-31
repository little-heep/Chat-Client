#ifndef ALLSTRUCTS_H
#define ALLSTRUCTS_H

#include <QString>
#include <QList>
#include <QDebug>
#include <QDateTime>

//好友信息
struct FriendInfo {
    QString userID;
    QString name;
    int status;//好友状态
    bool online;

    void print() const {
        qDebug() << "User ID:" << userID
                 <<"name:"<<name
                 << "Status:" << status
                 << "Online:" << online;
    }
};

struct FriendListMessage {
    QString type;
    QList<FriendInfo> friends;

    void print() const {
        qDebug() << "Type:" << type;
        for (const auto& friendInfo : friends) {
            friendInfo.print();
        }
    }
};

// 定义发送消息结构体
struct Message {
    QString type;       //消息类型，为message
    QString sendid;      // 发送方id
    QString receiveid;    // 接收方id
    QString content;       // 消息内容
    QDateTime sendTime;    // 发送时间
};



#endif // ALLSTRUCTS_H
