#include "passwordeditmessagebox.h"

PasswordEditMessageBox::PasswordEditMessageBox(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("修改密码"));
    setFixedSize(350, 400);
    setupUI();
    applyStyle();
}

void PasswordEditMessageBox::onConfirmClicked()
{
    if (currentPasswordEdit->text().isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("请输入当前密码"));
        return;
    }

    if (newPasswordEdit->text().isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("请输入新密码"));
        return;
    }

    if (newPasswordEdit->text() != confirmPasswordEdit->text()) {
        QMessageBox::warning(this, tr("警告"), tr("两次输入的新密码不一致"));
        return;
    }

    if (newPasswordEdit->text().length() < 6) {
        QMessageBox::warning(this, tr("警告"), tr("密码长度不能少于6位"));
        return;
    }

    accept(); // 关闭对话框并返回 QDialog::Accepted
}

void PasswordEditMessageBox::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // 当前密码
    QLabel *currentLabel = new QLabel(tr("当前密码:"));
    currentPasswordEdit = new QLineEdit();
    currentPasswordEdit->setEchoMode(QLineEdit::Password);
    currentPasswordEdit->setPlaceholderText(tr("请输入当前密码"));
    mainLayout->addWidget(currentLabel);
    mainLayout->addWidget(currentPasswordEdit);

    // 新密码
    QLabel *newLabel = new QLabel(tr("新密码:"));
    newPasswordEdit = new QLineEdit();
    newPasswordEdit->setEchoMode(QLineEdit::Password);
    newPasswordEdit->setPlaceholderText(tr("请输入新密码"));
    mainLayout->addWidget(newLabel);
    mainLayout->addWidget(newPasswordEdit);

    // 确认密码
    QLabel *confirmLabel = new QLabel(tr("确认密码:"));
    confirmPasswordEdit = new QLineEdit();
    confirmPasswordEdit->setEchoMode(QLineEdit::Password);
    confirmPasswordEdit->setPlaceholderText(tr("请再次输入新密码"));
    mainLayout->addWidget(confirmLabel);
    mainLayout->addWidget(confirmPasswordEdit);

    // 按钮布局
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(15);

    QPushButton *cancelButton = new QPushButton(tr("取消"));
    QPushButton *confirmButton = new QPushButton(tr("确认"));

    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(confirmButton);

    mainLayout->addLayout(buttonLayout);

    // 连接信号槽
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(confirmButton, &QPushButton::clicked, this, &PasswordEditMessageBox::onConfirmClicked);
}

void PasswordEditMessageBox::applyStyle()
{
    this->setStyleSheet(R"(
            PasswordChangeDialog {
                background-color: #fff0f5;
                border-radius: 10px;
            }

            QLabel {
                color: #db7093;
                font-size: 14px;
            }

            QLineEdit {
                border: 1px solid #ffb6c1;
                border-radius: 8px;
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
                border-radius: 8px;
                padding: 8px 20px;
                font-size: 14px;
                min-width: 80px;
            }

            QPushButton:hover {
                background-color: #ff1493;
            }

            QPushButton:pressed {
                background-color: #c71585;
            }
        )");
}
