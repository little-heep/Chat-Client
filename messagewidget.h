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
#include "client.h"
#include "friendlistitem.h"
#include "dbmanage.h"
#include <QMenu>
#include <QDialog>
#include <QMessageBox>


class MessageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MessageWidget(QString me,client *c,QWidget *parent = nullptr);

    //初始化好友列表
    void initfriend(FriendListMessage);
    void addfriend(FriendInfo);

private:
    QString myid;
    QLineEdit *searchBox;
    QListWidget *sessionList;
    QStackedWidget *chatStack;
    QMap<QString,ChatWidget*>chatWidgets;
    QLabel *chatTitle;
    client *clen;
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

private slots:
    void onSessionChanged(QListWidgetItem *current);
    void onaddlog(const Message &msg);
    void onSearchFriend();
};

#endif // MESSAGEWIDGET_H
