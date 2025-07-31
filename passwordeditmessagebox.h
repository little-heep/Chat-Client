#ifndef PASSWORDEDITMESSAGEBOX_H
#define PASSWORDEDITMESSAGEBOX_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>

class PasswordEditMessageBox : public QDialog
{
    Q_OBJECT

public:
    PasswordEditMessageBox(QWidget *parent = nullptr);

    QString getCurrentPassword() const { return currentPasswordEdit->text(); }
    QString getNewPassword() const { return newPasswordEdit->text(); }
    QString getConfirmPassword() const { return confirmPasswordEdit->text(); }

private slots:
    void onConfirmClicked();

private:
    QLineEdit *currentPasswordEdit;
    QLineEdit *newPasswordEdit;
    QLineEdit *confirmPasswordEdit;

    void setupUI();

    void applyStyle();
};

#endif // PASSWORDEDITMESSAGEBOX_H
