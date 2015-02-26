/****************************************************************************
** Meta object code from reading C++ file 'missionrecap.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../UAV-Forge-New/missionrecap.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'missionrecap.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MissionRecap_t {
    QByteArrayData data[8];
    char stringdata[161];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MissionRecap_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MissionRecap_t qt_meta_stringdata_MissionRecap = {
    {
QT_MOC_LITERAL(0, 0, 12), // "MissionRecap"
QT_MOC_LITERAL(1, 13, 20), // "replayMissionClicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 21), // "on_backButton_clicked"
QT_MOC_LITERAL(4, 57, 21), // "on_playButton_clicked"
QT_MOC_LITERAL(5, 79, 21), // "on_stopButton_clicked"
QT_MOC_LITERAL(6, 101, 25), // "on_openFileButton_clicked"
QT_MOC_LITERAL(7, 127, 33) // "on_horizontalSlider_sliderPre..."

    },
    "MissionRecap\0replayMissionClicked\0\0"
    "on_backButton_clicked\0on_playButton_clicked\0"
    "on_stopButton_clicked\0on_openFileButton_clicked\0"
    "on_horizontalSlider_sliderPressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MissionRecap[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MissionRecap::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MissionRecap *_t = static_cast<MissionRecap *>(_o);
        switch (_id) {
        case 0: _t->replayMissionClicked(); break;
        case 1: _t->on_backButton_clicked(); break;
        case 2: _t->on_playButton_clicked(); break;
        case 3: _t->on_stopButton_clicked(); break;
        case 4: _t->on_openFileButton_clicked(); break;
        case 5: _t->on_horizontalSlider_sliderPressed(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MissionRecap::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MissionRecap.data,
      qt_meta_data_MissionRecap,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MissionRecap::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MissionRecap::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MissionRecap.stringdata))
        return static_cast<void*>(const_cast< MissionRecap*>(this));
    return QWidget::qt_metacast(_clname);
}

int MissionRecap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
