#ifndef SOFT_CIRCLE_METHODS
#define SOFT_CIRCLE_METHODS

#include "./soft_circle.h"
#include "./eval_space.h"
#include "./_es_bindable.h"

static PyObject* SoftCircle__on_bound(SoftCircleObject *self, PyObject *arg){
    if(!PyObject_IsInstance(arg,(PyObject*) &EvalSpaceType)){
        PyErr_SetString(PyExc_TypeError,"Binding object must be of type Eval_Space.");
        return NULL;
    }
    EvalSpaceObject* eso = (EvalSpaceObject*) arg;
    if(_EsBindable__on_bound((_EsBindableObject*) self, (_Binder*) arg) == NULL){return NULL;}
    self->index = eso->es._soft_circles.size();
    eso->es._soft_circles.push_back(*(self->sc));
    self->sc = &(eso->es._soft_circles[self->index]);

    return Py_None;
}

static PyObject* SoftCircle__on_unbound(SoftCircleObject *self, PyObject *arg){
    if(!PyObject_IsInstance(arg,(PyObject*) &EvalSpaceType)){
        PyErr_SetString(PyExc_TypeError,"Binding object must be of type Eval_Space.");
        return NULL;
    }
    SoftCircleObject* sco;
    EvalSpaceObject* eso = (EvalSpaceObject*) arg;
    if(_EsBindable__on_unbound((_EsBindableObject*) self, (_Binder*) arg) == NULL){return NULL;}
    eso->es._soft_circles.erase(eso->es._soft_circles.begin() + self->index);
    for(PyObject* pyo : eso->bound){
        if(!PyObject_IsInstance(pyo,(PyObject*) &SoftCircleType)){continue;}
        sco = (SoftCircleObject*) pyo;
        if(sco->index < self->index){continue;}
        sco->index -= 1;
        sco->sc = &(eso->es._soft_circles[sco->index]);
    }
    self->index = 0;
    return Py_None;
}

#endif