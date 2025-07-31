#include "filelinemessage.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDesktopServices>
#include <QUrl>
#include <QFileInfo>
#include <QDebug>

FileLineMessage::FileLineMessage(const QString filepath,QString head,bool isme,QWidget *parent)
    : QWidget{parent}
{
    file=filepath;
    setMinimumSize(200, 50);
    setFixedHeight(70);
    //放头像
    QVBoxLayout *vlayhead = new QVBoxLayout();

    QLabel *headlab = new QLabel();
    QPixmap original(head);
    QPixmap scaled = original.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    headlab->setPixmap(scaled);
    headlab->setFixedSize(40, 40);
    vlayhead->addWidget(headlab);
    vlayhead->addStretch();

    //放内容
    QHBoxLayout *hlaydetail=new QHBoxLayout();
    hlaydetail->setContentsMargins(0,0,0,0);

    detaillab=new QLabel();
    //获取文件信息
    QFileInfo fileInfo(file);
    if (!fileInfo.exists()) {
        qDebug() << "文件不存在：" << file;
        return;
    }
    // 文件名（不含路径）
    QString fileName = fileInfo.fileName();
    // 文件大小（字节）
    qint64 fileSize = fileInfo.size();
    // 格式化文件大小（KB/MB/GB）
    QString formattedSize;
    if (fileSize < 1024) {
        formattedSize = QString("%1 字节").arg(fileSize);
    } else if (fileSize < 1024 * 1024) {
        formattedSize = QString("%1 KB").arg(fileSize / 1024.0, 0, 'f', 2);
    } else if (fileSize < 1024 * 1024 * 1024) {
        formattedSize = QString("%1 MB").arg(fileSize / (1024.0 * 1024), 0, 'f', 2);
    } else {
        formattedSize = QString("%1 GB").arg(fileSize / (1024.0 * 1024 * 1024), 0, 'f', 2);
    }
    detaillab->setText(fileName+"\n"+formattedSize);

    filebtn=new QPushButton();
    filebtn->setIcon(QIcon(":/new/prefix1/images/file.png"));
    filebtn->setFixedSize(40, 40);

    filebtn->setStyleSheet(
        "QPushButton {"
        "    margin: 0px; padding: 0px;"  // 去除边距和内边距
        "    background: transparent;"  // 背景透明
        "    vertical-align: top;"  // 顶部对齐
        "}"
        );
    connect(filebtn,&QPushButton::clicked,this,&FileLineMessage::onclicked);

    QWidget *detailwig=new QWidget();
    // 设置消息气泡样式
    QString msgStyle = isme ?
                           "background-color: #95EC69; border-radius: 10px; padding: 10px;" :
                           "background-color: #FFFFFF; border-radius: 10px; padding: 10px;";
    detailwig->setStyleSheet(msgStyle);
    detailwig->setLayout(hlaydetail);

    QHBoxLayout *mainlay=new QHBoxLayout(this);
    mainlay->setContentsMargins(0,0,0,0);
    if(isme)
    {
        detaillab->setAlignment(Qt::AlignRight);
        hlaydetail->addWidget(detaillab);
        hlaydetail->addWidget(filebtn);
        hlaydetail->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        mainlay->setAlignment(Qt::AlignRight);
        mainlay->addStretch();  // 关键：左侧拉伸
        mainlay->addWidget(detailwig);
        mainlay->addLayout(vlayhead);
    }
    else{
        detaillab->setAlignment(Qt::AlignLeft);
        hlaydetail->addWidget(filebtn);
        hlaydetail->addWidget(detaillab);
        hlaydetail->setAlignment(Qt::AlignTop | Qt::AlignRight);
        mainlay->setAlignment(Qt::AlignLeft);
        mainlay->addLayout(vlayhead);
        mainlay->addWidget(detailwig);
        mainlay->addStretch();
    }
    hlaydetail->setSpacing(0);  // 设置水平布局中间距为2px
    mainlay->setSpacing(0);     // 设置主布局中间距为2px
}

void FileLineMessage::onclicked()
{
    // 使用文件资源管理器打开所在目录并选中文件
    QFileInfo fileInfo(file);
    QDesktopServices::openUrl(QUrl::fromLocalFile(fileInfo.absolutePath()));
}
