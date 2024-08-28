#ifndef FORCE_CONVEYOR_OBJECT
#define FORCE_CONVEYOR_OBJECT

#define PY_SSIZE_T_CLEAN
#include "./soft_circle_module.h"
#include "_es_bindable.h"
#include "soft_circle.h"
#include "exceptions.h"
#include "force_conveyor/force_conveyor_callback.h"

typedef struct ForceConveyorObject {
    _EsBindableObject esbo;
    fc_type* fc = nullptr;
    std::vector<PyObject*> referencing;
} ForceConveyorObject;

#include "force_conveyor/force_conveyor_make.h"

static void ForceConveyor_dealloc(ForceConveyorObject* self){
    if(self->fc != nullptr){delete self->fc; self->fc = nullptr;}
    Py_TYPE(self)->tp_free((PyObject*) self);
};

static PyObject* ForceConveyor_new(PyTypeObject *type, PyObject *args, PyObject *kwds){
    ForceConveyorObject *self;

    self = (ForceConveyorObject*) type->tp_alloc(type, 0);
    if(self != NULL){
    }
    return (PyObject*) self;
};

static int ForceConveyor_init(ForceConveyorObject* self, PyObject *args, PyObject *kwds){

    return 0;
};

static PyObject* ForceConveyor_callback(ForceConveyorObject* self, PyObject *args){
    return Py_None;
};

static PyMemberDef ForceConveyor_members[] = {
    {NULL},
};


static PyMethodDef ForceConveyor_methods[] = {
    {"callback", (PyCFunction) ForceConveyor_callback, METH_VARARGS, ""},
    {"make_callback", (PyCFunction) ForceConveyor_make_callback, METH_NOARGS | METH_CLASS, ""},
    {"make_soft_circle_gravity", (PyCFunction) ForceConveyor_make_soft_circle_gravity, METH_VARARGS | METH_CLASS, ""},
    {"make_point_force", (PyCFunction) ForceConveyor_make_point_force, METH_VARARGS | METH_CLASS, ""},
    {"make_simple_drag", (PyCFunction) ForceConveyor_make_simple_drag, METH_VARARGS | METH_CLASS, ""},
    {NULL},
};

static PyGetSetDef ForceConveyor_getsetters[] = {
    {NULL}
};

static PyTypeObject ForceConveyorType = {
    .ob_base = PyVarObject_HEAD_INIT(NULL,0)
    .tp_name = "soft_circles_module.Force_Conveyor",
    .tp_basicsize = sizeof(ForceConveyorObject),
    .tp_itemsize = 0,
    .tp_dealloc = (destructor) ForceConveyor_dealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = PyDoc_STR("Eval space object."),
    .tp_methods = ForceConveyor_methods,
    .tp_members = ForceConveyor_members,
    .tp_getset = ForceConveyor_getsetters,
    .tp_base = &_EsBindableType,
    .tp_init = (initproc) ForceConveyor_init,
    .tp_new = ForceConveyor_new,
};

#endif