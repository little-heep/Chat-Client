#include "personalwidget.h"
#include "passwordeditmessagebox.h"

PersonalWidget::PersonalWidget(const QString id,const QString name,QWidget *parent)
    : QWidget{parent}
{
    mid=id;
    mname=name;
    setupUI();
    applyStyle();
}

void PersonalWidget::onAvatarClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("选择头像"), "",
                                                    tr("图片文件 (*.png *.jpg *.jpeg *.bmp)"));
    if (!fileName.isEmpty()) {
        QPixmap pixmap(fileName);
        if (!pixmap.isNull()) {
            // 圆形裁剪
            QPixmap circularPixmap = getCircularPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            avatarLabel->setPixmap(circularPixmap);
        }
    }
}

void PersonalWidget::onSaveClicked()
{
    if (nicknameEdit->text().isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("昵称不能为空"));
        return;
    }


    // 这里添加保存逻辑
    emit changename(nicknameEdit->text());
}

void PersonalWidget::onPWDchanged()
{
    PasswordEditMessageBox dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString currentPassword = dialog.getCurrentPassword();
        QString newPassword = dialog.getNewPassword();

        // 向主窗口发送修改密码的信号，然后发送给服务端消息
        emit changepwd(currentPassword,newPassword);
    }
}

void PersonalWidget::setupUI()
{
    // 主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    // 标题
    QLabel *titleLabel = new QLabel(tr("个人信息"));
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setObjectName("titleLabel");
    mainLayout->addWidget(titleLabel);

    // 头像部分
    QHBoxLayout *avatarLayout = new QHBoxLayout();
    avatarLayout->setAlignment(Qt::AlignCenter);

    avatarLabel = new QLabel();
    avatarLabel->setFixedSize(100, 100);
    avatarLabel->setAlignment(Qt::AlignCenter);
    avatarLabel->setCursor(Qt::PointingHandCursor);
    avatarLabel->setPixmap(getCircularPixmap(QPixmap(":/new/prefix1/images/head.png").scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation)));

    avatarLayout->addWidget(avatarLabel);
    mainLayout->addLayout(avatarLayout);

    // 昵称编辑
    QHBoxLayout *nicknameLayout = new QHBoxLayout();
    QLabel *nicknameTitle = new QLabel(tr("昵称:"));
    nicknameTitle->setFixedWidth(100);
    nicknameEdit = new QLineEdit();
    nicknameEdit->setPlaceholderText(mname);
    nicknameLayout->addWidget(nicknameTitle);
    nicknameLayout->addWidget(nicknameEdit);
    mainLayout->addLayout(nicknameLayout);

    //修改密码链接
    passwordedit=new QPushButton(tr("修改密码"));
    passwordedit->setObjectName("passwordedit");  // 添加这行设置对象名，方便进行样式设计
    mainLayout->addWidget(passwordedit,0,Qt::AlignLeft);

    //添加一些空白填充下部
    QWidget *blackwidg = new QWidget(this);
    blackwidg->setMinimumHeight(80);  // 设置更大的高度
    mainLayout->addWidget(blackwidg, 1);  // 添加 stretch 因子

    // 保存按钮
    saveButton = new QPushButton(tr("保存修改"));
    saveButton->setCursor(Qt::PointingHandCursor);
    mainLayout->addWidget(saveButton, 0, Qt::AlignRight);

    // 连接信号槽
    //connect(avatarLabel, &QLabel::clicked, this, &PersonalWidget::onAvatarClicked);
    connect(saveButton, &QPushButton::clicked, this, &PersonalWidget::onSaveClicked);
    connect(passwordedit,&QPushButton::clicked,this,&PersonalWidget::onPWDchanged);
}

void PersonalWidget::applyStyle()
{
    this->setStyleSheet(R"(
            PersonalWidget {
                background-color: #fff0f5;
                border-radius: 15px;
            }

            #titleLabel {
                font-size: 20px;
                font-weight: bold;
                color: #ff69b4;
                padding-bottom: 10px;
                height：50
            }

            QPushButton#passwordedit {
                background: transparent;
                color: #FFC6C7;
                border: none;
                text-decoration: underline;
                padding: 0;
                min-width: auto;
            }

            QPushButton#passwordedit:hover {
                color: #ff69b4;
            }

            QLabel {
                color: #db7093;
                font-size: 14px;
            }

            QLineEdit {
                border: 1px solid #ffb6c1;
                border-radius: 10px;
                padding: 8px;
                font-size: 14px;
                background-color: white;
                selection-background-color: #ffb6c1;
            }

            QLineEdit:focus {
                border: 1px solid #ff69b4;
            }

            QPushButton {
                background-color: #ff69b4;
                color: white;
                border: none;
                border-radius: 10px;
                padding: 10px 25px;
                font-size: 14px;
                min-width: 120px;
            }

            QPushButton:hover {
                background-color: #ff1493;
            }

            QPushButton:pressed {
                background-color: #c71585;
            }
        )");
}

QPixmap PersonalWidget::getCircularPixmap(const QPixmap &source)
{
    QPixmap result(source.size());
    result.fill(Qt::transparent);

    QPainter painter(&result);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QPainterPath path;
    path.addEllipse(result.rect());
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, source);

    return result;
}

void PersonalWidget::pwdchangestatus(QString status,QString msg)
{
    if(status=="success")
        QMessageBox::information(this,"成功","密码修改成功");
    else
        QMessageBox::critical(this,"失败",msg);
}
void PersonalWidget::namechangestatus(QString status)
{
    if(status=="success")
        QMessageBox::information(this,"成功","昵称修改成功");
    else
        QMessageBox::critical(this,"失败","昵称修改失败");
}

