/****************************************************************************
** Meta object code from reading C++ file 'caps.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../src/qt/caps.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'caps.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BitcoinApplication_t {
    QByteArrayData data[15];
    char stringdata0[228];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BitcoinApplication_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BitcoinApplication_t qt_meta_stringdata_BitcoinApplication = {
    {
QT_MOC_LITERAL(0, 0, 18), // "BitcoinApplication"
QT_MOC_LITERAL(1, 19, 19), // "requestedInitialize"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 17), // "requestedShutdown"
QT_MOC_LITERAL(4, 58, 11), // "windowShown"
QT_MOC_LITERAL(5, 70, 11), // "BitcoinGUI*"
QT_MOC_LITERAL(6, 82, 6), // "window"
QT_MOC_LITERAL(7, 89, 16), // "initializeResult"
QT_MOC_LITERAL(8, 106, 7), // "success"
QT_MOC_LITERAL(9, 114, 33), // "interfaces::BlockAndHeaderTip..."
QT_MOC_LITERAL(10, 148, 8), // "tip_info"
QT_MOC_LITERAL(11, 157, 15), // "requestShutdown"
QT_MOC_LITERAL(12, 173, 22), // "handleRunawayException"
QT_MOC_LITERAL(13, 196, 7), // "message"
QT_MOC_LITERAL(14, 204, 23) // "handleNonFatalException"

    },
    "BitcoinApplication\0requestedInitialize\0"
    "\0requestedShutdown\0windowShown\0"
    "BitcoinGUI*\0window\0initializeResult\0"
    "success\0interfaces::BlockAndHeaderTipInfo\0"
    "tip_info\0requestShutdown\0"
    "handleRunawayException\0message\0"
    "handleNonFatalException"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BitcoinApplication[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    1,   51,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    2,   54,    2, 0x0a /* Public */,
      11,    0,   59,    2, 0x0a /* Public */,
      12,    1,   60,    2, 0x0a /* Public */,
      14,    1,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 9,    8,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QString,   13,

       0        // eod
};

void BitcoinApplication::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BitcoinApplication *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->requestedInitialize(); break;
        case 1: _t->requestedShutdown(); break;
        case 2: _t->windowShown((*reinterpret_cast< BitcoinGUI*(*)>(_a[1]))); break;
        case 3: _t->initializeResult((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< interfaces::BlockAndHeaderTipInfo(*)>(_a[2]))); break;
        case 4: _t->requestShutdown(); break;
        case 5: _t->handleRunawayException((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->handleNonFatalException((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BitcoinApplication::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BitcoinApplication::requestedInitialize)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BitcoinApplication::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BitcoinApplication::requestedShutdown)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BitcoinApplication::*)(BitcoinGUI * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BitcoinApplication::windowShown)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BitcoinApplication::staticMetaObject = { {
    QMetaObject::SuperData::link<QApplication::staticMetaObject>(),
    qt_meta_stringdata_BitcoinApplication.data,
    qt_meta_data_BitcoinApplication,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BitcoinApplication::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BitcoinApplication::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BitcoinApplication.stringdata0))
        return static_cast<void*>(this);
    return QApplication::qt_metacast(_clname);
}

int BitcoinApplication::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QApplication::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void BitcoinApplication::requestedInitialize()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void BitcoinApplication::requestedShutdown()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void BitcoinApplication::windowShown(BitcoinGUI * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
