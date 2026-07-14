#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QLineEdit>
#include <QListWidget>
#include <QStackedWidget>
#include "chatwidget.h"
#include "allstructs.h"
#include "friendlistitem.h"
#include "dbmanage.h"
#include <QMenu>
#include <QDialog>
#include <QMessageBox>


class MessageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MessageWidget(QString me,QWidget *parent = nullptr);

    //初始化好友列表
    void initfriend(FriendListMessage);
    void addfriend(FriendInfo);
public slots:
    void onappendLog(QString sendid,QString receiveid,QString content,QDateTime sendtime);
    void onfileReceived(const QString sendid,const QString filepath);

private:
    QString myid;
    QLineEdit *searchBox;
    QListWidget *sessionList;
    QStackedWidget *chatStack;
    QMap<QString,ChatWidget*>chatWidgets;
    QLabel *chatTitle;
    DBManage *database=new DBManage();
    QMap<QString,QString> *friendlist;//好友昵称列表

    //设置右键好友展示信息
    void setupListWidget();

    void showFriendContextMenu(const QPoint &pos);

    void initlog();
    
    // 根据好友ID查找并选中列表项
    void selectFriendInList(const QString &friendId);

signals:
    void sendid(QString);
    void addfriendbyid(QString);
    void addfriendbyname(QString);
    void sendmessage(const QJsonObject &jsonMsg);
    void sendfilemsg(const QString filename,const QString sendid,const QString receiveid);
    void newmsg(QString sendid,QString receiveid,QString content,QDateTime sendtime);
    void filereceived(const QString sendid,const QString filepath);

private slots:
    void onSessionChanged(QListWidgetItem *current);
    void onaddlog(const Message &msg);
    void onSearchFriend();
    void onsendmessage(const QJsonObject &jsonMsg);
    void onsendfile(const QString filename,const QString sendid,const QString receiveid);
};

#endif // MESSAGEWIDGET_H
