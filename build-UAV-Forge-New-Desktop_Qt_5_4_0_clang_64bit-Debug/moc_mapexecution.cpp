/****************************************************************************
** Meta object code from reading C++ file 'mapexecution.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GS/mapexecution.h"
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
struct qt_meta_stringdata_MapExecution_t {
    QByteArrayData data[24];
    char stringdata[309];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MapExecution_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MapExecution_t qt_meta_stringdata_MapExecution = {
    {
QT_MOC_LITERAL(0, 0, 12), // "MapExecution"
QT_MOC_LITERAL(1, 13, 6), // "setMap"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 14), // "QList<QString>"
QT_MOC_LITERAL(4, 36, 4), // "list"
QT_MOC_LITERAL(5, 41, 9), // "addNewMap"
QT_MOC_LITERAL(6, 51, 11), // "updateTable"
QT_MOC_LITERAL(7, 63, 3), // "lat"
QT_MOC_LITERAL(8, 67, 3), // "lng"
QT_MOC_LITERAL(9, 71, 13), // "newTelemCoord"
QT_MOC_LITERAL(10, 85, 11), // "coordString"
QT_MOC_LITERAL(11, 97, 14), // "sendFlightPlan"
QT_MOC_LITERAL(12, 112, 14), // "updatePosition"
QT_MOC_LITERAL(13, 127, 3), // "alt"
QT_MOC_LITERAL(14, 131, 3), // "spd"
QT_MOC_LITERAL(15, 135, 23), // "on_finishButton_clicked"
QT_MOC_LITERAL(16, 159, 27), // "on_returnHomeButton_clicked"
QT_MOC_LITERAL(17, 187, 23), // "on_cancelButton_clicked"
QT_MOC_LITERAL(18, 211, 21), // "on_stopButton_clicked"
QT_MOC_LITERAL(19, 233, 21), // "on_backButton_clicked"
QT_MOC_LITERAL(20, 255, 14), // "push_new_point"
QT_MOC_LITERAL(21, 270, 5), // "point"
QT_MOC_LITERAL(22, 276, 16), // "addClickListener"
QT_MOC_LITERAL(23, 293, 15) // "initCurrentData"

    },
    "MapExecution\0setMap\0\0QList<QString>\0"
    "list\0addNewMap\0updateTable\0lat\0lng\0"
    "newTelemCoord\0coordString\0sendFlightPlan\0"
    "updatePosition\0alt\0spd\0on_finishButton_clicked\0"
    "on_returnHomeButton_clicked\0"
    "on_cancelButton_clicked\0on_stopButton_clicked\0"
    "on_backButton_clicked\0push_new_point\0"
    "point\0addClickListener\0initCurrentData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MapExecution[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x0a /* Public */,
       5,    0,   87,    2, 0x0a /* Public */,
       6,    2,   88,    2, 0x0a /* Public */,
       9,    1,   93,    2, 0x0a /* Public */,
      11,    0,   96,    2, 0x0a /* Public */,
      12,    4,   97,    2, 0x0a /* Public */,
      15,    0,  106,    2, 0x08 /* Private */,
      16,    0,  107,    2, 0x08 /* Private */,
      17,    0,  108,    2, 0x08 /* Private */,
      18,    0,  109,    2, 0x08 /* Private */,
      19,    0,  110,    2, 0x08 /* Private */,
      20,    1,  111,    2, 0x08 /* Private */,
      22,    0,  114,    2, 0x08 /* Private */,
      23,    0,  115,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    7,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,    7,    8,   13,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MapExecution::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MapExecution *_t = static_cast<MapExecution *>(_o);
        switch (_id) {
        case 0: _t->setMap((*reinterpret_cast< QList<QString>(*)>(_a[1]))); break;
        case 1: _t->addNewMap(); break;
        case 2: _t->updateTable((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 3: _t->newTelemCoord((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->sendFlightPlan(); break;
        case 5: _t->updatePosition((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 6: _t->on_finishButton_clicked(); break;
        case 7: _t->on_returnHomeButton_clicked(); break;
        case 8: _t->on_cancelButton_clicked(); break;
        case 9: _t->on_stopButton_clicked(); break;
        case 10: _t->on_backButton_clicked(); break;
        case 11: _t->push_new_point((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->addClickListener(); break;
        case 13: _t->initCurrentData(); break;
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

const QMetaObject MapExecution::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MapExecution.data,
      qt_meta_data_MapExecution,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MapExecution::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MapExecution::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MapExecution.stringdata))
        return static_cast<void*>(const_cast< MapExecution*>(this));
    return QDialog::qt_metacast(_clname);
}

int MapExecution::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
