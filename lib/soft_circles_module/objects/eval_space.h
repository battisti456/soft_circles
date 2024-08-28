#ifndef EVAL_SPACE_OBJECT
#define EVAL_SPACE_OBJECT

#define PY_SSIZE_T_CLEAN
#include "soft_circle_module.h"
#include "_es_bindable.h"
#include "soft_circle.h"
#include "exceptions.h"

typedef struct EvalSpaceObject : _Binder{
    es_type es;
} EvalSpaceObject;


static void EvalSpace_dealloc(EvalSpaceObject* self){
    Py_TYPE(self)->tp_free((PyObject*) self);
};

static PyObject* EvalSpace_new(PyTypeObject *type, PyObject *args, PyObject *kwds){
    EvalSpaceObject *self;

    double x_size, y_size;
    unsigned int x_divs, y_divs;

    self = (EvalSpaceObject*) type->tp_alloc(type, 0);
    if(self != NULL){
        PyArg_ParseTuple(args,"ddII",&x_size,&y_size,&x_divs,&y_divs);
        self->es = es_type(x_size,y_size,x_divs,y_divs);
    }
    return (PyObject*) self;
};

static int EvalSpace_init(EvalSpaceObject* self, PyObject *args, PyObject *kwds){
    return 0;
};

static PyMemberDef EvalSpace_members[] = {
    {NULL},
};

static PyObject* EvalSpace_bind(EvalSpaceObject* self, PyObject* args){
    PyObject* _bo;
    if(!PyArg_ParseTuple(args,"O",&_bo)){return NULL;}
    if(!PyObject_IsInstance(_bo,(PyObject*) &_EsBindableType)){return NULL;}
    return PyObject_CallMethod(_bo,"_on_bound","O",self);
};

static PyObject* EvalSpace_unbind(EvalSpaceObject* self, PyObject* args){
    PyObject* _bo;
    if(!PyArg_ParseTuple(args,"O",&_bo)){return NULL;}
    if(!PyObject_IsInstance(_bo,(PyObject*) &_EsBindableType)){return NULL;}
    return PyObject_CallMethod(_bo,"_on_unbound","O",self);
}

template <PyObject* type>
static PyObject* EvalSpace_get_bound(EvalSpaceObject* self, void* closure){
    PyObject* to_return = PyTuple_New(self->bound.size());
    std::size_t index = 0;
    for(PyObject* pyo : self->bound){
        if(!PyObject_IsInstance(pyo,type)){continue;}
        PySequence_SetItem(to_return,index++,pyo);
    }
    _PyTuple_Resize(&to_return,index);
    return to_return;
}

static PyMethodDef EvalSpace_methods[] = {
    {"bind", (PyCFunction) EvalSpace_bind, METH_VARARGS, ""},
    {"unbind", (PyCFunction) EvalSpace_unbind, METH_VARARGS, ""},
    {NULL},
};

static PyGetSetDef EvalSpace_getsetters[] = {
    {"bound", (getter) EvalSpace_get_bound<(PyObject*) &_EsBindableType>,NULL,"",NULL},
    {"soft_circles", (getter) EvalSpace_get_bound<(PyObject*) &SoftCircleType>, NULL, "", NULL},
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