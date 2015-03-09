/****************************************************************************
** Meta object code from reading C++ file 'mapexecution.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mapexecution.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mapexecution.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_mapexecution_t {
    QByteArrayData data[16];
    char stringdata[185];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mapexecution_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mapexecution_t qt_meta_stringdata_mapexecution = {
    {
QT_MOC_LITERAL(0, 0, 12), // "mapexecution"
QT_MOC_LITERAL(1, 13, 6), // "setMap"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 14), // "QList<QString>"
QT_MOC_LITERAL(4, 36, 4), // "list"
QT_MOC_LITERAL(5, 41, 8), // "addPoint"
QT_MOC_LITERAL(6, 50, 6), // "string"
QT_MOC_LITERAL(7, 57, 9), // "addNewMap"
QT_MOC_LITERAL(8, 67, 13), // "finishClicked"
QT_MOC_LITERAL(9, 81, 17), // "returnHomeClicked"
QT_MOC_LITERAL(10, 99, 13), // "cancelClicked"
QT_MOC_LITERAL(11, 113, 11), // "stopClicked"
QT_MOC_LITERAL(12, 125, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(13, 147, 14), // "push_new_point"
QT_MOC_LITERAL(14, 162, 5), // "point"
QT_MOC_LITERAL(15, 168, 16) // "addClickListener"

    },
    "mapexecution\0setMap\0\0QList<QString>\0"
    "list\0addPoint\0string\0addNewMap\0"
    "finishClicked\0returnHomeClicked\0"
    "cancelClicked\0stopClicked\0"
    "on_pushButton_clicked\0push_new_point\0"
    "point\0addClickListener"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mapexecution[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x0a /* Public */,
       5,    1,   67,    2, 0x0a /* Public */,
       7,    0,   70,    2, 0x0a /* Public */,
       8,    0,   71,    2, 0x08 /* Private */,
       9,    0,   72,    2, 0x08 /* Private */,
      10,    0,   73,    2, 0x08 /* Private */,
      11,    0,   74,    2, 0x08 /* Private */,
      12,    0,   75,    2, 0x08 /* Private */,
      13,    1,   76,    2, 0x08 /* Private */,
      15,    0,   79,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void,

       0        // eod
};

void mapexecution::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        mapexecution *_t = static_cast<mapexecution *>(_o);
        switch (_id) {
        case 0: _t->setMap((*reinterpret_cast< QList<QString>(*)>(_a[1]))); break;
        case 1: _t->addPoint((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->addNewMap(); break;
        case 3: _t->finishClicked(); break;
        case 4: _t->returnHomeClicked(); break;
        case 5: _t->cancelClicked(); break;
        case 6: _t->stopClicked(); break;
        case 7: _t->on_pushButton_clicked(); break;
        case 8: _t->push_new_point((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->addClickListener(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QString> >(); break;
            }
            break;
        }
    }
}

const QMetaObject mapexecution::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_mapexecution.data,
      qt_meta_data_mapexecution,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *mapexecution::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mapexecution::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_mapexecution.stringdata))
        return static_cast<void*>(const_cast< mapexecution*>(this));
    return QWidget::qt_metacast(_clname);
}

int mapexecution::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
