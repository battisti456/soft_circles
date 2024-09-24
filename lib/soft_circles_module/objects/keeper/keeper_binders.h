#ifndef KEEPER_METHODS
#define KEEPER_METHODS
#include "./keeper.h"
#include "./eval_space.h"

static PyObject* Keeper__on_bound(KeeperObject *self, PyObject *arg){
    EvalSpaceObject* eso = get_eso_for_binding(arg);
    if(eso == NULL){return NULL;}
    if(_EsBindable__on_bound((_EsBindableObject*) self, (_Binder*) arg) == NULL){return NULL;}
    eso->es.keepers.push_back(self->kp);
    return Py_None;
}

static PyObject* Keeper__on_unbound(KeeperObject *self, PyObject *arg){
    EvalSpaceObject* eso = get_eso_for_binding(arg);
    if(eso == NULL){return NULL;}
    if(_EsBindable__on_unbound((_EsBindableObject*) self, (_Binder*) arg) == NULL){return NULL;}
    eso->es.keepers.erase(std::find(eso->es.keepers.begin(),eso->es.keepers.end(),self->kp));
    return Py_None;
}

#endif