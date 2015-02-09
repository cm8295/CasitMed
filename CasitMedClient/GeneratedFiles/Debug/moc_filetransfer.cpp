/****************************************************************************
** Meta object code from reading C++ file 'filetransfer.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../filetransfer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filetransfer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_filetransfer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      42,   14,   13,   13, 0x05,
      88,   83,   13,   13, 0x05,
     148,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
     167,   13,   13,   13, 0x0a,
     175,   13,   13,   13, 0x0a,
     200,  191,   13,   13, 0x0a,
     241,  229,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_filetransfer[] = {
    "filetransfer\0\0_filename,_fileid,errorinfo\0"
    "transferErrorSignal(QString,int,QString)\0"
    ",,,,\0transferDataSignal(QString,QString,QString,QString,QString)\0"
    "transferOkSignal()\0start()\0startTransfer()\0"
    "numBytes\0updateClientProgress(qint64)\0"
    "socketError\0displayError(QAbstractSocket::SocketError)\0"
};

void filetransfer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        filetransfer *_t = static_cast<filetransfer *>(_o);
        switch (_id) {
        case 0: _t->transferErrorSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->transferDataSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 2: _t->transferOkSignal(); break;
        case 3: _t->start(); break;
        case 4: _t->startTransfer(); break;
        case 5: _t->updateClientProgress((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 6: _t->displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData filetransfer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject filetransfer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_filetransfer,
      qt_meta_data_filetransfer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &filetransfer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *filetransfer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *filetransfer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_filetransfer))
        return static_cast<void*>(const_cast< filetransfer*>(this));
    return QObject::qt_metacast(_clname);
}

int filetransfer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void filetransfer::transferErrorSignal(QString _t1, int _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void filetransfer::transferDataSignal(QString _t1, QString _t2, QString _t3, QString _t4, QString _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void filetransfer::transferOkSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
