#ifndef PERSONALWIDGET_H
#define PERSONALWIDGET_H

#include <QWidget>

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QPainterPath>

class PersonalWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PersonalWidget(const QString id,const QString name,QWidget *parent = nullptr);

signals:
    void changepwd(QString oldpwd,QString newpwd);//修改密码信号
    void changename(QString name);//修改昵称信号

private slots:
    void onAvatarClicked();
    void onSaveClicked();
    void onPWDchanged();
    void pwdchangestatus(QString status,QString msg);
    void namechangestatus(QString status);

private:
    QLabel *avatarLabel;
    QLineEdit *nicknameEdit;
    QLineEdit *currentPasswordEdit;
    QLineEdit *newPasswordEdit;
    QLineEdit *confirmPasswordEdit;
    QPushButton *saveButton;
    QPushButton *cancelbtn;
    QPushButton *passwordedit;

    QString mname;
    QString mheadpath;
    QString mid;
    QString newpsd;

    void setupUI();

    void applyStyle();

    QPixmap getCircularPixmap(const QPixmap &source);
};

#endif // PERSONALWIDGET_H
