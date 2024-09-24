#ifndef KEEPER_MAKE
#define KEEPER_MAKE

#include "./keeper.h"

using namespace softcircles;

static KeeperObject* Keeper_make(PyTypeObject *type){
    return (KeeperObject*) Keeper_new(type,NULL,NULL);
};

static PyObject* Keeper_make_box(PyTypeObject *type, PyObject *args){
    KeeperObject* self = Keeper_make(type);
    double mca, mct, left, up, right, down;
    if(!PyArg_ParseTuple(args,"dddddd",&mca,&mct,&left,&up,&right,&down)){return NULL;}
    if(!PyObject_IsInstance(sco,(PyObject*) &KeeperType)){PyErr_SetString(PyExc_TypeError, "Must be of type Keeper."); return NULL;}
    self->kp = new Box_Keeper<num_type>(mca,mct,left,up,right,down);
    return (PyObject*) self;
};

#endif