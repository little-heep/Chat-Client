#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>

#include <QSplitter>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include "client.h"
#include "filehandle.h"
#include "allstructs.h"
#include "linemessage.h"

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWidget(QWidget *parent = nullptr,client *clen=0);

    void setmyid(QString i);//设置我自己的id
    void setcurrentid(QString  id);//设置好友的id
    void loadinglog(Message &msg);//加载聊天记录
private:
    client * clen;
    QLabel *iplab;
    QLineEdit *iple;
    QPushButton *send,*start,*sendfile;
    QTextEdit *ed;
    QVBoxLayout *lay;
    QSplitter *sp;

    QScrollArea *showarea;//展示消息区域
    QVBoxLayout *msglayout;//排列消息

    bool firstshow;//记录是否是第一次展示界面
    QString id;//本账号id
    QString currentfriendid;//当前会话的好友id
    fileHandle *dealfile;//处理消息与接送数据转换
    QString m_fileName;//要传送的文件名


    void setstyle();
    QString getPinkThemeStyleSheet();

public slots:
    void appendLog(QString sendid,QString receiveid,QString content,QDateTime sendtime);
    void sendFun();
    void onfileReceived(const QString sendid,const QString filepath);

private slots:
    void onsendfile();

signals:
    void addchatlog(const Message &msg);//添加聊天记录的信号
};

#endif // CHATWIDGET_H
