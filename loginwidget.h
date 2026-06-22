#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QCheckBox>
#include <QMessageBox>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QToolButton>
#include <QStyle>
#include <QJsonObject>
#include <QJsonDocument>
#include "mywindow.h"
#include "client.h"

class RoundedWidget : public QWidget {
public:
    RoundedWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setAttribute(Qt::WA_TranslucentBackground);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QPainterPath path;
        path.addRoundedRect(rect(), 15, 15);

        // 垂直多色渐变（顶部粉色到底部白色）
        QLinearGradient gradient(0, 0, 0, height());  // 垂直渐变
        gradient.setColorAt(0, QColor(255, 182, 193)); // 顶部粉红色
        gradient.setColorAt(0.3, QColor(255, 200, 220)); // 中等粉色
        gradient.setColorAt(0.7, QColor(255, 240, 245)); // 淡粉色
        gradient.setColorAt(1, Qt::white);             // 底部白色

        painter.fillPath(path, gradient);
    }
};

class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = nullptr);

signals:

private slots:
    void onLoginClicked();
    void onRegisterSwitch();
    void success(QString id);
    void fail(QString m);
    void registerSuccess(uint userid, QString message);
    void registerFail(QString message);

private:
    bool isRegisterMode = false;
    QLabel *avatarLabel;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPropertyAnimation *fadeAnimation;
    QPoint m_dragPosition;
    MyWindow *w;
    client *c;
    QJsonObject user;
    QPushButton *loginButton;
    QPushButton *registerLink;
private:
    void setupUI();
    void setupLineEdit(QLineEdit *edit, const QString &placeholder);
    void setupAnimations();
    void setupEffects();
    void shakeAnimation();
    void setAvatar(const QString &imagePath);//设置头像

    // 重写鼠标事件实现窗口拖动
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

};

#endif // LOGINWIDGET_H
