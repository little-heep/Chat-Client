/****************************************************************************
** Meta object code from reading C++ file 'mywindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../mywindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mywindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyWindow_t {
    QByteArrayData data[20];
    char stringdata0[221];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyWindow_t qt_meta_stringdata_MyWindow = {
    {
QT_MOC_LITERAL(0, 0, 8), // "MyWindow"
QT_MOC_LITERAL(1, 9, 8), // "sendjson"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 4), // "json"
QT_MOC_LITERAL(4, 24, 15), // "requestInitData"
QT_MOC_LITERAL(5, 40, 10), // "showfriend"
QT_MOC_LITERAL(6, 51, 17), // "FriendListMessage"
QT_MOC_LITERAL(7, 69, 11), // "onchangepwd"
QT_MOC_LITERAL(8, 81, 6), // "oldpwd"
QT_MOC_LITERAL(9, 88, 6), // "newpwd"
QT_MOC_LITERAL(10, 95, 12), // "onchangename"
QT_MOC_LITERAL(11, 108, 7), // "newname"
QT_MOC_LITERAL(12, 116, 15), // "onaddfriendbyid"
QT_MOC_LITERAL(13, 132, 2), // "id"
QT_MOC_LITERAL(14, 135, 17), // "onaddfriendbyname"
QT_MOC_LITERAL(15, 153, 4), // "name"
QT_MOC_LITERAL(16, 158, 17), // "onaddfriendresult"
QT_MOC_LITERAL(17, 176, 18), // "onaddfriendrequest"
QT_MOC_LITERAL(18, 195, 10), // "FriendInfo"
QT_MOC_LITERAL(19, 206, 14) // "onacceptfriend"

    },
    "MyWindow\0sendjson\0\0json\0requestInitData\0"
    "showfriend\0FriendListMessage\0onchangepwd\0"
    "oldpwd\0newpwd\0onchangename\0newname\0"
    "onaddfriendbyid\0id\0onaddfriendbyname\0"
    "name\0onaddfriendresult\0onaddfriendrequest\0"
    "FriendInfo\0onacceptfriend"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    0,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   68,    2, 0x08 /* Private */,
       7,    2,   71,    2, 0x08 /* Private */,
      10,    1,   76,    2, 0x08 /* Private */,
      12,    1,   79,    2, 0x08 /* Private */,
      14,    1,   82,    2, 0x08 /* Private */,
      16,    2,   85,    2, 0x08 /* Private */,
      17,    1,   90,    2, 0x08 /* Private */,
      19,    1,   93,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QJsonObject,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    2,    2,
    QMetaType::Void, 0x80000000 | 18,    2,
    QMetaType::Void, 0x80000000 | 18,    2,

       0        // eod
};

void MyWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendjson((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 1: _t->requestInitData(); break;
        case 2: _t->showfriend((*reinterpret_cast< FriendListMessage(*)>(_a[1]))); break;
        case 3: _t->onchangepwd((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->onchangename((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->onaddfriendbyid((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->onaddfriendbyname((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->onaddfriendresult((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->onaddfriendrequest((*reinterpret_cast< FriendInfo(*)>(_a[1]))); break;
        case 9: _t->onacceptfriend((*reinterpret_cast< FriendInfo(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< FriendListMessage >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< FriendInfo >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< FriendInfo >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyWindow::*)(QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyWindow::sendjson)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MyWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyWindow::requestInitData)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MyWindow.data,
    qt_meta_data_MyWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MyWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void MyWindow::sendjson(QJsonObject _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyWindow::requestInitData()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
