#include "linemessage.h"

LineMessage::LineMessage(bool isme,QString head,QString content,QDateTime *sendtime,QWidget *parent)
    : QWidget{parent}
{
    height=60;

    //主布局
    QHBoxLayout *hlay = new QHBoxLayout(this);
    hlay->setSpacing(10);
    hlay->setContentsMargins(10, 5, 10, 5);

    //放内容
    QVBoxLayout *vlay = new QVBoxLayout();
    vlay->setSpacing(0);
    vlay->setContentsMargins(0, 0, 0, 0);

    //放头像
    QVBoxLayout *vlayhead = new QVBoxLayout();

    QLabel *headlab = new QLabel();
    QPixmap original(head);
    QPixmap scaled = original.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    headlab->setPixmap(scaled);
    headlab->setFixedSize(40, 40);
    vlayhead->addWidget(headlab);
    vlayhead->addStretch();

    //内容
    QWidget *wigTitle = new QWidget();
    QWidget *wigMsg = new QWidget();
    QHBoxLayout *titleLayout = new QHBoxLayout(wigTitle);
    QHBoxLayout *msgLayout = new QHBoxLayout(wigMsg);
    titleLayout->setContentsMargins(0, 0, 0, 0);
    msgLayout->setContentsMargins(0, 0, 0, 0);
    
    QLabel *labtitle = new QLabel();
    QLabel *labmsg = new QLabel();
    labmsg->setWordWrap(true);
    
    titleLayout->addWidget(labtitle);
    msgLayout->addWidget(labmsg);
    
    // 设置标签样式
    labmsg->setStyleSheet("QLabel { color: black; }");
    labtitle->setStyleSheet("QLabel { color: gray; }");
    
    // 设置固定的标题宽度
    wigTitle->setFixedWidth(120);
    
    // 计算消息气泡的宽度和高度
    QFontMetrics fm(labmsg->font());
    int maxWidth = 200; // 最大宽度
    int minWidth = 30; // 最小宽度
    int padding = 20;   // 内边距

    // 计算文本的显示尺寸（考虑自动换行）
    QRect textRect = fm.boundingRect(
        0, 0, maxWidth - padding-10, 0, // 可用宽度 = maxWidth - padding
        Qt::TextWordWrap,            // 启用自动换行
        content                      // 文本内容
        );

    // 设置消息气泡的宽度（不能超过 maxWidth）
    int bubbleWidth = qMin(textRect.width() + padding+10, maxWidth);
    bubbleWidth = qMax(bubbleWidth, minWidth); // 不低于 minWidth
    // 设置消息气泡的高度
    int bubbleHeight = textRect.height() + padding;

    wigMsg->setFixedWidth(bubbleWidth);
    wigMsg->setFixedHeight(bubbleHeight);
    /*
    // 根据内容调整消息气泡宽度
    QFontMetrics fm(labmsg->font());
    int textWidth = fm.horizontalAdvance(content);
    int maxWidth = 200; // 最大宽度
    int minWidth = 100; // 最小宽度
    
    // 如果文本宽度超过最大宽度，启用自动换行
    if (textWidth > maxWidth) {
        wigMsg->setFixedWidth(maxWidth);
        labmsg->setWordWrap(true);
    } else {
        // 否则使用实际文本宽度，但不小于最小宽度
        wigMsg->setFixedWidth(qMax(textWidth, minWidth)); // 加上padding
    }
*/
    // 设置消息气泡样式
    QString msgStyle = isme ?
                           "background-color: #95EC69; border-radius: 10px; padding: 10px;" :
                           "background-color: #FFFFFF; border-radius: 10px; padding: 10px;";
    wigMsg->setStyleSheet(msgStyle);
    QString txtTitle=sendtime->toString("yyyy-MM-dd HH:mm");
    labtitle->setText(txtTitle);
    labtitle->setMinimumWidth(60);
    labmsg->setText(content);
    //labmsg->setMinimumWidth(bubbleWidth);
    labmsg->adjustSize();

    // 设置标题高度
    QFontMetrics fontm(labmsg->font());
    int titleHeight = fontm.height() + 10;
    wigTitle->setFixedHeight(titleHeight);
/*
    // 计算消息实际需要的高度
    labmsg->adjustSize();
    int msgHeight = labmsg->height();
    wigMsg->setMinimumHeight(msgHeight);
*/
    // 更新整体高度
    height = titleHeight + bubbleHeight + 10; // 加上布局间距

    // 根据是否是自己发送的消息设置对齐方式
    if (isme) {

        titleLayout->setAlignment(Qt::AlignRight);
        msgLayout->setAlignment(Qt::AlignRight);
        labtitle->setAlignment(Qt::AlignRight);
        labmsg->setAlignment(Qt::AlignRight);
    } else {
        titleLayout->setAlignment(Qt::AlignLeft);
        msgLayout->setAlignment(Qt::AlignLeft);
        labtitle->setAlignment(Qt::AlignLeft);
        labmsg->setAlignment(Qt::AlignLeft);
    }
    
    vlay->addWidget(wigTitle, 0, Qt::AlignTop);  // 确保标题在最上面

    if(isme) { //如果是自己发信息显示在右边
        vlay->addWidget(wigMsg,0,Qt::AlignRight);
        hlay->addStretch();
        hlay->addLayout(vlay);
        hlay->addLayout(vlayhead);
    } else { //如果是好友的消息显示在左边
        vlay->addWidget(wigMsg,0,Qt::AlignLeft);
        hlay->addLayout(vlayhead);
        hlay->addLayout(vlay);
        hlay->addStretch();
    }

    // this->setStyleSheet("background-color: red;");
    //固定高度大小
    this->setGeometry(0,0,bubbleWidth>120?bubbleWidth+40:160,height);
    this->setMinimumHeight(height);
    this->setMaximumHeight(height);

    this->setLayout(hlay);
}
