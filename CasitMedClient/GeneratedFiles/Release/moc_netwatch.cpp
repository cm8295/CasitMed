/****************************************************************************
** Meta object code from reading C++ file 'netwatch.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../netwatch.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'netwatch.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_netwatch[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   10,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,    9,    9,    9, 0x0a,
      78,    9,    9,    9, 0x0a,
      98,    9,    9,    9, 0x0a,
     121,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_netwatch[] = {
    "netwatch\0\0str\0ShowStatus(QString)\0"
    "OnSocketError(QAbstractSocket::SocketError)\0"
    "OnSocketConnected()\0OnSocketDisconnected()\0"
    "ConnectServer()\0"
};

void netwatch::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        netwatch *_t = static_cast<netwatch *>(_o);
        switch (_id) {
        case 0: _t->ShowStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->OnSocketError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 2: _t->OnSocketConnected(); break;
        case 3: _t->OnSocketDisconnected(); break;
        case 4: _t->ConnectServer(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData netwatch::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject netwatch::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_netwatch,
      qt_meta_data_netwatch, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &netwatch::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *netwatch::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *netwatch::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_netwatch))
        return static_cast<void*>(const_cast< netwatch*>(this));
    return QThread::qt_metacast(_clname);
}

int netwatch::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void netwatch::ShowStatus(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
