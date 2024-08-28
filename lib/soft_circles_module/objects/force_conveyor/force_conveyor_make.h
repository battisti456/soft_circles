#ifndef FORCE_CONVEYOR_MAKE
#define FORCE_CONVEYOR_MAKE

#include "./force_conveyor.h"

static ForceConveyorObject* ForceConveyor_make(PyTypeObject *type){
    return (ForceConveyorObject*) _PyObject_New(type);
};

static PyObject* ForceConveyor_make_callback(PyTypeObject *type, PyObject *args){
    ForceConveyorObject* self = ForceConveyor_make(type);
    self->fc = new Python_Callback_Force_Conveyor<num_type>((_EsBindableObject*) self,PyObject_GetAttrString((PyObject*) self,"callback"));
    return (PyObject*) self;
};

static PyObject* ForceConveyor_make_soft_circle_gravity(PyTypeObject *type, PyObject *args){
    ForceConveyorObject* self = ForceConveyor_make(type);
    PyObject* sco;
    double strength;
    if(!PyArg_ParseTuple(args,"Od",&sco,&strength)){return NULL;}
    if(!PyObject_IsInstance(sco,(PyObject*) &SoftCircleType)){PyErr_SetString(PyExc_TypeError, "Must be of type Soft_Circle."); return NULL;}
    self->referencing.push_back(sco);
    Py_INCREF(sco);
    self->fc = new Soft_Circle_Gravity<num_type>(((SoftCircleObject*) sco)->sc,strength);
    return (PyObject*) self;
};

static PyObject* ForceConveyor_make_point_force(PyTypeObject *type, PyObject *args){
    ForceConveyorObject* self = ForceConveyor_make(type);
    PyObject* tuple;
    double strength;
    double x, y;
    if(!PyArg_ParseTuple(args,"Od",&tuple,&strength)){return NULL;}
    if(!PyArg_ParseTuple(tuple,"dd",&x,&y)){return NULL;}
    self->fc = new Point_Force<num_type>(vec2<num_type>(x,y),strength);
    return (PyObject*) self;
};

static PyObject* ForceConveyor_make_simple_drag(PyTypeObject *type, PyObject *args){
    ForceConveyorObject* self = ForceConveyor_make(type);
    double c;
    if(!PyArg_ParseTuple(args,"d",&c)){return NULL;}
    self->fc = new Simple_Drag<num_type>(c);
    return (PyObject*) self;
};

#endif