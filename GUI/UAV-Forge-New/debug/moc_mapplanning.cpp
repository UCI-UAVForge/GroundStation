/****************************************************************************
** Meta object code from reading C++ file 'mapplanning.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mapplanning.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mapplanning.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MapPlanning_t {
    QByteArrayData data[16];
    char stringdata[268];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MapPlanning_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MapPlanning_t qt_meta_stringdata_MapPlanning = {
    {
QT_MOC_LITERAL(0, 0, 11), // "MapPlanning"
QT_MOC_LITERAL(1, 12, 15), // "addPointToTable"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 3), // "lat"
QT_MOC_LITERAL(4, 33, 3), // "lng"
QT_MOC_LITERAL(5, 37, 23), // "on_pushButton_6_clicked"
QT_MOC_LITERAL(6, 61, 23), // "on_pushButton_5_clicked"
QT_MOC_LITERAL(7, 85, 23), // "on_pushButton_7_clicked"
QT_MOC_LITERAL(8, 109, 23), // "on_pushButton_8_clicked"
QT_MOC_LITERAL(9, 133, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(10, 155, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(11, 179, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(12, 203, 16), // "addClickListener"
QT_MOC_LITERAL(13, 220, 11), // "closeWindow"
QT_MOC_LITERAL(14, 232, 12), // "getTableData"
QT_MOC_LITERAL(15, 245, 22) // "QList<QList<QString> >"

    },
    "MapPlanning\0addPointToTable\0\0lat\0lng\0"
    "on_pushButton_6_clicked\0on_pushButton_5_clicked\0"
    "on_pushButton_7_clicked\0on_pushButton_8_clicked\0"
    "on_pushButton_clicked\0on_pushButton_2_clicked\0"
    "on_pushButton_3_clicked\0addClickListener\0"
    "closeWindow\0getTableData\0"
    "QList<QList<QString> >"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MapPlanning[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   69,    2, 0x0a /* Public */,
       5,    0,   74,    2, 0x08 /* Private */,
       6,    0,   75,    2, 0x08 /* Private */,
       7,    0,   76,    2, 0x08 /* Private */,
       8,    0,   77,    2, 0x08 /* Private */,
       9,    0,   78,    2, 0x08 /* Private */,
      10,    0,   79,    2, 0x08 /* Private */,
      11,    0,   80,    2, 0x08 /* Private */,
      12,    0,   81,    2, 0x08 /* Private */,
      13,    0,   82,    2, 0x08 /* Private */,
      14,    0,   83,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 15,

       0        // eod
};

void MapPlanning::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MapPlanning *_t = static_cast<MapPlanning *>(_o);
        switch (_id) {
        case 0: _t->addPointToTable((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: _t->on_pushButton_6_clicked(); break;
        case 2: _t->on_pushButton_5_clicked(); break;
        case 3: _t->on_pushButton_7_clicked(); break;
        case 4: _t->on_pushButton_8_clicked(); break;
        case 5: _t->on_pushButton_clicked(); break;
        case 6: _t->on_pushButton_2_clicked(); break;
        case 7: _t->on_pushButton_3_clicked(); break;
        case 8: _t->addClickListener(); break;
        case 9: _t->closeWindow(); break;
        case 10: { QList<QList<QString> > _r = _t->getTableData();
            if (_a[0]) *reinterpret_cast< QList<QList<QString> >*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject MapPlanning::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MapPlanning.data,
      qt_meta_data_MapPlanning,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MapPlanning::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MapPlanning::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MapPlanning.stringdata))
        return static_cast<void*>(const_cast< MapPlanning*>(this));
    return QDialog::qt_metacast(_clname);
}

int MapPlanning::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
