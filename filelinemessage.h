#ifndef FILELINEMESSAGE_H
#define FILELINEMESSAGE_H

#include <QWidget>
#include <QFile>
#include <QFileInfo>
#include <QLabel>
#include <QPushButton>

class FileLineMessage : public QWidget
{
    Q_OBJECT
public:
    explicit FileLineMessage(const QString filepath,QString head,bool isme,QWidget *parent = nullptr);

private:
    QString file;

    QLabel *detaillab;
    QPushButton *filebtn;

private slots:
    void onclicked();

signals:
};

#endif // FILELINEMESSAGE_H
