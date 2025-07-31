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


class MessageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MessageWidget(QString me,client *c,QWidget *parent = nullptr);

    //初始化好友列表
    void initfriend(FriendListMessage);

private:
    QString myid;
    QLineEdit *searchBox;
    QListWidget *sessionList;
    QStackedWidget *chatStack;
    QMap<QString,ChatWidget*>chatWidgets;
    QLabel *chatTitle;
    client *clen;
    DBManage *database=new DBManage();

    //设置右键好友展示信息
    void setupListWidget();

    void showFriendContextMenu(const QPoint &pos);

    void initlog();

signals:
    void sendid(QString);

private slots:
    void onSessionChanged(QListWidgetItem *current);
    void onaddlog(const Message &msg);
};

#endif // MESSAGEWIDGET_H
