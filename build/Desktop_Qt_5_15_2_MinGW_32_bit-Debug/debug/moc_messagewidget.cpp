/****************************************************************************
** Meta object code from reading C++ file 'messagewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../messagewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'messagewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MessageWidget_t {
    QByteArrayData data[26];
    char stringdata0[279];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MessageWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MessageWidget_t qt_meta_stringdata_MessageWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "MessageWidget"
QT_MOC_LITERAL(1, 14, 6), // "sendid"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 13), // "addfriendbyid"
QT_MOC_LITERAL(4, 36, 15), // "addfriendbyname"
QT_MOC_LITERAL(5, 52, 11), // "sendmessage"
QT_MOC_LITERAL(6, 64, 7), // "jsonMsg"
QT_MOC_LITERAL(7, 72, 11), // "sendfilemsg"
QT_MOC_LITERAL(8, 84, 8), // "filename"
QT_MOC_LITERAL(9, 93, 9), // "receiveid"
QT_MOC_LITERAL(10, 103, 6), // "newmsg"
QT_MOC_LITERAL(11, 110, 7), // "content"
QT_MOC_LITERAL(12, 118, 8), // "sendtime"
QT_MOC_LITERAL(13, 127, 12), // "filereceived"
QT_MOC_LITERAL(14, 140, 8), // "filepath"
QT_MOC_LITERAL(15, 149, 11), // "onappendLog"
QT_MOC_LITERAL(16, 161, 14), // "onfileReceived"
QT_MOC_LITERAL(17, 176, 16), // "onSessionChanged"
QT_MOC_LITERAL(18, 193, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(19, 210, 7), // "current"
QT_MOC_LITERAL(20, 218, 8), // "onaddlog"
QT_MOC_LITERAL(21, 227, 7), // "Message"
QT_MOC_LITERAL(22, 235, 3), // "msg"
QT_MOC_LITERAL(23, 239, 14), // "onSearchFriend"
QT_MOC_LITERAL(24, 254, 13), // "onsendmessage"
QT_MOC_LITERAL(25, 268, 10) // "onsendfile"

    },
    "MessageWidget\0sendid\0\0addfriendbyid\0"
    "addfriendbyname\0sendmessage\0jsonMsg\0"
    "sendfilemsg\0filename\0receiveid\0newmsg\0"
    "content\0sendtime\0filereceived\0filepath\0"
    "onappendLog\0onfileReceived\0onSessionChanged\0"
    "QListWidgetItem*\0current\0onaddlog\0"
    "Message\0msg\0onSearchFriend\0onsendmessage\0"
    "onsendfile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MessageWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       3,    1,   87,    2, 0x06 /* Public */,
       4,    1,   90,    2, 0x06 /* Public */,
       5,    1,   93,    2, 0x06 /* Public */,
       7,    3,   96,    2, 0x06 /* Public */,
      10,    4,  103,    2, 0x06 /* Public */,
      13,    2,  112,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    4,  117,    2, 0x0a /* Public */,
      16,    2,  126,    2, 0x0a /* Public */,
      17,    1,  131,    2, 0x08 /* Private */,
      20,    1,  134,    2, 0x08 /* Private */,
      23,    0,  137,    2, 0x08 /* Private */,
      24,    1,  138,    2, 0x08 /* Private */,
      25,    3,  141,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QJsonObject,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    8,    1,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QDateTime,    1,    9,   11,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    1,   14,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QDateTime,    1,    9,   11,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    1,   14,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    8,    1,    9,

       0        // eod
};

void MessageWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MessageWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendid((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->addfriendbyid((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->addfriendbyname((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->sendmessage((*reinterpret_cast< const QJsonObject(*)>(_a[1]))); break;
        case 4: _t->sendfilemsg((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 5: _t->newmsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QDateTime(*)>(_a[4]))); break;
        case 6: _t->filereceived((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 7: _t->onappendLog((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QDateTime(*)>(_a[4]))); break;
        case 8: _t->onfileReceived((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 9: _t->onSessionChanged((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 10: _t->onaddlog((*reinterpret_cast< const Message(*)>(_a[1]))); break;
        case 11: _t->onSearchFriend(); break;
        case 12: _t->onsendmessage((*reinterpret_cast< const QJsonObject(*)>(_a[1]))); break;
        case 13: _t->onsendfile((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Message >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MessageWidget::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MessageWidget::sendid)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MessageWidget::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MessageWidget::addfriendbyid)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MessageWidget::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MessageWidget::addfriendbyname)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MessageWidget::*)(const QJsonObject & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MessageWidget::sendmessage)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MessageWidget::*)(const QString , const QString , const QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MessageWidget::sendfilemsg)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MessageWidget::*)(QString , QString , QString , QDateTime );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MessageWidget::newmsg)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MessageWidget::*)(const QString , const QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MessageWidget::filereceived)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MessageWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_MessageWidget.data,
    qt_meta_data_MessageWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MessageWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MessageWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MessageWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MessageWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void MessageWidget::sendid(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MessageWidget::addfriendbyid(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MessageWidget::addfriendbyname(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MessageWidget::sendmessage(const QJsonObject & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MessageWidget::sendfilemsg(const QString _t1, const QString _t2, const QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MessageWidget::newmsg(QString _t1, QString _t2, QString _t3, QDateTime _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MessageWidget::filereceived(const QString _t1, const QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
