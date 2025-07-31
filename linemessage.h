#ifndef LINEMESSAGE_H
#define LINEMESSAGE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDateTime>

class LineMessage : public QWidget
{
    Q_OBJECT
public:
    explicit LineMessage(bool isme,QString head,QString content,QDateTime *sendtime,QWidget *parent = nullptr);

private:
    int height;//消息高度


signals:
};

#endif // LINEMESSAGE_H
