/****************************************************************************
** Meta object code from reading C++ file 'client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_client_t {
    QByteArrayData data[34];
    char stringdata0[372];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_client_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_client_t qt_meta_stringdata_client = {
    {
QT_MOC_LITERAL(0, 0, 6), // "client"
QT_MOC_LITERAL(1, 7, 13), // "messageLogged"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 6), // "sendid"
QT_MOC_LITERAL(4, 29, 9), // "receiveid"
QT_MOC_LITERAL(5, 39, 7), // "content"
QT_MOC_LITERAL(6, 47, 8), // "sendtime"
QT_MOC_LITERAL(7, 56, 12), // "updatefriend"
QT_MOC_LITERAL(8, 69, 17), // "FriendListMessage"
QT_MOC_LITERAL(9, 87, 7), // "message"
QT_MOC_LITERAL(10, 95, 11), // "loginsucess"
QT_MOC_LITERAL(11, 107, 2), // "id"
QT_MOC_LITERAL(12, 110, 9), // "loginfail"
QT_MOC_LITERAL(13, 120, 12), // "fileReceived"
QT_MOC_LITERAL(14, 133, 8), // "filePath"
QT_MOC_LITERAL(15, 142, 15), // "changepwdstatus"
QT_MOC_LITERAL(16, 158, 5), // "statu"
QT_MOC_LITERAL(17, 164, 3), // "msg"
QT_MOC_LITERAL(18, 168, 16), // "changenamestatus"
QT_MOC_LITERAL(19, 185, 15), // "addfriendresult"
QT_MOC_LITERAL(20, 201, 2), // "ok"
QT_MOC_LITERAL(21, 204, 6), // "detail"
QT_MOC_LITERAL(22, 211, 16), // "addfriendrequest"
QT_MOC_LITERAL(23, 228, 10), // "FriendInfo"
QT_MOC_LITERAL(24, 239, 5), // "finfo"
QT_MOC_LITERAL(25, 245, 12), // "acceptfriend"
QT_MOC_LITERAL(26, 258, 15), // "registerSuccess"
QT_MOC_LITERAL(27, 274, 6), // "userid"
QT_MOC_LITERAL(28, 281, 12), // "registerFail"
QT_MOC_LITERAL(29, 294, 11), // "handleError"
QT_MOC_LITERAL(30, 306, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(31, 335, 11), // "socketError"
QT_MOC_LITERAL(32, 347, 8), // "readData"
QT_MOC_LITERAL(33, 356, 15) // "receiveFileData"

    },
    "client\0messageLogged\0\0sendid\0receiveid\0"
    "content\0sendtime\0updatefriend\0"
    "FriendListMessage\0message\0loginsucess\0"
    "id\0loginfail\0fileReceived\0filePath\0"
    "changepwdstatus\0statu\0msg\0changenamestatus\0"
    "addfriendresult\0ok\0detail\0addfriendrequest\0"
    "FriendInfo\0finfo\0acceptfriend\0"
    "registerSuccess\0userid\0registerFail\0"
    "handleError\0QAbstractSocket::SocketError\0"
    "socketError\0readData\0receiveFileData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_client[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   89,    2, 0x06 /* Public */,
       7,    1,   98,    2, 0x06 /* Public */,
      10,    1,  101,    2, 0x06 /* Public */,
      12,    1,  104,    2, 0x06 /* Public */,
      13,    2,  107,    2, 0x06 /* Public */,
      15,    2,  112,    2, 0x06 /* Public */,
      18,    1,  117,    2, 0x06 /* Public */,
      19,    2,  120,    2, 0x06 /* Public */,
      22,    1,  125,    2, 0x06 /* Public */,
      25,    1,  128,    2, 0x06 /* Public */,
      26,    2,  131,    2, 0x06 /* Public */,
      28,    1,  136,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      29,    1,  139,    2, 0x08 /* Private */,
      32,    0,  142,    2, 0x08 /* Private */,
      33,    0,  143,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QDateTime,    3,    4,    5,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,   14,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   16,   17,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,   20,   21,
    QMetaType::Void, 0x80000000 | 23,   24,
    QMetaType::Void, 0x80000000 | 23,   24,
    QMetaType::Void, QMetaType::UInt, QMetaType::QString,   27,    9,
    QMetaType::Void, QMetaType::QString,    9,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 30,   31,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<client *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->messageLogged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QDateTime(*)>(_a[4]))); break;
        case 1: _t->updatefriend((*reinterpret_cast< FriendListMessage(*)>(_a[1]))); break;
        case 2: _t->loginsucess((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->loginfail((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->fileReceived((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->changepwdstatus((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->changenamestatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->addfriendresult((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->addfriendrequest((*reinterpret_cast< FriendInfo(*)>(_a[1]))); break;
        case 9: _t->acceptfriend((*reinterpret_cast< FriendInfo(*)>(_a[1]))); break;
        case 10: _t->registerSuccess((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 11: _t->registerFail((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->handleError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 13: _t->readData(); break;
        case 14: _t->receiveFileData(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (client::*)(QString , QString , QString , QDateTime );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&client::messageLogged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (client::*)(FriendListMessage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&client::updatefriend)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (client::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&client::loginsucess)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (client::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&client::loginfail)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (client::*)(const QString , const QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&client::fileReceived)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (client::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&client::changepwdstatus)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (client::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&client::changenamestatus)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (client::*)(bool , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&client::addfriendresult)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (client::*)(FriendInfo );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&client::addfriendrequest)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (client::*)(FriendInfo );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&client::acceptfriend)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (client::*)(uint , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&client::registerSuccess)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (client::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&client::registerFail)) {
                *result = 11;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject client::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_client.data,
    qt_meta_data_client,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_client.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void client::messageLogged(QString _t1, QString _t2, QString _t3, QDateTime _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void client::updatefriend(FriendListMessage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void client::loginsucess(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void client::loginfail(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void client::fileReceived(const QString _t1, const QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void client::changepwdstatus(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void client::changenamestatus(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void client::addfriendresult(bool _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void client::addfriendrequest(FriendInfo _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void client::acceptfriend(FriendInfo _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void client::registerSuccess(uint _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void client::registerFail(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
