#ifndef SOFT_CIRCLES_MODULE
#define SOFT_CIRCLES_MODULE


#include <Python.h>
#include "vec2.h" //By: Chan Jer Shan, provided under the MIT License
#include "soft_circles/soft_circle.h"
#include "soft_circles/eval_space.h"
#include "soft_circles/force_conveyors.h"

using num_type = double;
using sc_type = Soft_Circle<num_type>;
using es_type = Eval_Space<num_type>;
using fc_type = Force_Conveyor<num_type>;
using re_type = Reaction_Force<num_type>;

Py_ssize_t SoftCircleReferenceSize = sizeof(sc_type*);

template <class T>
T* get_ptr(PyObject *capsule){
    return (T*) PyCapsule_GetPointer(capsule,NULL);
}

template <class T>
T* get_ptr_from_args(PyObject *arg){
    PyObject* capsule;
    if(!PyArg_ParseTuple(arg,"O",&capsule)){return NULL;};
    return get_ptr<T>(capsule);
}

template <class T>
static PyObject *store_ptr(T* ptr){
    return PyCapsule_New(ptr,NULL,NULL);
}

template <class T>
static PyObject *method_delete(PyObject *self, PyObject *args){
    PyObject *capsule;
    if(!PyArg_ParseTuple(args,"O",&capsule)){return NULL;}
    T *item = get_ptr<T>(capsule);
    delete item;
}

static PyObject *PyTuple_From_Vec2(vec2<num_type> vec){
    PyObject* to_return = PyTuple_New(2);
    PyTuple_SetItem(to_return,0,PyFloat_FromDouble(vec.x));
    PyTuple_SetItem(to_return,1,PyFloat_FromDouble(vec.y));
    return to_return;
}

template <class T>
vec2<T> Vec2_From_PyTuple(PyObject* tuple){
    return vec2<T>(
        (T) PyFloat_AsDouble(
            PyTuple_GetItem(tuple,0)
        ),
        (T) PyFloat_AsDouble(
            PyTuple_GetItem(tuple,1)
        )
    );
}

static PyObject *method_get_address_from_capsule(PyObject *self, PyObject *args) {
    PyObject *capsule;
    if(!PyArg_ParseTuple(args,"O",&capsule)){return NULL;};
    return PyLong_FromSize_t((size_t) get_ptr<void>(capsule));
}

#include "soft_circles_module/eval_space.h"
#include "soft_circles_module/forces.h"
#include "soft_circles_module/soft_circle.h"

#endif