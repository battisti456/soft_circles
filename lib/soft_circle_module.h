#ifndef SOFT_CIRCLES_MODULE
#define SOFT_CIRCLES_MODULE


#include <Python.h>
#include "vec2.h" //By: Chan Jer Shan, provided under the MIT License
#include "soft_circles/soft_circle.h"
#include "soft_circles/eval_space.h"
#include "soft_circles/force_conveyors.h"
#include "soft_circles/keeper.h"

using num_type = double;
using sc_type = softcircles::Soft_Circle<num_type>;
using es_type = softcircles::Eval_Space<num_type>;
using fc_type = softcircles::Force_Conveyor<num_type>;
using kp_type = softcircles::Keeper<num_type>;
using vec_type = vec2<num_type>;

bool py_to_num(PyObject* value, num_type& val){
    if(PyLong_Check(value)){
        val = (num_type) PyLong_AsLong(value);
    } else if (PyFloat_Check(value)){
        val = (num_type) PyFloat_AsDouble(value);
    } else {
        PyErr_SetString(PyExc_TypeError, "Value was not a compatible number type.");
        return false;
    }
    return true;
}

bool py_to_vec(PyObject* value, vec_type& val){
    if(!PySequence_Check(value)){PyErr_SetString(PyExc_TypeError,"Value is not sequence."); return false;}
    if(PySequence_Size(value) != 2){PyErr_SetString(PyExc_IndexError, "Value is not of length 2."); return false;}
    if(!py_to_num(PySequence_Fast_GET_ITEM(value,0),val.x)){return false;}
    if(!py_to_num(PySequence_Fast_GET_ITEM(value,1),val.y)){return false;}
    return true;
}


#include "soft_circles_module/objects/exceptions.h"
#include "soft_circles_module/objects/_es_bindable.h"
#include "soft_circles_module/objects/soft_circle.h"
#include "soft_circles_module/objects/force_conveyor.h"
#include "soft_circles_module/objects/keeper.h"
#include "soft_circles_module/objects/eval_space.h"

#endif