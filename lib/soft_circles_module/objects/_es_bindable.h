#ifndef _ES_BINDABLE_OBJECT
#define _ES_BINDABLE_OBJECT

#define PY_SSIZE_T_CLEAN
#include <algorithm>
#include <Python.h>
#include "exceptions.h"

typedef struct {
    PyObject_HEAD;
    std::vector<PyObject*> bound;
} _Binder;

typedef struct _EsBindableObject {
    PyObject_HEAD;
    _Binder* es = nullptr;
} _EsBindableObject;

static void _EsBindable_dealloc(_EsBindableObject* self){
    Py_TYPE(self)->tp_free((PyObject*) self);
};

static PyObject* _EsBindable_new(PyTypeObject *type, PyObject *args, PyObject *kwds){
    _EsBindableObject *self;

    self = (_EsBindableObject*) type->tp_alloc(type, 0);
    if(self != NULL){
    }
    return (PyObject*) self;
};

static int _EsBindable_init(_EsBindableObject* self, PyObject *args, PyObject *kwds){
    PyErr_SetString(PyExc_NotImplementedError, "Force Conveyors should not be made using the default new and initialization. Use .make_callback to make a callback based force conveyor.");
    return -1;
};

static PyObject* _EsBindable__on_bound(_EsBindableObject *self, _Binder * binder){
    if(self->es != nullptr){
        PyErr_SetString(BindException, "This Soft_Circle is already bound.");
        return NULL;
    }
    self->es = binder;
    Py_INCREF(self);
    Py_INCREF(self->es);
    binder->bound.push_back((PyObject*) self);
    return Py_None;
}

static PyObject* _EsBindable__on_unbound(_EsBindableObject *self, _Binder * binder){
    if(binder != self->es){
        PyErr_SetString(BindException, "Attempting to unbind an Eval_Space object that was not bound to this _ES_Bindable.");
        return NULL;
    }
    Py_DECREF(self);
    Py_DECREF(self->es);
    self->es = nullptr;
    binder->bound.erase(std::find(binder->bound.begin(),binder->bound.end(),(PyObject*) self));
    return Py_None;
}

static PyObject* _EsBindable_get_eval_space(_EsBindableObject* self, void* closure){
    if(self->es == nullptr){return Py_None;} else {return (PyObject*) self->es;}
}

static PyMemberDef _EsBindable_members[] = {
    {NULL},
};

static PyMethodDef _EsBindable_methods[] = {
    {"_on_bound", (PyCFunction) _EsBindable__on_bound, METH_O, ""},
    {"_on_unbound", (PyCFunction) _EsBindable__on_unbound, METH_O, ""},
    {NULL},
};

static PyGetSetDef _EsBindable_getsetters[] = {
    {"eval_space", (getter) _EsBindable_get_eval_space, NULL, "", NULL},
    {NULL}
};

static PyTypeObject _EsBindableType = {
    .ob_base = PyVarObject_HEAD_INIT(NULL,0)
    .tp_name = "soft_circles_module._Es_Bindable",
    .tp_basicsize = sizeof(_EsBindableObject),
    .tp_itemsize = 0,
    .tp_dealloc = (destructor) _EsBindable_dealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = PyDoc_STR("Eval space object."),
    .tp_methods = _EsBindable_methods,
    .tp_members = _EsBindable_members,
    .tp_getset = _EsBindable_getsetters,
    .tp_init = (initproc) _EsBindable_init,
    .tp_new = _EsBindable_new,
};

#endif