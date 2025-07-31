#include "chatwidget.h"
#include <QDebug>
#include <QFileDialog>
#include "filelinemessage.h"

ChatWidget::ChatWidget(QWidget *parent ,client *c)
    : QWidget{parent}
{
    clen=c;

    sp=new QSplitter(Qt::Vertical,this);
    send = new QPushButton("发送");
    sendfile=new QPushButton("发送文件");

    send->setIcon(QIcon(":/new/prefix1/images/send.png"));
    ed= new QTextEdit();

    showarea = new QScrollArea(sp);
    QWidget* container = new QWidget(showarea);
    msglayout = new QVBoxLayout(container);
    msglayout->setAlignment(Qt::AlignTop);
    container->setLayout(msglayout);
    showarea->setWidget(container);
    showarea->setWidgetResizable(true);

    QWidget *qw=new QWidget(sp);
    lay=new QVBoxLayout(qw);
    lay->addWidget(ed);
    QHBoxLayout *sendlay=new QHBoxLayout();
    sendlay->addWidget(sendfile);
    sendlay->addWidget(send);
    lay->addLayout(sendlay);

    sp->setStretchFactor(0,4);
    sp->setStretchFactor(1,1);

    // 设置 QSplitter 作为主窗口的中心部件,使其可以随窗口大小变化
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(sp);
    setLayout(mainLayout);

    firstshow=false;
    dealfile=new fileHandle();

    connect(send,SIGNAL(clicked()),this,SLOT(sendFun()));
    connect(clen, &client::messageLogged, this, &ChatWidget::appendLog);
    connect(sendfile,SIGNAL(clicked()),this,SLOT(onsendfile()));
    connect(clen,SIGNAL(fileReceived(QString,QString)),this,SLOT(onfileReceived(QString,QString)));

    setstyle();

}

void ChatWidget::loadinglog(Message &msg)
{
    if(msg.content.startsWith("file:"))
    {
        QString filepath=msg.content.mid(5);
        FileLineMessage *fl=new FileLineMessage(filepath,":/new/prefix1/images/head.png",id==msg.sendid,this);
        msglayout->addWidget(fl);
    }
    else{
        LineMessage *lm=new LineMessage(id==msg.sendid,":/new/prefix1/images/head.png",msg.content,&msg.sendTime,this);
        msglayout->addWidget(lm);
    }

}

void ChatWidget::onfileReceived(const QString sendid,const QString filepath)
{
    qDebug()<<"发送者id"<<sendid<<"当前好友id："<<currentfriendid<<"收到的文件："<<filepath;
    if(sendid==currentfriendid)
    {
        qDebug()<<"开始构建好友发来的filelinemessage";
        FileLineMessage *fl=new FileLineMessage(filepath,":/new/prefix1/images/head.png",false,this);
        msglayout->addWidget(fl);

        //加入数据库聊天消息
        QString context="file:"+filepath;
        Message msg;
        msg.type="message";
        msg.sendid=currentfriendid;
        msg.receiveid=id;
        msg.content=context;
        msg.sendTime=QDateTime::currentDateTime();
        //记录聊天记录
        emit addchatlog(msg);
    }
}

void ChatWidget::onsendfile()
{
    //得到文件路径
    m_fileName=QFileDialog::getOpenFileName(this);
    if(!m_fileName.isEmpty()){
        //调用clen的发送文件函数
        clen->sendfile(m_fileName,id,currentfriendid);
        //构造文件消息
        FileLineMessage *fl=new FileLineMessage(m_fileName,":/new/prefix1/images/head.png",true,this);
        msglayout->addWidget(fl);

        //加入数据库聊天消息
        QString context="file:"+m_fileName;
        Message msg;
        msg.type="message";
        msg.sendid=id;
        msg.receiveid=currentfriendid;
        msg.content=context;
        msg.sendTime=QDateTime::currentDateTime();
        //记录聊天记录
        emit addchatlog(msg);
    }
}

void ChatWidget::setmyid(QString i)
{
    id=i;
}

void ChatWidget::setcurrentid(QString  id)
{
    currentfriendid=id;
}

void ChatWidget::appendLog(QString sendid,QString receiveid,QString content,QDateTime sendtime) {
    if(sendid==id &&receiveid==currentfriendid){//我发送的
        LineMessage *lm=new LineMessage(true,":/new/prefix1/images/head.png",content,&sendtime,this);
        msglayout->addWidget(lm);
    }
    else if(sendid==currentfriendid &&receiveid==id){//好友发送的
        LineMessage *lm=new LineMessage(false,":/new/prefix1/images/head.png",content,&sendtime,this);
        msglayout->addWidget(lm);
    }

}

void ChatWidget::sendFun()
{
    QString message = ed->toPlainText();
    if (message.isEmpty()) {
        qDebug()<<"---------输入为空.\n";
        return;
    }

    Message msg;
    msg.type="message";
    msg.sendid=id;//我自己
    msg.receiveid=currentfriendid;
    msg.content=message;
    msg.sendTime=QDateTime::currentDateTime();

    ed->clear();
    appendLog(msg.sendid,msg.receiveid,msg.content,msg.sendTime);
    if (!clen->isconnected) {
        qDebug()<<message+"\n连接已断开，发送失败\n";
        return;
    }
    //发送消息
    clen->sendJsonMessage(dealfile->messageToJson(msg));
    //记录聊天记录
    emit addchatlog(msg);

}


void ChatWidget::setstyle()
{
    setStyleSheet(getPinkThemeStyleSheet());
    setWindowIcon(QIcon(":/new/prefix1/images/exec.png"));

}

QString ChatWidget::getPinkThemeStyleSheet() {
    return R"(
        /* 全局设置 */
        QWidget {

            font-size: 15px;
        }

        /* 主窗口背景 */
        QWidget#centralWidget {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                          stop:0 #ffb6c1, stop:1 #ffc0cb);
            border: 1px solid #ff9bb2;
            border-radius: 15px;
            padding: 10px;
        }

        /* 按钮样式 */
        QPushButton {
            background-color: #ff9bb2;
            color: white;
            border: none;
            border-radius: 8px;
            padding: 8px 16px;
            min-width: 80px;
            icon-size: 22px;
        }

        QPushButton:hover {
            background-color: #ff1493;
        }

        QPushButton:pressed {
            background-color: #c71585;
        }

        /* 输入框样式 */
        QLineEdit, QTextEdit, QPlainTextEdit {
            background-color: rgba(255, 255, 255, 150);
            border: 1px solid #ff9bb2;
            border-radius: 6px;
            padding: 5px;
            selection-background-color: #ff9bb2;
        }

        /* 复选框和单选按钮 */
        QCheckBox, QRadioButton {
            spacing: 5px;
        }

        QCheckBox::indicator, QRadioButton::indicator {
            width: 16px;
            height: 16px;
        }

        QCheckBox::indicator:checked {
            image: url(:/icons/checked_pink.png);
        }

        /* 组合框 */
        QComboBox {
            background-color: rgba(255, 255, 255, 150);
            border: 1px solid #ff9bb2;
            border-radius: 6px;
            padding: 3px;
        }

        QComboBox::drop-down {
            border: none;
            width: 20px;
        }

        /* 滑块 */
        QSlider::groove:horizontal {
            height: 8px;
            background: #ffb6c1;
            border-radius: 4px;
        }

        QSlider::handle:horizontal {
            background: #ff9bb2;
            border: 1px solid #c71585;
            width: 16px;
            margin: -4px 0;
            border-radius: 8px;
        }

        /* 进度条 */
        QProgressBar {
            border: 1px solid #ff9bb2;
            border-radius: 6px;
            text-align: center;
        }

        QProgressBar::chunk {
            background-color: #ff9bb2;
            width: 10px;
        }

        /* 标签 */
        QLabel {
            color:#74b3ff
        }

        /* 菜单栏 */
        QMenuBar {
            background-color: #ffb6c1;
        }

        QMenuBar::item {
            padding: 5px 10px;
            background: transparent;
        }

        QMenuBar::item:selected {
            background: #ff9bb2;
            color: white;
        }
    )";
}

