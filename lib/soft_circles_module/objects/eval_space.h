#ifndef EVAL_SPACE_OBJECT
#define EVAL_SPACE_OBJECT

#define PY_SSIZE_T_CLEAN
#include "soft_circle_module.h"
#include "_es_bindable.h"
#include "exceptions.h"

typedef struct EvalSpaceObject : _Binder{
    es_type es;
} EvalSpaceObject;

EvalSpaceObject* get_eso_for_binding(PyObject* obj);

static void EvalSpace_dealloc(EvalSpaceObject* self){
    Py_TYPE(self)->tp_free((PyObject*) self);
};

static PyObject* EvalSpace_new(PyTypeObject *type, PyObject *args, PyObject *kwds){
    EvalSpaceObject *self;

    double x_center, y_center, x_size, y_size;

    self = (EvalSpaceObject*) type->tp_alloc(type, 0);
    if(self != NULL){
        self->bound = std::vector<PyObject*>();
        PyArg_ParseTuple(args,"dddd",&x_center,&y_center,&x_size,&y_size);
        self->es = es_type(x_center,y_center,x_size,y_size);
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

static PyObject* EvalSpace_tick(EvalSpaceObject* self, PyObject* args){
    double dt;
    std::size_t num;
    if(!PyArg_ParseTuple(args,"dK",&dt,&num)){return NULL;}
    for(std::size_t i = 0; i < num; i++){
        self->es.tick(dt);
        if(PyErr_Occurred()){return NULL;}
    }
    return Py_None;
}

static PyObject* EvalSpace_set_dim(EvalSpaceObject* self, PyObject* args){
    double left,top,right,down;
    if(!PyArg_ParseTuple(args,"dddd",&left,&top,&right,&down)){return NULL;}
    self->es.set_dim(left,top,right,down);
    return Py_None;
}

template <PyObject* type>
static PyObject* EvalSpace_get_bound(EvalSpaceObject* self, void* closure);

static PyObject* EvalSpace_get_oosb(EvalSpaceObject* self, void* closure){
    return PyLong_FromSize_t((std::size_t) self->es.get_oosb());
}

static int EvalSpace_set_oosb(EvalSpaceObject* self, PyObject* val, void* closure){
    if(!PyLong_Check(val)){
        PyErr_SetString(PyExc_TypeError, "Value must be a boolean.");
        return -1;
    }
    self->es.set_oosb((softcircles::OutOfScopeBehavior) PyLong_AsSize_t(val));
    return 0;
}

static PyMethodDef EvalSpace_methods[] = {
    {"bind", (PyCFunction) EvalSpace_bind, METH_VARARGS, ""},
    {"unbind", (PyCFunction) EvalSpace_unbind, METH_VARARGS, ""},
    {"tick", (PyCFunction) EvalSpace_tick, METH_VARARGS, ""},
    {"set_dim", (PyCFunction) EvalSpace_set_dim, METH_VARARGS, ""},
    {NULL},
};

#include "soft_circle.h"
#include "force_conveyor.h"

static PyGetSetDef EvalSpace_getsetters[] = {
    {"bound", (getter) EvalSpace_get_bound<(PyObject*) &_EsBindableType>,NULL,"",NULL},
    {"soft_circles", (getter) EvalSpace_get_bound<(PyObject*) &SoftCircleType>, NULL, "", NULL},
    {"force_conveyors", (getter) EvalSpace_get_bound<(PyObject*) &ForceConveyorType>, NULL, "", NULL},
    {"oosb", (getter) EvalSpace_get_oosb, (setter) EvalSpace_set_oosb, "", NULL},
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

EvalSpaceObject* get_eso_for_binding(PyObject* obj){
    if(!PyObject_IsInstance(obj,(PyObject*) &EvalSpaceType)){
        PyErr_SetString(PyExc_TypeError,"Binding object must be of type Eval_Space.");
        return NULL;
    }
    return (EvalSpaceObject*) obj;
}

#include "eval_space/get_bound.h"

#endif