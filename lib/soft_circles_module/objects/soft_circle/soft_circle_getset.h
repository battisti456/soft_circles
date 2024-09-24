#ifndef SOFT_CIRCLE_GETSET
#define SOFT_CIRCLE_GETSET

#include "../soft_circle.h"

template <sc_getter<num_type> getter_func>
static PyObject* SoftCircle_get<getter_func>(SoftCircleObject* self, void* closure){
    return PyFloat_FromDouble(
        (self->sc->*(getter_func))()
    );
}

template <sc_setter<num_type> setter_func>
static int SoftCircle_set<setter_func>(SoftCircleObject* self, PyObject* value, void* closure){
    if(value == NULL){
        PyErr_SetString(PyExc_TypeError, "You cannot delete this attribute.");
        return -1;
    }
    num_type val;
    if(!py_to_num(value,val)){return -1;}
    (self->sc->*(setter_func))(val);
    return 0;
}

template <sc_getter<bool> getter_func>
static PyObject* SoftCircle_bool_get<getter_func>(SoftCircleObject* self, void* closure){
    return PyBool_FromLong(
        (int long) (self->sc->*(getter_func))()
    );
}

template <sc_setter<bool> setter_func>
static int SoftCircle_bool_set<setter_func>(SoftCircleObject* self, PyObject* value, void* closure){
    if(value == NULL){
        PyErr_SetString(PyExc_TypeError, "You cannot delete this attribute.");
        return -1;
    }
    int val = PyObject_IsTrue(value);
    if(val == -1){return -1;}
    (self->sc->*(setter_func))((bool) val);
    return 0;
}

template <sc_getter<std::size_t> getter_func>
static PyObject* SoftCircle_size_get<getter_func>(SoftCircleObject* self, void* closure){
    return PyLong_FromSize_t(
        (std::size_t) (self->sc->*(getter_func))()
    );
}

template <sc_setter<std::size_t> setter_func>
static int SoftCircle_size_set<setter_func>(SoftCircleObject* self, PyObject* value, void* closure){
    if(value == NULL){
        PyErr_SetString(PyExc_TypeError, "You cannot delete this attribute.");
        return -1;
    }
    if(!PyLong_Check(value)){
        PyErr_SetString(PyExc_TypeError, "Value must be an integer.");
        return -1;
    }
    (self->sc->*(setter_func))(PyLong_AsSize_t(value));
    return 0;
}

template <sc_getter<vec_type> getter_func>
static PyObject* SoftCircle_vec_get<getter_func>(SoftCircleObject* self, void* closure){
    vec_type vec = (self->sc->*(getter_func))();
    PyObject* to_return = PyTuple_New(2);
    PyTuple_SetItem(to_return,0,PyFloat_FromDouble(vec.x));
    PyTuple_SetItem(to_return,1,PyFloat_FromDouble(vec.y));
    return to_return;
}

template <sc_setter<vec_type> setter_func>
static int SoftCircle_vec_set<setter_func>(SoftCircleObject* self, PyObject* value, void* closure){
    if(value == NULL){
        PyErr_SetString(PyExc_TypeError, "You cannot delete this attribute.");
        return -1;
    }
    vec_type vec;
    if(!py_to_vec(value,vec)){return -1;}
    (self->sc->*(setter_func))(vec);
    return 0;
}

#endif