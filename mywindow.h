#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QStackedWidget>
#include <QFont>
#include <QFontDatabase>
#include "chatwidget.h"
#include "client.h"
#include "dbmanage.h"
#include "friendlistitem.h"
#include "messagewidget.h"
#include "personalwidget.h"

class MyWindow : public QMainWindow
{
    Q_OBJECT

public:
    MyWindow(QString id,QString name,client *c,QWidget *parent = nullptr);
    ~MyWindow();

private:

    //创建客户端连接
    client *clen;

    //数据库管理
    DBManage *db;

    //登录后的用户id
    QString m_id;
    QString m_name;//用户名

    QWidget *centralWidget;//主控件
    QListWidget *menuList;//左侧菜单栏
    QStackedWidget *stackedWidget;//右侧内容栏

    //消息页面控件
    MessageWidget * msgwidget;

    //联系人页面控件
    QListWidget *allfriend;

    //个人信息编辑界面
    PersonalWidget *personwidget;

    //主题
    void setupStyles();

    // 创建其他内容页面
    QWidget* createContentPage(const QString &title);

    //联系人界面
    QWidget* createFriendPage();



private slots:
    void showfriend(FriendListMessage);//初始化好友列表

    void onchangepwd(QString oldpwd,QString newpwd);//修改密码
    void onchangename( QString newname);//修改昵称

    void onaddfriendbyid(QString id);
    void onaddfriendbyname(QString name);

    void onaddfriendresult(bool,QString);
    void onaddfriendrequest(FriendInfo);
    void onacceptfriend(FriendInfo);

signals:


protected:
    //void showEvent(QShowEvent *event);
};
#endif // MYWINDOW_H

