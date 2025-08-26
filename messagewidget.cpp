#include "messagewidget.h"

MessageWidget::MessageWidget(QString me,client *c,QWidget *parent)
    : QWidget{parent}
{
    clen=c;
    myid=me;
    friendlist = new QMap<QString, QString>();

    // 主布局
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // 使用分割器
    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);

    /* 左侧会话列表区域 */
    QWidget *leftPanel = new QWidget;
    leftPanel->setMinimumWidth(250);
    leftPanel->setMaximumWidth(350);
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->setSpacing(0);
    leftLayout->setContentsMargins(0, 0, 0, 0);

    // 搜索框
    searchBox = new QLineEdit;
    searchBox->setPlaceholderText("搜索昵称或ID...");
    searchBox->setStyleSheet("QLineEdit { padding: 8px; border: none; border-bottom: 1px solid #FFB6C1; background: #FFF0F5; }");
    // 搜索按钮
    QPushButton *searchbtn=new QPushButton("搜索");
    searchbtn->setFixedWidth(50);
    searchbtn->setStyleSheet("QPushButton{padding: 8px; border: none; border-bottom: 1px solid #FFB6C1; background: #FFF0F5;}");
    QHBoxLayout *hlayout=new QHBoxLayout;
    hlayout->addWidget(searchBox);
    hlayout->addWidget(searchbtn);

    // 会话列表
    sessionList = new QListWidget;
    sessionList->setStyleSheet(
        "QListWidget { background: #FFF0F5; border: none; }"
        "QListWidget::item { height: 70px; border-bottom: 1px solid #FFE4E1; }"
        "QListWidget::item:hover { background: #FFB6C1; }"
        "QListWidget::item:selected { background: #FF69B4; }"
        );
    setupListWidget();

    leftLayout->addLayout(hlayout);
    leftLayout->addWidget(sessionList);

    /* 右侧聊天区域 */
    QWidget *rightPanel = new QWidget;
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);
    rightLayout->setSpacing(0);
    rightLayout->setContentsMargins(0, 0, 0, 0);

    // 标题栏
    QWidget *header = new QWidget;
    header->setFixedHeight(60);
    header->setStyleSheet("background: #FFB6C1; border-bottom: 1px solid #ADD8E6;");

    QHBoxLayout *headerLayout = new QHBoxLayout(header);
    chatTitle = new QLabel("选择一个会话");
    chatTitle->setStyleSheet("QLabel { font-weight: bold; color: #FFFFFF; }");
    headerLayout->addWidget(chatTitle);
    headerLayout->addStretch();

    // 聊天内容区域（使用堆栈窗口）
    chatStack = new QStackedWidget;

    // 默认空页面
    QWidget *emptyPage = new QWidget;
    QVBoxLayout *emptyLayout = new QVBoxLayout(emptyPage);
    QLabel *emptyLabel = new QLabel("请从左侧选择会话");
    emptyLabel->setAlignment(Qt::AlignCenter);
    emptyLabel->setStyleSheet("QLabel { color: #888888; font-size: 16px; }");
    emptyLayout->addWidget(emptyLabel);
    chatStack->addWidget(emptyPage);

    rightLayout->addWidget(header);
    rightLayout->addWidget(chatStack);

    // 添加到分割器
    splitter->addWidget(leftPanel);
    splitter->addWidget(rightPanel);
    splitter->setSizes({300, 700});

    mainLayout->addWidget(splitter);

    // 连接信号
    connect(sessionList, &QListWidget::currentItemChanged, this, &MessageWidget::onSessionChanged);
    connect(searchbtn,SIGNAL(clicked()),this,SLOT(onSearchFriend()));
}

void MessageWidget::addfriend(FriendInfo finfo)
{
    FriendListItem *item = new FriendListItem(finfo);
    sessionList->addItem(item);

    // 创建对应的聊天窗口
    ChatWidget *chat = new ChatWidget(this, clen);
    chat->setmyid(myid);
    chat->setcurrentid(finfo.userID);
    chatWidgets.insert(finfo.userID, chat);
    chatStack->addWidget(chat);
    friendlist->insert(finfo.name,finfo.userID);
    connect(chat,&ChatWidget::addchatlog,this,&MessageWidget::onaddlog);
}

// 根据好友ID查找并选中列表项
void MessageWidget::selectFriendInList(const QString &friendId)
{
    // 遍历列表查找对应的好友项
    for (int i = 0; i < sessionList->count(); i++) {
        FriendListItem *item = dynamic_cast<FriendListItem*>(sessionList->item(i));
        if (item && item->getid() == friendId) {
            // 找到了对应的项，设置为当前项
            sessionList->setCurrentItem(item);
            return;
        }
    }
}

void MessageWidget::onSearchFriend()
{
    QString searchtext = searchBox->displayText();
    bool isnum;
    int id = 0;
    id = searchtext.toInt(&isnum);

    if(isnum)
    {
        //如果是为纯数字就搜索id
        for (const auto &key : friendlist->keys()) {
            if (searchtext == friendlist->value(key))
            {
                selectFriendInList(searchtext);
                return;
            }
        }
        QString informstr = QString("不存在此好友\n是否搜索并请求添加id为 %1 的用户为好友").arg(searchtext);
        //弹出框询问是否搜索并添加好友
        QMessageBox::StandardButton result = QMessageBox::information(this, "好友请求", informstr, QMessageBox::Yes|QMessageBox::No);
        if(result == QMessageBox::Yes)
            emit addfriendbyid(searchtext);
    }
    else
    {
        //存在定位到好友
        if (friendlist->contains(searchtext))
        {
            QString friendId = friendlist->value(searchtext);
            selectFriendInList(friendId);
        }
        else
        {
            QString informstr = QString("不存在此好友\n是否搜索并请求添加昵称为 %1 的用户为好友").arg(searchtext);
            //弹出框询问是否搜索并添加好友
            QMessageBox::StandardButton result = QMessageBox::information(this, "好友请求", informstr, QMessageBox::Yes|QMessageBox::No);
            if(result == QMessageBox::Yes)
                emit addfriendbyname(searchtext);
        }
    }

}
void MessageWidget::initlog(){
    QList<Message> totallog=database->getAllMessages();
    for(int i = 0; i < totallog.count(); i++) {
        // 只处理与当前用户相关的消息
        if(totallog[i].receiveid == myid || totallog[i].sendid == myid) {
            QString chatWidgetKey;

            if(totallog[i].receiveid == myid) {
                chatWidgetKey = totallog[i].sendid;
            } else {
                chatWidgetKey = totallog[i].receiveid;
            }

            // 检查键是否存在
            if(chatWidgets.contains(chatWidgetKey)) {
                ChatWidget* widget = chatWidgets.value(chatWidgetKey);
                if(widget != nullptr) {
                    widget->loadinglog(totallog[i]);
                }
            }
        }
    }
}

void MessageWidget::initfriend(FriendListMessage f)
{
    //解析好友列表
    for (const auto& friendInfo : f.friends) {
        FriendListItem *item = new FriendListItem(friendInfo);
        sessionList->addItem(item);

        // 创建对应的聊天窗口
        ChatWidget *chat = new ChatWidget(this, clen);
        chat->setmyid(myid);
        chat->setcurrentid(friendInfo.userID);
        chatWidgets.insert(friendInfo.userID, chat);
        chatStack->addWidget(chat);
        friendlist->insert(friendInfo.name,friendInfo.userID);
        connect(chat,&ChatWidget::addchatlog,this,&MessageWidget::onaddlog);
    }

    //加载聊天记录
    initlog();
}

void MessageWidget::onSessionChanged(QListWidgetItem *current)
{
    if (!current) {
        // 没有选中任何会话时显示默认空页面
        chatTitle->setText("选择一个会话");
        chatStack->setCurrentIndex(0);
        return;
    }

    FriendListItem *friendItem = dynamic_cast<FriendListItem*>(current);
    if (!friendItem) return;

    // 更新标题
    chatTitle->setText(friendItem->text());

    // 切换到对应的聊天窗口
    QString friendId = friendItem->getid();
    if (chatWidgets.contains(friendId)) {
        chatStack->setCurrentWidget(chatWidgets.value(friendId));
    }
}

void MessageWidget::setupListWidget() {
    sessionList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(sessionList, &QListWidget::customContextMenuRequested,
            this, &MessageWidget::showFriendContextMenu);
}

void MessageWidget::showFriendContextMenu(const QPoint &pos) {
    QListWidgetItem *item = sessionList->itemAt(pos);
    if (!item) return;

    FriendListItem *friendItem = dynamic_cast<FriendListItem*>(item);
    if (!friendItem) return;

    QMenu menu;
    QAction *viewAction = menu.addAction("查看好友信息");
    QAction *removeAction = menu.addAction("删除好友");

    QAction *selected = menu.exec(sessionList->viewport()->mapToGlobal(pos));
    if (selected == viewAction) {
        QDialog dialog(this);
        dialog.setWindowTitle("好友信息");
        dialog.setFixedSize(300, 200);

        QVBoxLayout layout(&dialog);
        QLabel nameLabel("姓名: " + friendItem->info().name);
        layout.addWidget(&nameLabel);
        dialog.exec();
    } else if (selected == removeAction) {
        // 删除好友逻辑
    }
}

void MessageWidget::onaddlog(const Message &msg)
{
    database->insertMessage(msg);
}
