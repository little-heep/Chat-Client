#include "loginwidget.h"
#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
    if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0)) QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

    auto *w = new LoginWidget;
    w->show();
    return a.exec();
}
