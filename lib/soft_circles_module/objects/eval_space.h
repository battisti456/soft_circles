#ifndef EVAL_SPACE_OBJECT
#define EVAL_SPACE_OBJECT

#define PY_SSIZE_T_CLEAN
#include "soft_circle_module.h"
#include "soft_circle.h"
#include "exceptions.h"

typedef struct {
    PyObject_HEAD;
    es_type es;
    std::vector<SoftCircleObject*> scos;
    PyObject* soft_circles;
} EvalSpaceObject;

void remake_soft_circles_tuple(EvalSpaceObject* self){
    std::size_t num = self->scos.size();
    PyObject* new_soft_circles = PyTuple_New(num);
    for (std::size_t i = 0; i < num; i++){
        PySequence_SetItem(new_soft_circles,i,(PyObject*) self->scos[i]);
    }
    Py_DECREF(self->soft_circles);
    self->soft_circles = new_soft_circles;
}

static void EvalSpace_dealloc(EvalSpaceObject* self){
    Py_TYPE(self)->tp_free((PyObject*) self);
};

static PyObject* EvalSpace_new(PyTypeObject *type, PyObject *args, PyObject *kwds){
    EvalSpaceObject *self;
    self = (EvalSpaceObject*) type->tp_alloc(type, 0);
    if(self != NULL){
        self->soft_circles = PyTuple_New(0);
    }
    return (PyObject*) self;
};

static PyObject* EvalSpace_init(EvalSpaceObject* self, PyObject *args, PyObject *kwds){
    return 0;
};

static PyMemberDef EvalSpace_members[] = {
    {NULL},
};

static PyObject* EvalSpace_bind(EvalSpaceObject* self, PyObject* args){
    SoftCircleObject* sco = nullptr;
    PyObject* empty_tuple = PyTuple_New(0);
    PyObject* empty_dict = PyDict_New();
    Py_ssize_t num_add = PyTuple_Size(args);
    std::size_t start_size = self->es._soft_circles.size();
    std::size_t end_size = start_size + num_add;
    self->es._soft_circles.reserve(end_size);
    for(std::size_t i = start_size; i < end_size; i++){
        sco = (SoftCircleObject*) PyTuple_GET_ITEM(args,i-start_size);
        if(sco->es != nullptr){
            PyErr_SetString(BindException, "This soft circle is already bound.");
            return NULL;
        }
        sco->es = (PyObject*) self;
        sco->index = i;
        self->es._soft_circles.push_back(*(sco->sc));
        self->scos.push_back(sco);
        delete sco->sc;
        sco->sc = &(self->es._soft_circles[i]);
        Py_INCREF(self);
        Py_INCREF(sco);
    }
    remake_soft_circles_tuple(self);
    return Py_None;
};

static PyObject* EvalSpace_unbind(EvalSpaceObject* self, PyObject* args){
    SoftCircleObject* sco = (SoftCircleObject*) PyTuple_GET_ITEM(args,0);
    std::vector<SoftCircleObject*>::const_iterator erase;
    sc_type* sc;
    std::size_t i = 0;
    if(sco->es == nullptr){
        PyErr_SetString(BindException, "This soft circle is not bound.");
        return NULL;
    }
    if(((EvalSpaceObject*) sco->es) != self){
        PyErr_SetString(BindException, "This soft circle is not bound to this eval space.");
    }
    sco->es = nullptr;
    sco->sc = new sc_type(*(sc));
    self->es._soft_circles.erase(self->es._soft_circles.begin() + sco->index);
    erase = self->scos.begin() + sco->index;
    self->scos.erase(erase);
    for(std::vector<SoftCircleObject*>::const_iterator _sco = erase; _sco < self->scos.end(); _sco++){
        (*_sco)->index -= 1;
        (*_sco)->sc = (sc_type*) ((std::size_t) (*_sco)->sc - (std::size_t) &(self->es._soft_circles[(*_sco)->index]));
    }
    Py_DECREF(sco);
    Py_DECREF(self);
    remake_soft_circles_tuple(self);
    return Py_None;
}

static PyObject* EvalSpace_get_soft_circles(EvalSpaceObject* self, void* closure){
    return self->soft_circles;
}

static PyMethodDef EvalSpace_methods[] = {
    {"bind", (PyCFunction) EvalSpace_bind, METH_VARARGS, ""},
    {"unbind", (PyCFunction) EvalSpace_unbind, METH_VARARGS, ""},
    {NULL},
};

static PyGetSetDef EvalSpace_getsetters[] = {
    {"soft_circles", (getter) EvalSpace_get_soft_circles, NULL, "", NULL},
    {NULL}
};

static PyTypeObject EvalSpaceType = {
    .ob_base = PyVarObject_HEAD_INIT(NULL,0)
    .tp_name = "soft_circles_module.Eval_Space",
    .tp_basicsize = sizeof(EvalSpaceObject),
    .tp_itemsize = 0,
    .tp_dealloc = (destructor) EvalSpace_dealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = PyDoc_STR("Eval space object."),
    .tp_methods = EvalSpace_methods,
    .tp_members = EvalSpace_members,
    .tp_getset = EvalSpace_getsetters,
    .tp_init = (initproc) EvalSpace_init,
    .tp_new = EvalSpace_new,
};

#endif