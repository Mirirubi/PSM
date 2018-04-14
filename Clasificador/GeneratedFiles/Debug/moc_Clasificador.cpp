/****************************************************************************
** Meta object code from reading C++ file 'Clasificador.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Clasificador.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Clasificador.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CClasificador_t {
    QByteArrayData data[19];
    char stringdata0[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CClasificador_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CClasificador_t qt_meta_stringdata_CClasificador = {
    {
QT_MOC_LITERAL(0, 0, 13), // "CClasificador"
QT_MOC_LITERAL(1, 14, 7), // "entrena"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 7), // "verImag"
QT_MOC_LITERAL(4, 31, 9), // "StartStop"
QT_MOC_LITERAL(5, 41, 8), // "verVideo"
QT_MOC_LITERAL(6, 50, 10), // "guardaImag"
QT_MOC_LITERAL(7, 61, 9), // "procesado"
QT_MOC_LITERAL(8, 71, 3), // "Mat"
QT_MOC_LITERAL(9, 75, 3), // "img"
QT_MOC_LITERAL(10, 79, 15), // "clasificacionFS"
QT_MOC_LITERAL(11, 95, 6), // "img_in"
QT_MOC_LITERAL(12, 102, 13), // "computeOutput"
QT_MOC_LITERAL(13, 116, 1), // "x"
QT_MOC_LITERAL(14, 118, 2), // "r1"
QT_MOC_LITERAL(15, 121, 2), // "s1"
QT_MOC_LITERAL(16, 124, 2), // "r2"
QT_MOC_LITERAL(17, 127, 2), // "s2"
QT_MOC_LITERAL(18, 130, 7) // "leyenda"

    },
    "CClasificador\0entrena\0\0verImag\0StartStop\0"
    "verVideo\0guardaImag\0procesado\0Mat\0img\0"
    "clasificacionFS\0img_in\0computeOutput\0"
    "x\0r1\0s1\0r2\0s2\0leyenda"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CClasificador[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    1,   64,    2, 0x08 /* Private */,
      10,    1,   67,    2, 0x08 /* Private */,
      12,    5,   70,    2, 0x08 /* Private */,
      18,    0,   81,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    0x80000000 | 8, 0x80000000 | 8,   11,
    QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   13,   14,   15,   16,   17,
    QMetaType::Void,

       0        // eod
};

void CClasificador::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CClasificador *_t = static_cast<CClasificador *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->entrena(); break;
        case 1: _t->verImag(); break;
        case 2: _t->StartStop(); break;
        case 3: _t->verVideo(); break;
        case 4: _t->guardaImag(); break;
        case 5: _t->procesado((*reinterpret_cast< Mat(*)>(_a[1]))); break;
        case 6: { Mat _r = _t->clasificacionFS((*reinterpret_cast< Mat(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Mat*>(_a[0]) = std::move(_r); }  break;
        case 7: { int _r = _t->computeOutput((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->leyenda(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CClasificador::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CClasificador.data,
      qt_meta_data_CClasificador,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CClasificador::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CClasificador::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CClasificador.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int CClasificador::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
