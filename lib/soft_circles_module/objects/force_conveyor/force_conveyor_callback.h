#ifndef FORCE_CONVEYOR_CALLBACK
#define FORCE_CONVEYOR_CALLBACK

#include "soft_circles/force_conveyors.h"
#include "./_es_bindable.h"
#include "./soft_circle.h"
#include <Python.h>

using namespace softcircles;

template <class T>
class Python_Callback_Force_Conveyor:public Force_Conveyor<T> {
    private:
    _EsBindableObject* self;
    PyObject* callback;
    public:
    Python_Callback_Force_Conveyor(_EsBindableObject* _self, PyObject* _callback){self = _self; callback = _callback;};

    vec2<T> force(const Soft_Circle<T> * sc) const override {
        SoftCircleObject* sco = nullptr;
        PyObject* arg_tuple, *tuple;
        double x, y;
        for(PyObject* pyo : self->es->bound){
            if(!PyObject_IsInstance(pyo,(PyObject*) &SoftCircleType)){continue;}
            sco = (SoftCircleObject*) pyo;
            break;
        }
        if(sco == nullptr){
            PyErr_SetString(PyExc_RuntimeError, "Force conveyor callback received an sc that isn't in it's eso.");
            return vec2<T>();
        }
        arg_tuple = PyObject_CallFunctionObjArgs(callback,sco);
        Py_DECREF(arg_tuple);
        if(!PyArg_ParseTuple(arg_tuple,"O",&tuple)){return vec2<T>();};
        if(!PyArg_ParseTuple(tuple,"dd",&x,&y)){return vec2<T>();};
        return vec2<T>((T) x,(T) y);
    };
};


#endif