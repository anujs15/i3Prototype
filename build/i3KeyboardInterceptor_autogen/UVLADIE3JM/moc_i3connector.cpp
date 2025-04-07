/****************************************************************************
** Meta object code from reading C++ file 'i3connector.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/i3connector.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'i3connector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_I3Connector_t {
    QByteArrayData data[14];
    char stringdata0[212];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_I3Connector_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_I3Connector_t qt_meta_stringdata_I3Connector = {
    {
QT_MOC_LITERAL(0, 0, 11), // "I3Connector"
QT_MOC_LITERAL(1, 12, 21), // "keyboardBufferChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 23), // "connectionStatusChanged"
QT_MOC_LITERAL(4, 59, 9), // "connected"
QT_MOC_LITERAL(5, 69, 17), // "handleKeySequence"
QT_MOC_LITERAL(6, 87, 8), // "sequence"
QT_MOC_LITERAL(7, 96, 10), // "readSocket"
QT_MOC_LITERAL(8, 107, 17), // "handleSocketError"
QT_MOC_LITERAL(9, 125, 30), // "QLocalSocket::LocalSocketError"
QT_MOC_LITERAL(10, 156, 11), // "socketError"
QT_MOC_LITERAL(11, 168, 11), // "connectToI3"
QT_MOC_LITERAL(12, 180, 16), // "disconnectFromI3"
QT_MOC_LITERAL(13, 197, 14) // "keyboardBuffer"

    },
    "I3Connector\0keyboardBufferChanged\0\0"
    "connectionStatusChanged\0connected\0"
    "handleKeySequence\0sequence\0readSocket\0"
    "handleSocketError\0QLocalSocket::LocalSocketError\0"
    "socketError\0connectToI3\0disconnectFromI3\0"
    "keyboardBuffer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_I3Connector[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       1,   62, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    1,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   53,    2, 0x0a /* Public */,
       7,    0,   56,    2, 0x08 /* Private */,
       8,    1,   57,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      11,    0,   60,    2, 0x02 /* Public */,
      12,    0,   61,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,

 // methods: parameters
    QMetaType::Bool,
    QMetaType::Bool,

 // properties: name, type, flags
      13, QMetaType::QString, 0x00495001,

 // properties: notify_signal_id
       0,

       0        // eod
};

void I3Connector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<I3Connector *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->keyboardBufferChanged(); break;
        case 1: _t->connectionStatusChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->handleKeySequence((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->readSocket(); break;
        case 4: _t->handleSocketError((*reinterpret_cast< QLocalSocket::LocalSocketError(*)>(_a[1]))); break;
        case 5: { bool _r = _t->connectToI3();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: { bool _r = _t->disconnectFromI3();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (I3Connector::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I3Connector::keyboardBufferChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (I3Connector::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I3Connector::connectionStatusChanged)) {
                *result = 1;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<I3Connector *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->keyboardBuffer(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject I3Connector::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_I3Connector.data,
    qt_meta_data_I3Connector,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *I3Connector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *I3Connector::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_I3Connector.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int I3Connector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void I3Connector::keyboardBufferChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void I3Connector::connectionStatusChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
