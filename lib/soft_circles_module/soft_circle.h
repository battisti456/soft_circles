#include "./soft_circle_module.h"


static PyObject *method_make_soft_circle(PyObject *self, PyObject *args){
    num_type m,r,f,t,k,a,b;
    if (!PyArg_ParseTuple(args,"ddddddd",&m,&r,&f,&t,&k,&a,&b)){
        return NULL;
    }
    if(m <= 0) {
        return NULL;
    }
    sc_type *sc = new sc_type(m,r,f,t,k,a,b);
    #ifdef DEBUG_EVAL_TICK
        printf("Created SC %llu\n", (unsigned __int64) sc);
    #endif
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

static PyObject *method_get_soft_circle_out_of_scope_behavior(PyObject *self, PyObject *args){
    PyObject *capsule;
    if(!PyArg_ParseTuple(args,"O",&capsule)){return NULL;};
    return PyLong_FromLong((long int)get_ptr<sc_type>(capsule)->get_oosb());
}

static PyObject *method_set_soft_circle_out_of_scope_behavior(PyObject *self, PyObject *args){
    PyObject *capsule;
    unsigned int oosb;
    if(!PyArg_ParseTuple(args,"Ok",&capsule,&oosb)){return NULL;};
    sc_type *es = get_ptr<sc_type>(capsule);
    es->set_oosb((OutOfScopeBehavior) oosb);
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