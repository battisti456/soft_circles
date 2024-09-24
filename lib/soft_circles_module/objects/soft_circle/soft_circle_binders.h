#ifndef SOFT_CIRCLE_METHODS
#define SOFT_CIRCLE_METHODS

#include "./soft_circle.h"
#include "./eval_space.h"
#include "./_es_bindable.h"

void add_reallocate(EvalSpaceObject* eso){
    SoftCircleObject* sco;
    for (PyObject* ebo: eso->bound){
        if(!PyObject_TypeCheck(ebo,&SoftCircleType)) {continue;}
            sco = (SoftCircleObject*) ebo;
            sco->sc = &(eso->es._soft_circles[sco->index]);
    }
}

void remove_reallocate(EvalSpaceObject* eso, std::size_t i){
    SoftCircleObject* sco;
    for(PyObject* pyo : eso->bound){
        if(!PyObject_IsInstance(pyo,(PyObject*) &SoftCircleType)){continue;}
        sco = (SoftCircleObject*) pyo;
        if(sco->index < i){continue;}
        sco->index -= 1;
        sco->sc = &(eso->es._soft_circles[sco->index]);
    }
}

static PyObject* SoftCircle__on_bound(SoftCircleObject *self, PyObject *arg){
    EvalSpaceObject* eso = get_eso_for_binding(arg);
    if(eso == NULL){return NULL;}
    if(_EsBindable__on_bound((_EsBindableObject*) self, (_Binder*) arg) == NULL){return NULL;}
    self->index = eso->es._soft_circles.size();
    eso->es._soft_circles.push_back(*(self->sc));
    delete self->sc;
    self->sc = &(eso->es._soft_circles[self->index]);
    add_reallocate(eso);
    return Py_None;
}

static PyObject* SoftCircle__on_unbound(SoftCircleObject *self, PyObject *arg){
    EvalSpaceObject* eso = get_eso_for_binding(arg);
    if(eso == NULL){return NULL;}
    if(_EsBindable__on_unbound((_EsBindableObject*) self, (_Binder*) arg) == NULL){return NULL;}
    eso->es._soft_circles.erase(eso->es._soft_circles.begin() + self->index);
    remove_reallocate(eso,self->index);
    self->index = 0;
    return Py_None;
}

#endif