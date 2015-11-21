/****************************************************************************
** Meta object code from reading C++ file 'missionrecap.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "missionrecap.h"
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
    QByteArrayData data[16];
    char stringdata[269];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MissionRecap_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MissionRecap_t qt_meta_stringdata_MissionRecap = {
    {
QT_MOC_LITERAL(0, 0, 12), // "MissionRecap"
QT_MOC_LITERAL(1, 13, 12), // "updateSlider"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 8), // "position"
QT_MOC_LITERAL(4, 36, 17), // "updateMediaPlayer"
QT_MOC_LITERAL(5, 54, 20), // "replayMissionClicked"
QT_MOC_LITERAL(6, 75, 21), // "setupRealtimeDataDemo"
QT_MOC_LITERAL(7, 97, 12), // "QCustomPlot*"
QT_MOC_LITERAL(8, 110, 10), // "customPlot"
QT_MOC_LITERAL(9, 121, 16), // "realtimeDataSlot"
QT_MOC_LITERAL(10, 138, 21), // "on_backButton_clicked"
QT_MOC_LITERAL(11, 160, 21), // "on_playButton_clicked"
QT_MOC_LITERAL(12, 182, 21), // "on_stopButton_clicked"
QT_MOC_LITERAL(13, 204, 25), // "on_openFileButton_clicked"
QT_MOC_LITERAL(14, 230, 21), // "on_newMission_clicked"
QT_MOC_LITERAL(15, 252, 16) // "addClickListener"

    },
    "MissionRecap\0updateSlider\0\0position\0"
    "updateMediaPlayer\0replayMissionClicked\0"
    "setupRealtimeDataDemo\0QCustomPlot*\0"
    "customPlot\0realtimeDataSlot\0"
    "on_backButton_clicked\0on_playButton_clicked\0"
    "on_stopButton_clicked\0on_openFileButton_clicked\0"
    "on_newMission_clicked\0addClickListener"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MissionRecap[] = {

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
       1,    1,   69,    2, 0x0a /* Public */,
       4,    1,   72,    2, 0x0a /* Public */,
       5,    0,   75,    2, 0x0a /* Public */,
       6,    1,   76,    2, 0x0a /* Public */,
       9,    0,   79,    2, 0x08 /* Private */,
      10,    0,   80,    2, 0x08 /* Private */,
      11,    0,   81,    2, 0x08 /* Private */,
      12,    0,   82,    2, 0x08 /* Private */,
      13,    0,   83,    2, 0x08 /* Private */,
      14,    0,   84,    2, 0x08 /* Private */,
      15,    0,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::LongLong,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
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
        case 0: _t->updateSlider((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 1: _t->updateMediaPlayer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->replayMissionClicked(); break;
        case 3: _t->setupRealtimeDataDemo((*reinterpret_cast< QCustomPlot*(*)>(_a[1]))); break;
        case 4: _t->realtimeDataSlot(); break;
        case 5: _t->on_backButton_clicked(); break;
        case 6: _t->on_playButton_clicked(); break;
        case 7: _t->on_stopButton_clicked(); break;
        case 8: _t->on_openFileButton_clicked(); break;
        case 9: _t->on_newMission_clicked(); break;
        case 10: _t->addClickListener(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCustomPlot* >(); break;
            }
            break;
        }
    }
}

const QMetaObject MissionRecap::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MissionRecap.data,
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
    return QDialog::qt_metacast(_clname);
}

int MissionRecap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
