#include <Python.h>
#include "eval_space.h"
#include "_es_bindable.h"

typedef struct {
    PyObject_HEAD
    EvalSpaceObject* eso;
    PyObject* type;
    std::vector<PyObject*>::const_iterator pos;
} BoundIterObject;

static void BoundIter_dealloc(BoundIterObject* self){
    Py_DECREF(self->eso);
    Py_DECREF(self->type);
    Py_TYPE(self)->tp_free((PyObject*) self);
};

static BoundIterObject* BoundIter_raw_new(PyTypeObject* type, EvalSpaceObject* eso, PyObject* check_type){
    BoundIterObject* self = (BoundIterObject*) type->tp_alloc(type, 0);
    if(self != NULL){
        self->eso = eso;
        self->type = check_type;
        self->pos = self->eso->bound.begin();
        Py_INCREF(eso);
        Py_INCREF(check_type);
    }
    return self;
}

static PyObject* BoundIter_new(PyTypeObject *type, PyObject *args, PyObject *kwds){
    BoundIterObject *self;

    PyObject* check_type = (PyObject*) &_EsBindableType;
    PyObject* eso;

    switch(PyTuple_GET_SIZE(args)){
        case 2:
            check_type = (PyObject*) PyTuple_GetItem(args,1);
            if(check_type == NULL){return NULL;}
            if(!PyType_IsSubtype((PyTypeObject*) check_type,&_EsBindableType)){
                PyErr_SetString(PyExc_TypeError,"Arg 1 must be a subtype of _Es_Bindable");
                return NULL;
            }
        case 1:
            eso = (PyObject*) PyTuple_GetItem(args,0);
            if(eso == NULL){return NULL;}
            if(!PyObject_IsInstance(eso,(PyObject*) &EvalSpaceType)){
                PyErr_SetString(PyExc_TypeError,"Arg 0 must be of type eval space.");
                return NULL;
            }
            break;
        default:
            PyErr_SetString(PyExc_TypeError,"Wrong Number of arguments for a Bound_Iter.");
            return NULL;
    }
    self = BoundIter_raw_new(type,(EvalSpaceObject*) eso,check_type);

    return (PyObject*) self;
};

PyObject* BoundIter_iter(BoundIterObject* self){
    Py_INCREF(self);
    return (PyObject*) self;
}

PyObject* BoundIter_iternext(BoundIterObject* self){
    PyObject* val;
    if(self->pos != self->eso->bound.end()){
        val = (*(self->pos));
        self->pos += 1;
        if(!PyObject_IsInstance(val,self->type)){
            return BoundIter_iternext(self);
        } else {
            Py_INCREF(val);
            return val;
        }
    } else {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }
}

static PyTypeObject BoundIterType = {
    .ob_base = PyVarObject_HEAD_INIT(NULL,0)
    .tp_name = "soft_circles_module.Bound_Iter",
    .tp_basicsize = sizeof(BoundIterObject),
    .tp_dealloc = (destructor) BoundIter_dealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "",
    .tp_iter = (getiterfunc) BoundIter_iter,
    .tp_iternext = (iternextfunc) BoundIter_iternext,
    .tp_new = BoundIter_new,
};