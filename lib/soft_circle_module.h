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
using vec_type = vec2<num_type>;


static PyObject *PyTuple_From_Vec2(vec2<num_type> vec){
    PyObject* to_return = PyTuple_New(2);
    PyTuple_SetItem(to_return,0,PyFloat_FromDouble(vec.x));
    PyTuple_SetItem(to_return,1,PyFloat_FromDouble(vec.y));
    return to_return;
};

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
};


#include "soft_circles_module/objects/exceptions.h"
#include "soft_circles_module/objects/_es_bindable.h"
#include "soft_circles_module/objects/soft_circle.h"
#include "soft_circles_module/objects/force_conveyor.h"
#include "soft_circles_module/objects/eval_space.h"

#endif