/****************************************************************************
** Meta object code from reading C++ file 'playwidget.h'
**
** Created: Wed Jul 1 03:15:45 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "playwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_playwidget[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_playwidget[] = {
    "playwidget\0\0timefuc()\0"
};

const QMetaObject playwidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_playwidget,
      qt_meta_data_playwidget, 0 }
};

const QMetaObject *playwidget::metaObject() const
{
    return &staticMetaObject;
}

void *playwidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_playwidget))
        return static_cast<void*>(const_cast< playwidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int playwidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: timefuc(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
