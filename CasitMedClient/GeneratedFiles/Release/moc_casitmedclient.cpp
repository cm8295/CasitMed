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
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   16,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      40,   15,   15,   15, 0x0a,
      48,   15,   15,   15, 0x0a,
      73,   64,   15,   15, 0x0a,
     114,  102,   15,   15, 0x0a,
     157,   15,   15,   15, 0x0a,
     168,   15,   15,   15, 0x0a,
     183,   15,   15,   15, 0x0a,
     203,   15,   15,   15, 0x0a,
     219,   15,   15,   15, 0x0a,
     234,   15,   15,   15, 0x0a,
     253,  246,   15,   15, 0x0a,
     302,   15,   15,   15, 0x0a,
     314,   15,   15,   15, 0x0a,
     334,   15,   15,   15, 0x0a,
     350,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CasitMedClient[] = {
    "CasitMedClient\0\0_speed\0speedsignal(int)\0"
    "start()\0startTransfer()\0numBytes\0"
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
        case 1: _t->start(); break;
        case 2: _t->startTransfer(); break;
        case 3: _t->updateClientProgress((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 4: _t->displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 5: _t->openFile(); break;
        case 6: _t->downLoadFile(); break;
        case 7: _t->clientReceiveFile(); break;
        case 8: _t->transfererror(); break;
        case 9: _t->connectClose(); break;
        case 10: _t->systemSet(); break;
        case 11: _t->iconActivated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 12: _t->minAction(); break;
        case 13: _t->creatSystemSetIni(); break;
        case 14: _t->fileWatchPath(); break;
        case 15: _t->sureWatchPath(); break;
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
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void CasitMedClient::speedsignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
