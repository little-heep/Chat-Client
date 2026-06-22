#include "loginwidget.h"
LoginWidget::LoginWidget(QWidget *parent)
    : QWidget{parent}
{
    c=new client;
    c->startCommunication();
    setupUI();
    setupAnimations();
    setupEffects();
    setAvatar(":/new/prefix1/images/head.png");

    connect(c,&client::loginfail,this,&LoginWidget::fail);
    connect(c,&client::loginsucess,this,&LoginWidget::success);
    connect(c,&client::registerSuccess,this,&LoginWidget::registerSuccess);

    connect(c,&client::registerFail, this,&LoginWidget::registerFail);
}

void LoginWidget::onLoginClicked() {
    if (usernameEdit->text().isEmpty() || passwordEdit->text().isEmpty()) {
        shakeAnimation();
        QMessageBox::warning(this, "错误", "用户名和密码不能为空");
    } else {
        user["type"] = isRegisterMode ? "register" : "login";
        user["name"]=usernameEdit->text();
        user["pwd"]=passwordEdit->text();
        c->sendJsonMessage(user);
    }
}

void LoginWidget::setAvatar(const QString &imagePath) {
    QPixmap pixmap(imagePath);
    if(!pixmap.isNull()) {
        // 创建圆形头像
        QPixmap circularPixmap(pixmap.size());
        circularPixmap.fill(Qt::transparent);

        QPainter painter(&circularPixmap);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

        QPainterPath path;
        path.addEllipse(0, 0, pixmap.width(), pixmap.height());
        painter.setClipPath(path);
        painter.drawPixmap(0, 0, pixmap);

        avatarLabel->setPixmap(circularPixmap.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void LoginWidget::setupUI() {
    // 设置窗口属性
    setWindowTitle("登录");
    setFixedSize(400, 500);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);

    // 主容器
    RoundedWidget *mainWidget = new RoundedWidget(this);
    mainWidget->setFixedSize(380, 480);
    mainWidget->move(10, 10);

    // 关闭按钮
    QToolButton *closeButton = new QToolButton(mainWidget);
    closeButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    closeButton->setStyleSheet(
        "QToolButton {"
        "   background: transparent;"
        "   border: none;"
        "   padding: 5px;"
        "}"
        "QToolButton:hover {"
        "   background: #ff9999;"
        "   border-radius: 10px;"
        "}"
        );
    closeButton->setGeometry(350, 10, 20, 20);
    connect(closeButton, &QToolButton::clicked, this, &QWidget::close);

    // 主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->setContentsMargins(40, 50, 40, 30);
    mainLayout->setSpacing(20);

    // 头像标签
    avatarLabel = new QLabel();
    avatarLabel->setAlignment(Qt::AlignCenter);
    avatarLabel->setFixedSize(80, 80);
    avatarLabel->setStyleSheet(
        "QLabel {"
        "   border: 2px solid white;"
        "   border-radius: 40px;" // 圆形
        "   background-color: transparent;"
        "}"
        );


    // 头像容器布局
    QVBoxLayout *avatarLayout = new QVBoxLayout();
    avatarLayout->addWidget(avatarLabel, 0, Qt::AlignCenter);

    // 用户名输入框
    usernameEdit = new QLineEdit;
    setupLineEdit(usernameEdit, "用户名");

    // 密码输入框
    passwordEdit = new QLineEdit;
    setupLineEdit(passwordEdit, "密码");
    passwordEdit->setEchoMode(QLineEdit::Password);

    // 记住密码复选框
    QCheckBox *rememberCheck = new QCheckBox("记住密码");
    rememberCheck->setStyleSheet(
        "QCheckBox { color: #FFC6C7; }"
        "QCheckBox::indicator { width: 16px; height: 16px; }"
        "QCheckBox::indicator:checked { background-color: #ff4081; }"
        );

    // 登录按钮
    loginButton = new QPushButton("登 录");
    loginButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #ff4081;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 5px;"
        "   padding: 12px;"
        "   font-size: 16px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #f50057;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #c51162;"
        "}"
        );

    // 底部链接
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->setContentsMargins(0, 10, 0, 0);
    bottomLayout->setSpacing(15);

    registerLink = new QPushButton("注册账号");
    QPushButton *forgotLink = new QPushButton("忘记密码?");

    QString linkStyle = "QPushButton {"
                        "   background: transparent;"
                        "   color: #FFC6C7;"
                        "   border: none;"
                        "}"
                        "QPushButton:hover {"
                        "   color: #ff4081;"
                        "   text-decoration: underline;"
                        "}";

    registerLink->setStyleSheet(linkStyle);
    forgotLink->setStyleSheet(linkStyle);

    bottomLayout->addWidget(registerLink);
    bottomLayout->addStretch();
    bottomLayout->addWidget(forgotLink);

    // 添加到主布局
    mainLayout->addLayout(avatarLayout);
    mainLayout->addWidget(usernameEdit);
    mainLayout->addWidget(passwordEdit);
    mainLayout->addWidget(rememberCheck);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(loginButton);
    mainLayout->addLayout(bottomLayout);

    // 连接信号槽
    connect(loginButton, &QPushButton::clicked, this, &LoginWidget::onLoginClicked);
    connect(registerLink, &QPushButton::clicked, this, &LoginWidget::onRegisterSwitch);
}

void LoginWidget::setupLineEdit(QLineEdit *edit, const QString &placeholder) {
    edit->setPlaceholderText(placeholder);
    edit->setStyleSheet(
        "QLineEdit {"
        "   border: 1px solid #ffcdd2;"
        "   border-radius: 5px;"
        "   padding: 10px;"
        "   font-size: 14px;"
        "   background: rgba(255, 255, 255, 150);"
        "}"
        "QLineEdit:focus {"
        "   border: 1px solid #ff4081;"
        "}"
        );
    edit->setMinimumHeight(40);
}

void LoginWidget::setupAnimations() {
    // 淡入动画
    fadeAnimation = new QPropertyAnimation(this, "windowOpacity");
    fadeAnimation->setDuration(300);
    fadeAnimation->setStartValue(0);
    fadeAnimation->setEndValue(1);
    fadeAnimation->start();
}

void LoginWidget::setupEffects() {
    // 阴影效果
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(20);
    shadowEffect->setColor(QColor(0, 0, 0, 100));
    shadowEffect->setOffset(0, 5);
    setGraphicsEffect(shadowEffect);
}

void LoginWidget::shakeAnimation() {
    QPropertyAnimation *animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(100);
    animation->setLoopCount(3);
    animation->setKeyValueAt(0, pos());
    animation->setKeyValueAt(0.2, pos() + QPoint(5, 0));
    animation->setKeyValueAt(0.4, pos() + QPoint(-5, 0));
    animation->setKeyValueAt(0.6, pos() + QPoint(5, 0));
    animation->setKeyValueAt(0.8, pos() + QPoint(-5, 0));
    animation->setKeyValueAt(1, pos());
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void LoginWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void LoginWidget::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPos() - m_dragPosition);
        event->accept();
    }
}

void LoginWidget::success(QString id)
{
    w=new MyWindow(id,usernameEdit->text(),c);
    this->close();
    w->show();
}
void LoginWidget::fail(QString m)
{
    QMessageBox::critical(this,"登录错误",m);
    c->startCommunication();
}

void LoginWidget::onRegisterSwitch()
{
    isRegisterMode = !isRegisterMode;

    if(isRegisterMode)
    {
        loginButton->setText("注 册");
        registerLink->setText("返回登录");
        setWindowTitle("注册");
    }
    else
    {
        loginButton->setText("登 录");
        registerLink->setText("注册账号");
        setWindowTitle("登录");
    }
}

void LoginWidget::registerSuccess(uint userid, QString message)
{
    QMessageBox::information(
        this,
        "注册成功",
        QString("%1\n您的用户ID：%2,可以进行登录")
            .arg(message)
            .arg(userid));

    // 切回登录模式
    isRegisterMode = false;
    loginButton->setText("登 录");
    registerLink->setText("注册账号");
    setWindowTitle("登录");

    // 可以保留用户名，清空密码
    passwordEdit->clear();
}

void LoginWidget::registerFail(QString message)
{
    QMessageBox::warning(
        this,
        "注册失败",
        message);
}
