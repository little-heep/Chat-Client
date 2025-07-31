QT       += core gui
QT       += network
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatwidget.cpp \
    client.cpp \
    dbmanage.cpp \
    filehandle.cpp \
    filelinemessage.cpp \
    friendlistitem.cpp \
    linemessage.cpp \
    loginwidget.cpp \
    main.cpp \
    messagewidget.cpp \
    mywindow.cpp \
    passwordeditmessagebox.cpp \
    personalwidget.cpp

HEADERS += \
    allstructs.h \
    chatwidget.h \
    client.h \
    dbmanage.h \
    filehandle.h \
    filelinemessage.h \
    friendlistitem.h \
    linemessage.h \
    loginwidget.h \
    messagewidget.h \
    mywindow.h \
    passwordeditmessagebox.h \
    personalwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    static.qrc
