#ifndef FORCE_CONVEYOR_METHODS
#define FORCE_CONVEYOR_METHODS
#include "./force_conveyor.h"
#include "./eval_space.h"

static PyObject* ForceConveyor__on_bound(ForceConveyorObject *self, PyObject *arg){
    EvalSpaceObject* eso = get_eso_for_binding(arg);
    if(eso == NULL){return NULL;}
    if(_EsBindable__on_bound((_EsBindableObject*) self, (_Binder*) arg) == NULL){return NULL;}
    eso->es.forces.push_back(self->fc);
    return Py_None;
}

static PyObject* ForceConveyor__on_unbound(ForceConveyorObject *self, PyObject *arg){
    EvalSpaceObject* eso = get_eso_for_binding(arg);
    if(eso == NULL){return NULL;}
    if(_EsBindable__on_unbound((_EsBindableObject*) self, (_Binder*) arg) == NULL){return NULL;}
    eso->es.forces.erase(std::find(eso->es.forces.begin(),eso->es.forces.end(),self->fc));
    return Py_None;
}

#endif