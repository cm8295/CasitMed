/****************************************************************************
** Meta object code from reading C++ file 'casitmedclient.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../casitmedclient.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'casitmedclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CasitMedClient[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   16,   15,   15, 0x05,
      40,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      66,   15,   15,   15, 0x0a,
      74,   15,   15,   15, 0x0a,
      99,   90,   15,   15, 0x0a,
     140,  128,   15,   15, 0x0a,
     183,   15,   15,   15, 0x0a,
     194,   15,   15,   15, 0x0a,
     209,   15,   15,   15, 0x0a,
     229,   15,   15,   15, 0x0a,
     245,   15,   15,   15, 0x0a,
     260,   15,   15,   15, 0x0a,
     279,  272,   15,   15, 0x0a,
     328,   15,   15,   15, 0x0a,
     340,   15,   15,   15, 0x0a,
     360,   15,   15,   15, 0x0a,
     376,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CasitMedClient[] = {
    "CasitMedClient\0\0_speed\0speedsignal(int)\0"
    "transferOksignal(QString)\0start()\0"
    "startTransfer()\0numBytes\0"
    "updateClientProgress(qint64)\0socketError\0"
    "displayError(QAbstractSocket::SocketError)\0"
    "openFile()\0downLoadFile()\0clientReceiveFile()\0"
    "transfererror()\0connectClose()\0"
    "systemSet()\0reason\0"
    "iconActivated(QSystemTrayIcon::ActivationReason)\0"
    "minAction()\0creatSystemSetIni()\0"
    "fileWatchPath()\0sureWatchPath()\0"
};

void CasitMedClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CasitMedClient *_t = static_cast<CasitMedClient *>(_o);
        switch (_id) {
        case 0: _t->speedsignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->transferOksignal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->start(); break;
        case 3: _t->startTransfer(); break;
        case 4: _t->updateClientProgress((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 5: _t->displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 6: _t->openFile(); break;
        case 7: _t->downLoadFile(); break;
        case 8: _t->clientReceiveFile(); break;
        case 9: _t->transfererror(); break;
        case 10: _t->connectClose(); break;
        case 11: _t->systemSet(); break;
        case 12: _t->iconActivated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 13: _t->minAction(); break;
        case 14: _t->creatSystemSetIni(); break;
        case 15: _t->fileWatchPath(); break;
        case 16: _t->sureWatchPath(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CasitMedClient::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CasitMedClient::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CasitMedClient,
      qt_meta_data_CasitMedClient, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CasitMedClient::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CasitMedClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CasitMedClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CasitMedClient))
        return static_cast<void*>(const_cast< CasitMedClient*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int CasitMedClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void CasitMedClient::speedsignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CasitMedClient::transferOksignal(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
