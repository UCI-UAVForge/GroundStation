/****************************************************************************
** Meta object code from reading C++ file 'database.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GS/database.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'database.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Database_t {
    QByteArrayData data[24];
    char stringdata[252];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Database_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Database_t qt_meta_stringdata_Database = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Database"
QT_MOC_LITERAL(1, 9, 9), // "activated"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 9), // "connected"
QT_MOC_LITERAL(4, 30, 14), // "formatDatabase"
QT_MOC_LITERAL(5, 45, 10), // "newMission"
QT_MOC_LITERAL(6, 56, 22), // "QList<QList<QString> >"
QT_MOC_LITERAL(7, 79, 7), // "mission"
QT_MOC_LITERAL(8, 87, 11), // "editMission"
QT_MOC_LITERAL(9, 99, 6), // "number"
QT_MOC_LITERAL(10, 106, 13), // "deleteMission"
QT_MOC_LITERAL(11, 120, 11), // "loadMission"
QT_MOC_LITERAL(12, 132, 13), // "missionNumber"
QT_MOC_LITERAL(13, 146, 8), // "newEntry"
QT_MOC_LITERAL(14, 155, 11), // "missionName"
QT_MOC_LITERAL(15, 167, 8), // "waypoint"
QT_MOC_LITERAL(16, 176, 8), // "behavior"
QT_MOC_LITERAL(17, 185, 3), // "lat"
QT_MOC_LITERAL(18, 189, 3), // "lon"
QT_MOC_LITERAL(19, 193, 6), // "action"
QT_MOC_LITERAL(20, 200, 9), // "editEntry"
QT_MOC_LITERAL(21, 210, 11), // "deleteEntry"
QT_MOC_LITERAL(22, 222, 16), // "createConnection"
QT_MOC_LITERAL(23, 239, 12) // "QSqlDatabase"

    },
    "Database\0activated\0\0connected\0"
    "formatDatabase\0newMission\0"
    "QList<QList<QString> >\0mission\0"
    "editMission\0number\0deleteMission\0"
    "loadMission\0missionNumber\0newEntry\0"
    "missionName\0waypoint\0behavior\0lat\0lon\0"
    "action\0editEntry\0deleteEntry\0"
    "createConnection\0QSqlDatabase"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Database[] = {

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
       1,    0,   69,    2, 0x0a /* Public */,
       3,    0,   70,    2, 0x0a /* Public */,
       4,    0,   71,    2, 0x0a /* Public */,
       5,    1,   72,    2, 0x0a /* Public */,
       8,    2,   75,    2, 0x0a /* Public */,
      10,    1,   80,    2, 0x0a /* Public */,
      11,    1,   83,    2, 0x0a /* Public */,
      13,    6,   86,    2, 0x08 /* Private */,
      20,    6,   99,    2, 0x08 /* Private */,
      21,    2,  112,    2, 0x08 /* Private */,
      22,    0,  117,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 6,    9,    7,
    QMetaType::Void, QMetaType::Int,    9,
    0x80000000 | 6, QMetaType::Int,   12,
    QMetaType::Bool, QMetaType::QString, QMetaType::Int, QMetaType::QString, QMetaType::Float, QMetaType::Float, QMetaType::QString,   14,   15,   16,   17,   18,   19,
    QMetaType::Bool, QMetaType::QString, QMetaType::Int, QMetaType::QString, QMetaType::Float, QMetaType::Float, QMetaType::QString,   14,   15,   16,   17,   18,   19,
    QMetaType::Bool, QMetaType::QString, QMetaType::Int,   14,   15,
    0x80000000 | 23,

       0        // eod
};

void Database::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Database *_t = static_cast<Database *>(_o);
        switch (_id) {
        case 0: { bool _r = _t->activated();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: { bool _r = _t->connected();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { bool _r = _t->formatDatabase();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: _t->newMission((*reinterpret_cast< QList<QList<QString> >(*)>(_a[1]))); break;
        case 4: _t->editMission((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QList<QList<QString> >(*)>(_a[2]))); break;
        case 5: _t->deleteMission((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: { QList<QList<QString> > _r = _t->loadMission((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QList<QList<QString> >*>(_a[0]) = _r; }  break;
        case 7: { bool _r = _t->newEntry((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: { bool _r = _t->editEntry((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: { bool _r = _t->deleteEntry((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { QSqlDatabase _r = _t->createConnection();
            if (_a[0]) *reinterpret_cast< QSqlDatabase*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QList<QString> > >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QList<QString> > >(); break;
            }
            break;
        }
    }
}

const QMetaObject Database::staticMetaObject = {
    { &QSqlDatabase::staticMetaObject, qt_meta_stringdata_Database.data,
      qt_meta_data_Database,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Database::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Database::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Database.stringdata))
        return static_cast<void*>(const_cast< Database*>(this));
    return QSqlDatabase::qt_metacast(_clname);
}

int Database::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSqlDatabase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
