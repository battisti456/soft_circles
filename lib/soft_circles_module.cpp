//https://realpython.com/build-python-c-extension-module/

#include <Python.h>
#include "vec2.h" //By: Chan Jer Shan, provided under the MIT License
#include "soft_circles/soft_circle.h"
#include "soft_circles/eval_space.h"

using num_type = double;
using sc_type = Soft_Circle<num_type>;
using es_type = Eval_Space<num_type>;

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

static PyObject *PyTuple_FromVec2(vec2<num_type> &vec){
    PyObject* to_return = PyTuple_New(2);
    PyTuple_SetItem(to_return,0,PyFloat_FromDouble(vec.x));
    PyTuple_SetItem(to_return,1,PyFloat_FromDouble(vec.y));
    return to_return;
}
#pragma region soft_circles
static PyObject *PyTuple_FromSC(sc_type *sc) {
    PyObject *to_return = PyTuple_New(7);
    PyTuple_SetItem(to_return,0,PyFloat_FromDouble(sc->get_m()));
    PyTuple_SetItem(to_return,1,PyFloat_FromDouble(sc->get_r()));
    PyTuple_SetItem(to_return,2,PyFloat_FromDouble(sc->get_f()));
    PyTuple_SetItem(to_return,3,PyFloat_FromDouble(sc->get_t()));
    PyTuple_SetItem(to_return,4,PyFloat_FromDouble(sc->get_k()));
    PyTuple_SetItem(to_return,5,PyFloat_FromDouble(sc->get_a()));
    PyTuple_SetItem(to_return,6,PyFloat_FromDouble(sc->get_b()));
    return to_return;
}

static PyObject *method_make_soft_circle(PyObject *self, PyObject *args){
    num_type m,r,f,t,k,a,b;
    if (!PyArg_ParseTuple(args,"ddddddd",&m,&r,&f,&t,&k,&a,&b)){
        return NULL;
    }
    sc_type *sc = new sc_type(m,r,f,t,k,a,b);
    return store_ptr<sc_type>(sc);
}

static PyObject *method_get_soft_circle_position(PyObject *self, PyObject *args){
    sc_type *sc = get_ptr_from_args<sc_type>(args);
    if(sc == NULL){return NULL;};
    return PyTuple_FromVec2(sc->get_pos());
}

static PyObject *method_get_soft_circle_velocity(PyObject *self, PyObject *args){
    sc_type *sc = get_ptr_from_args<sc_type>(args);
    if(sc == NULL){return NULL;};
    return PyTuple_FromVec2(sc->get_vel());
}

static PyObject *method_get_soft_circle_acceleration(PyObject *self, PyObject *args){
    sc_type *sc = get_ptr_from_args<sc_type>(args);
    if(sc == NULL){return NULL;};
    return PyTuple_FromVec2(sc->get_acc());
}

static PyObject *method_get_soft_circle_constants(PyObject *self, PyObject *args){
    sc_type *sc = get_ptr_from_args<sc_type>(args);
    if(sc == NULL){return NULL;};
    return PyTuple_FromSC(sc);
}
#pragma endregion

static PyObject *method_make_eval_space(PyObject *self, PyObject *args){
    num_type x_size, y_size;
    unsigned int x_divs, y_divs;
    if(!PyArg_ParseTuple(args,"ddIIOI",&x_size,&y_size,&x_divs,&y_divs)){return NULL;}
    es_type *to_return = new es_type(x_size,y_size,x_divs,y_divs);
    return store_ptr<es_type>(to_return);
}

static PyObject *method_add_soft_circle_to_eval_space(PyObject *self, PyObject *args){
    PyObject *sc_capsule, *es_capsule;
    if(!PyArg_ParseTuple(args,"OO",&es_capsule,&sc_capsule)){return NULL;}
    sc_type *sc = get_ptr<sc_type>(sc_capsule);
    es_type *es = get_ptr<es_type>(es_capsule);
    es->add_soft_circle(*sc);
}

static PyObject *method_remove_soft_circle_from_eval_space(PyObject *self, PyObject *args){
    PyObject *sc_capsule, *es_capsule;
    if(!PyArg_ParseTuple(args,"OO",&es_capsule,&sc_capsule)){return NULL;}
    sc_type *sc = get_ptr<sc_type>(sc_capsule);
    es_type *es = get_ptr<es_type>(es_capsule);
    es->remove_soft_circle(*sc);
}

template <class T>
static PyObject * method_tick(PyObject *self, PyObject *args){
    num_type dt;
    PyObject *capsule;
    if(!PyArg_ParseTuple(args,"Od",&capsule,&dt)){return NULL;};
    es_typTe *es = get_ptr<T>(capsule);
    es->tick(dt);
    return Py_None;
}

static PyMethodDef SoftCirclesMethods[] = {
    {"make_soft_circle",method_make_soft_circle, METH_VARARGS, ""},
    {"get_soft_circle_position",method_get_soft_circle_position, METH_VARARGS, ""},
    {"get_soft_circle_velocity",method_get_soft_circle_velocity, METH_VARARGS, ""},
    {"get_soft_circle_acceleration",method_get_soft_circle_acceleration, METH_VARARGS, ""},
    {"get_soft_circle_constants",method_get_soft_circle_constants, METH_VARARGS, ""},
    {"make_eval_space",method_make_eval_space, METH_VARARGS, ""},
    {"add_soft_circle_to_eval_space",method_add_soft_circle_to_eval_space, METH_VARARGS, ""},
    {"remove_soft_circle_from_eval_space",method_remove_soft_circle_from_eval_space, METH_VARARGS, ""},
    {"tick_eval_space",method_tick<es_type>, METH_VARARGS, ""},
    {"tick_soft_circle",method_tick<sc_type>, METH_VARARGS, ""},
    {"delete_soft_circle",method_delete<sc_type>, METH_VARARGS, ""},
    {"delete_eval_space",method_delete<es_type>, METH_VARARGS, ""},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef soft_circles_module = {
    PyModuleDef_HEAD_INIT,
    "soft_circles",
    "A simple hello world test.",
    -1,
    SoftCirclesMethods
};

PyMODINIT_FUNC PyInit_soft_circles_module(void) {
    return PyModule_Create(&soft_circles_module);
};

