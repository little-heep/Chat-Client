#include "mywindow.h"

#include <QDebug>

MyWindow::MyWindow(QString id,QString name,client *c,QWidget *parent)
    : QMainWindow(parent)
{
    m_id=id;
    m_name=name;
    clen = c;

    db=new DBManage;
    db->initDatabase();
    // 主窗口设置
    setWindowTitle("客户端");
    resize(800, 600);

    // 主部件和布局
    centralWidget = new QWidget;
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // 左侧菜单栏 (宽度200px)
    menuList = new QListWidget;
    menuList->setFixedWidth(200);
    menuList->setMinimumHeight(400); // 修改最小高度为400像素
    menuList->setSpacing(10); // 设置列表项之间的间距为 10 像素

    // 添加菜单项
    QStringList menuItems = {"消息", "联系人", "群聊", "收藏", "个人信息", "设置"};
    menuList->addItems(menuItems);

    // 右侧堆叠窗口
    stackedWidget = new QStackedWidget;
    stackedWidget->setStyleSheet("background: white;");


    // 为每个菜单项创建对应的内容页面
    for (int i = 0; i < menuItems.size(); ++i) {
        if(i==0){
            msgwidget=new MessageWidget(m_id,clen,this);
            stackedWidget->addWidget(msgwidget);
        }
        else if(i==1)
        {
            QWidget *page=createFriendPage();
            stackedWidget->addWidget(page);
        }
        else if(i==4)
        {
            //创建个人信息编辑页面
            personwidget=new PersonalWidget(m_id,name,this);
            connect(personwidget,SIGNAL(changename(QString)),this,SLOT(onchangename(QString)));
            connect(personwidget,SIGNAL(changepwd(QString,QString)),this,SLOT(onchangepwd(QString,QString)));
            connect(clen,SIGNAL(changenamestatus(QString)),personwidget,SLOT(namechangestatus(QString)));
            connect(clen,SIGNAL(changepwdstatus(QString,QString)),personwidget,SLOT(pwdchangestatus(QString,QString)));
            stackedWidget->addWidget(personwidget);
        }
        else{
            QWidget *page = createContentPage(menuItems[i]);
            stackedWidget->addWidget(page);
        }
    }

    // 连接菜单点击信号到堆叠窗口切换
    connect(menuList, &QListWidget::currentRowChanged,
            stackedWidget, &QStackedWidget::setCurrentIndex);

    connect(clen,&client::updatefriend,this,&MyWindow::showfriend);


    // 默认选中第一个菜单项
    menuList->setCurrentRow(0);

    // 添加到主布局
    mainLayout->addWidget(menuList);
    mainLayout->addWidget(stackedWidget, 1); // 第二个参数1表示占据剩余空间

    setCentralWidget(centralWidget);

    setupStyles();

}

MyWindow::~MyWindow() {}

QWidget* MyWindow::createFriendPage()
{
    QWidget *page=new QWidget;
    QVBoxLayout *layout=new QVBoxLayout(page);
    allfriend=new QListWidget(page);

    QLabel *lab=new QLabel("联系人");

    allfriend->addItem("我自己");

    layout->addWidget(lab);
    layout->addWidget(allfriend);
    return page;
}

QWidget* MyWindow::createContentPage(const QString &title) {
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);

    // 标题
    QLabel *titleLabel = new QLabel(title);
    titleLabel->setStyleSheet(
        "QLabel {"
        "  font-size: 24px;"
        "  font-weight: bold;"
        "  padding: 20px;"
        "  color: #333333;"
        "}"
        );

    // 模拟内容
    QLabel *contentLabel = new QLabel("这是" + title + "页面的内容区域");
    contentLabel->setStyleSheet("font-size: 16px; padding: 20px;");
    contentLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    // 添加一些示例内容
    QPushButton *exampleButton = new QPushButton("示例按钮");
    exampleButton->setStyleSheet(
        "QPushButton {"
        "  padding: 8px 16px;"
        "  background: #4CAF50;"
        "  color: white;"
        "  border: none;"
        "  border-radius: 4px;"
        "}"
        "QPushButton:hover {"
        "  background: #45a049;"
        "}"
        );

    layout->addWidget(titleLabel);
    layout->addWidget(contentLabel);
    layout->addWidget(exampleButton);
    layout->addStretch(); // 添加伸缩使内容靠上

    return page;
}

 void MyWindow::showfriend(FriendListMessage f)
{
     msgwidget->initfriend(f);

    for (const auto& friendInfo : f.friends) {
         FriendListItem *friendItem = new FriendListItem(friendInfo);
         allfriend->addItem(friendItem);
    }
}

void MyWindow::setupStyles() {

    //应用图标
    setWindowIcon(QIcon(":/new/prefix1/images/exec.png"));

    //字体设置
    int fontId = QFontDatabase::addApplicationFont(":/new/prefix1/font/fonttt.ttf");
    if (fontId == -1) {
        qDebug() << "字体加载失败：无法加载字体文件";
        return;
    }
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    if (!fontFamilies.isEmpty()) {
        QString fontFamily = fontFamilies.at(0); // 获取第一个字体家族名称
        //qDebug() << "成功加载字体：" << fontFamily;
        // 设置全局字体
        QFont globalFont(fontFamily, 12); // 字体大小为 12
        qApp->setFont(globalFont);       // 应用到整个应用程序
    }
    else {
        qDebug() << "字体加载失败：无法获取字体家族名称";
    }

    // 主窗口背景颜色
    centralWidget->setStyleSheet("background: #FCE4EC;"); // 粉色背景

    // 左侧菜单栏样式
    menuList->setStyleSheet(
        "QListWidget {"
        "  background: #FFB6C1;" // 浅粉色
        "  border: none;"
        "}"
        "QListWidget::item {"
        "  border-bottom: 1px solid #FFD9E6;" // 浅粉色边框
        "  text-align: center;" // 水平居中对齐
        "}"
        "QListWidget::item:hover {"
        "  background: #FFA0B5;" // 悬停时深一点的粉色
        "}"
        "QListWidget::item:selected {"
        "  background: #FF69B4;" // 选中时更深的粉色
        "  color: white;"
        "}"

        );

    // 堆叠窗口样式
    stackedWidget->setStyleSheet("background: #FFF0F5;"); // 粉色背景

}

void MyWindow::onchangepwd(QString oldpwd,QString newpwd)//修改密码
{
    QJsonObject json;

    json["type"] = "changepwd";        // 消息类型标识
    json["oldpwd"] = oldpwd;
    json["newpwd"] = newpwd;

    //发送消息
    clen->sendJsonMessage(json);

}
void MyWindow::onchangename(QString newname)//修改昵称
{
    QJsonObject json;

    json["type"] = "changename";        // 消息类型标识
    json["name"] = newname;

    //发送消息
    clen->sendJsonMessage(json);
}
