/****************************************************************************
** Meta object code from reading C++ file 'playwidget.h'
**
** Created: Tue Jun 30 23:09:33 2009
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
      16,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      22,   11,   11,   11, 0x0a,
      32,   11,   11,   11, 0x0a,
      42,   11,   11,   11, 0x0a,
      52,   11,   11,   11, 0x0a,
      62,   11,   11,   11, 0x0a,
      72,   11,   11,   11, 0x0a,
      82,   11,   11,   11, 0x0a,
      92,   11,   11,   11, 0x0a,
     102,   11,   11,   11, 0x0a,
     113,   11,   11,   11, 0x0a,
     124,   11,   11,   11, 0x0a,
     135,   11,   11,   11, 0x0a,
     146,   11,   11,   11, 0x0a,
     157,   11,   11,   11, 0x0a,
     168,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_playwidget[] = {
    "playwidget\0\0timefuc()\0b1click()\0"
    "b2click()\0b3click()\0b4click()\0b5click()\0"
    "b6click()\0b7click()\0b8click()\0ub1click()\0"
    "ub2click()\0ub3click()\0ub4click()\0"
    "wb1click()\0wb2click()\0wb3click()\0"
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
        case 1: b1click(); break;
        case 2: b2click(); break;
        case 3: b3click(); break;
        case 4: b4click(); break;
        case 5: b5click(); break;
        case 6: b6click(); break;
        case 7: b7click(); break;
        case 8: b8click(); break;
        case 9: ub1click(); break;
        case 10: ub2click(); break;
        case 11: ub3click(); break;
        case 12: ub4click(); break;
        case 13: wb1click(); break;
        case 14: wb2click(); break;
        case 15: wb3click(); break;
        default: ;
        }
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
