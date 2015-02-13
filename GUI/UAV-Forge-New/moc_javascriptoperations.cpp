/****************************************************************************
** Meta object code from reading C++ file 'javascriptoperations.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "javascriptoperations.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'javascriptoperations.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_JavaScriptOperations_t {
    QByteArrayData data[3];
    char stringdata[40];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_JavaScriptOperations_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_JavaScriptOperations_t qt_meta_stringdata_JavaScriptOperations = {
    {
QT_MOC_LITERAL(0, 0, 20), // "JavaScriptOperations"
QT_MOC_LITERAL(1, 21, 17), // "addPointToTableHi"
QT_MOC_LITERAL(2, 39, 0) // ""

    },
    "JavaScriptOperations\0addPointToTableHi\0"
    ""
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_JavaScriptOperations[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void JavaScriptOperations::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        JavaScriptOperations *_t = static_cast<JavaScriptOperations *>(_o);
        switch (_id) {
        case 0: _t->addPointToTableHi(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject JavaScriptOperations::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_JavaScriptOperations.data,
      qt_meta_data_JavaScriptOperations,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *JavaScriptOperations::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *JavaScriptOperations::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_JavaScriptOperations.stringdata))
        return static_cast<void*>(const_cast< JavaScriptOperations*>(this));
    return QObject::qt_metacast(_clname);
}

int JavaScriptOperations::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
