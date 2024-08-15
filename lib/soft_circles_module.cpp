//https://realpython.com/build-python-c-extension-module/

//#define DEBUG_EVAL_TICK

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

static PyObject *PyTuple_From_Vec2(vec2<num_type> &vec){
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
#pragma region soft_circles
static PyObject *method_make_soft_circle(PyObject *self, PyObject *args){
    num_type m,r,f,t,k,a,b;
    if (!PyArg_ParseTuple(args,"ddddddd",&m,&r,&f,&t,&k,&a,&b)){
        return NULL;
    }
    if(m <= 0) {
        return NULL;
    }
    sc_type *sc = new sc_type(m,r,f,t,k,a,b);
    return store_ptr<sc_type>(sc);
}

static PyObject *method_get_soft_circle_is_immovable(PyObject *self, PyObject *args){
    PyObject *capsule;
    if(!PyArg_ParseTuple(args,"O",&capsule)){return NULL;};
    return PyBool_FromLong(get_ptr<sc_type>(capsule)->is_immovable());
}

static PyObject *method_set_soft_circle_is_immovable(PyObject *self, PyObject *args){
    PyObject *capsule;
    bool value;
    if(!PyArg_ParseTuple(args,"Op",&capsule,&value)){return NULL;};
    get_ptr<sc_type>(capsule)->set_is_immovable(value);
    return Py_None;
}

static PyObject *method_get_soft_circle_position(PyObject *self, PyObject *args){
    sc_type *sc = get_ptr_from_args<sc_type>(args);
    if(sc == NULL){return NULL;};
    return PyTuple_From_Vec2(sc->get_pos());
}

static PyObject *method_set_soft_circle_position(PyObject *self, PyObject *args){
    PyObject *capsule, *tuple;
    if(!PyArg_ParseTuple(args,"OO",&capsule,&tuple)){return NULL;};
    sc_type *sc = get_ptr<sc_type>(capsule);
    sc->set_pos(Vec2_From_PyTuple<num_type>(tuple));
}

static PyObject *method_get_soft_circle_velocity(PyObject *self, PyObject *args){
    sc_type *sc = get_ptr_from_args<sc_type>(args);
    if(sc == NULL){return NULL;};
    return PyTuple_From_Vec2(sc->get_vel());
}

static PyObject *method_set_soft_circle_velocity(PyObject *self, PyObject *args){
    PyObject *capsule, *tuple;
    if(!PyArg_ParseTuple(args,"OO",&capsule,&tuple)){return NULL;};
    sc_type *sc = get_ptr<sc_type>(capsule);
    sc->set_vel(Vec2_From_PyTuple<num_type>(tuple));
}

static PyObject *method_get_soft_circle_acceleration(PyObject *self, PyObject *args){
    sc_type *sc = get_ptr_from_args<sc_type>(args);
    if(sc == NULL){return NULL;};
    return PyTuple_From_Vec2(sc->get_acc());
}

static PyObject *method_set_soft_circle_acceleration(PyObject *self, PyObject *args){
    PyObject *capsule, *tuple;
    if(!PyArg_ParseTuple(args,"OO",&capsule,&tuple)){return NULL;};
    sc_type *sc = get_ptr<sc_type>(capsule);
    sc->set_acc(Vec2_From_PyTuple<num_type>(tuple));
}

static PyObject *method_get_soft_circle_m(PyObject *self, PyObject *args){
    PyObject *capsule;
    if(!PyArg_ParseTuple(args,"O",&capsule)){return NULL;};
    return PyFloat_FromDouble((double) (get_ptr<sc_type>(capsule))->get_m());
}

static PyObject *method_get_soft_circle_r(PyObject *self, PyObject *args){
    PyObject *capsule;
    if(!PyArg_ParseTuple(args,"O",&capsule)){return NULL;};
    return PyFloat_FromDouble((double) (get_ptr<sc_type>(capsule))->get_r());
}

static PyObject *method_get_soft_circle_f(PyObject *self, PyObject *args){
    PyObject *capsule;
    if(!PyArg_ParseTuple(args,"O",&capsule)){return NULL;};
    return PyFloat_FromDouble((double) (get_ptr<sc_type>(capsule))->get_f());
}

static PyObject *method_get_soft_circle_t(PyObject *self, PyObject *args){
    PyObject *capsule;
    if(!PyArg_ParseTuple(args,"O",&capsule)){return NULL;};
    return PyFloat_FromDouble((double) (get_ptr<sc_type>(capsule))->get_t());
}

static PyObject *method_get_soft_circle_k(PyObject *self, PyObject *args){
    PyObject *capsule;
    if(!PyArg_ParseTuple(args,"O",&capsule)){return NULL;};
    return PyFloat_FromDouble((double) (get_ptr<sc_type>(capsule))->get_k());
}

static PyObject *method_get_soft_circle_a(PyObject *self, PyObject *args){
    PyObject *capsule;
    if(!PyArg_ParseTuple(args,"O",&capsule)){return NULL;};
    return PyFloat_FromDouble((double) (get_ptr<sc_type>(capsule))->get_a());
}

static PyObject *method_get_soft_circle_b(PyObject *self, PyObject *args){
    PyObject *capsule;
    if(!PyArg_ParseTuple(args,"O",&capsule)){return NULL;};
    return PyFloat_FromDouble((double) (get_ptr<sc_type>(capsule))->get_b());
}
#pragma endregion

static PyObject *method_make_soft_circle_gravity(PyObject *self, PyObject *args) {
    PyObject *capsule;
    num_type g;
    if(!PyArg_ParseTuple(args,"Od",&capsule,&g)){return NULL;};
    sc_type *sc = get_ptr<sc_type>(capsule);
    return store_ptr<fc_type>(new Soft_Circle_Gravity<num_type>(sc,g));
}

#pragma region eval_space
static PyObject *method_make_eval_space(PyObject *self, PyObject *args){
    num_type x_size, y_size;
    unsigned int x_divs, y_divs;
    if(!PyArg_ParseTuple(args,"ddII",&x_size,&y_size,&x_divs,&y_divs)){return NULL;}
    es_type *to_return = new es_type(x_size,y_size,x_divs,y_divs);
    return store_ptr<es_type>(to_return);
}

static PyObject *method_add_soft_circle_to_eval_space(PyObject *self, PyObject *args){
    PyObject *sc_capsule, *es_capsule;
    if(!PyArg_ParseTuple(args,"OO",&es_capsule,&sc_capsule)){return NULL;}
    sc_type *sc = get_ptr<sc_type>(sc_capsule);
    es_type *es = get_ptr<es_type>(es_capsule);
    es->soft_circles.push_back(*sc);
}

static PyObject *method_remove_soft_circle_from_eval_space(PyObject *self, PyObject *args){
    PyObject *sc_capsule, *es_capsule;
    if(!PyArg_ParseTuple(args,"OO",&es_capsule,&sc_capsule)){return NULL;}
    sc_type *sc = get_ptr<sc_type>(sc_capsule);
    es_type *es = get_ptr<es_type>(es_capsule);
    es->soft_circles.remove(*sc);
}

static PyObject * method_tick_eval_space(PyObject *self, PyObject *args){
    int num_ticks;
    num_type dt;
    PyObject *capsule;
    if(!PyArg_ParseTuple(args,"OdI",&capsule,&dt,&num_ticks)){return NULL;};
    es_type *es = get_ptr<es_type>(capsule);
    for(int i = 0; i < num_ticks; i++){
        es->tick(dt);
    }
    return Py_None;
}

static PyObject *method_add_force_conveyor_to_eval_space(PyObject *self, PyObject *args){
    PyObject *fc_capsule, *es_capsule;
    if(!PyArg_ParseTuple(args,"OO",&es_capsule,&fc_capsule)){return NULL;};
    fc_type *fc = get_ptr<fc_type>(fc_capsule);
    es_type *es = get_ptr<es_type>(es_capsule);
    es->forces.push_back(fc);
}

#pragma endregion

static PyObject *method_get_address_from_capsule(PyObject *self, PyObject *args) {
    PyObject *capsule;
    if(!PyArg_ParseTuple(args,"O",&capsule)){return NULL;};
    return PyLong_FromSize_t((size_t) get_ptr<void>(capsule));
}

static PyMethodDef SoftCirclesMethods[] = {
    {"make_soft_circle",method_make_soft_circle, METH_VARARGS, ""},
    {"get_soft_circle_m",method_get_soft_circle_m, METH_VARARGS, ""},
    {"get_soft_circle_r",method_get_soft_circle_r, METH_VARARGS, ""},
    {"get_soft_circle_f",method_get_soft_circle_f, METH_VARARGS, ""},
    {"get_soft_circle_t",method_get_soft_circle_t, METH_VARARGS, ""},
    {"get_soft_circle_k",method_get_soft_circle_k, METH_VARARGS, ""},
    {"get_soft_circle_a",method_get_soft_circle_a, METH_VARARGS, ""},
    {"get_soft_circle_b",method_get_soft_circle_b, METH_VARARGS, ""},
    {"get_soft_circle_position",method_get_soft_circle_position, METH_VARARGS, ""},
    {"set_soft_circle_position",method_set_soft_circle_position, METH_VARARGS, ""},
    {"get_soft_circle_velocity",method_get_soft_circle_velocity, METH_VARARGS, ""},
    {"set_soft_circle_velocity",method_set_soft_circle_velocity, METH_VARARGS, ""},
    {"get_soft_circle_acceleration",method_get_soft_circle_acceleration, METH_VARARGS, ""},
    {"set_soft_circle_acceleration",method_set_soft_circle_acceleration, METH_VARARGS, ""},
    {"get_soft_circle_is_immovable",method_get_soft_circle_is_immovable, METH_VARARGS, ""},
    {"set_soft_circle_is_immovable",method_set_soft_circle_is_immovable, METH_VARARGS, ""},
    {"make_soft_circle_gravity",method_make_soft_circle_gravity, METH_VARARGS, ""},
    {"make_eval_space",method_make_eval_space, METH_VARARGS, ""},
    {"add_soft_circle_to_eval_space",method_add_soft_circle_to_eval_space, METH_VARARGS, ""},
    {"remove_soft_circle_from_eval_space",method_remove_soft_circle_from_eval_space, METH_VARARGS, ""},
    {"tick_eval_space",method_tick_eval_space, METH_VARARGS, ""},
    {"add_force_conveyor_to_eval_space",method_add_force_conveyor_to_eval_space, METH_VARARGS, ""},
    {"delete_soft_circle",method_delete<sc_type>, METH_VARARGS, ""},
    {"delete_eval_space",method_delete<es_type>, METH_VARARGS, ""},
    {"get_address_from_capsule",method_get_address_from_capsule, METH_VARARGS, ""},
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

