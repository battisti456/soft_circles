#ifndef FORCE_CONVEYOR_OBJECT
#define FORCE_CONVEYOR_OBJECT

#define PY_SSIZE_T_CLEAN
#include "./soft_circle_module.h"
#include "_es_bindable.h"
#include "soft_circle.h"
#include "exceptions.h"

typedef struct KeeperObject : _EsBindableObject{
    kp_type* kp;
    std::vector<PyObject*> referencing;
} KeeperObject;


static void Keeper_dealloc(KeeperObject* self){
    if(self->kp != nullptr){delete self->kp; self->kp = nullptr;}
    Py_TYPE(self)->tp_free((PyObject*) self);
};

static PyObject* Keeper_new(PyTypeObject *type, PyObject *args, PyObject *kwds){
    KeeperObject *self;

    self = (KeeperObject*) type->tp_alloc(type, 0);
    if(self != NULL){
        self->es = nullptr;
        self->kp = nullptr;
        self->referencing = std::vector<PyObject*>();
    }
    return (PyObject*) self;
};

static int Keeper_init(KeeperObject* self, PyObject *args, PyObject *kwds){
    return 0;
};

static PyObject* Keeper_callback(KeeperObject* self, PyObject *args){
    return Py_None;
};

static PyObject* Keeper__on_bound(KeeperObject *self, PyObject *arg);
static PyObject* Keeper__on_unbound(KeeperObject *self, PyObject *arg);

static PyMemberDef Keeper_members[] = {
    {NULL},
};

#include "keeper/keeper_make"

static PyMethodDef Keeper_methods[] = {
    {"_on_bound",(PyCFunction) Keeper__on_bound, METH_O,""},
    {"_on_unbound", (PyCFunction) Keeper__on_unbound, METH_O,""},
    {"make_box", (PyCFunction) Keeper_make_box, METH_VARARGS | METH_CLASS, ""},
    {NULL},
};

static PyGetSetDef Keeper_getsetters[] = {
    {NULL}
};

static PyTypeObject KeeperType = {
    .ob_base = PyVarObject_HEAD_INIT(NULL,0)
    .tp_name = "soft_circles_module.Keeper",
    .tp_basicsize = sizeof(KeeperObject),
    .tp_itemsize = 0,
    .tp_dealloc = (destructor) Keeper_dealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = PyDoc_STR("Keeper object."),
    .tp_methods = Keeper_methods,
    .tp_members = Keeper_members,
    .tp_getset = Keeper_getsetters,
    .tp_base = &_EsBindableType,
    .tp_init = (initproc) Keeper_init,
    .tp_new = Keeper_new,
};

#include "force_conveyor/force_conveyors_binders.h"

#endif