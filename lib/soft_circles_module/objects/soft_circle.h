#ifndef SOFT_CIRCLE_OBJECT
#define SOFT_CIRCLE_OBJECT

#define PY_SSIZE_T_CLEAN
#include "./soft_circle_module.h"

typedef struct SoftCircleObject {
    PyObject_HEAD
    sc_type* sc = nullptr;
    PyObject* es = nullptr;
    std::size_t index;
} SoftCircleObject;

static void SoftCircle_dealloc(SoftCircleObject* self){
    Py_TYPE(self)->tp_free((PyObject*) self);
};

static PyObject* SoftCircle_new(PyTypeObject *type, PyObject *args, PyObject *kwds){
    SoftCircleObject *self;
    self = (SoftCircleObject*) type->tp_alloc(type, 0);
    if(self != NULL){
        self->sc = new sc_type();
    }
    return (PyObject*) self;
};

static int SoftCircle_init(SoftCircleObject* self, PyObject *args, PyObject *kwds){
    return 0;
};

static PyObject* SoftCircle_get_eval_space(SoftCircleObject* self, void* closure){
    if(self->es == nullptr){return Py_None;} else {return self->es;}
}

template <num_type (sc_type::*getter_func)() const>
static PyObject* SoftCircle_get(SoftCircleObject* self, void* closure){
    return PyFloat_FromDouble(
        (self->sc->*(getter_func))()
    );
}

template <void (sc_type::*setter_func)(num_type)>
static int SoftCircle_set(SoftCircleObject* self, PyObject* value, void* closure){
    if(value == NULL){
        PyErr_SetString(PyExc_TypeError, "You cannot delete this attribute.");
        return -1;
    }
    if(!PyNumber_Float(value)){
        PyErr_SetString(PyExc_TypeError, "Value must be a floating point number.");
        return -1;
    }
    (self->sc->*(setter_func))(PyFloat_AS_DOUBLE(value));
    return 0;
}

template <vec2<num_type> (sc_type::*getter_func)() const>
static PyObject* SoftCircle_vec_get(SoftCircleObject* self, void* closure){
    vec2<num_type> vec = (self->sc->*(getter_func))();
    PyObject* to_return = PyTuple_New(2);
    PyTuple_SetItem(to_return,0,PyFloat_FromDouble(vec.x));
    PyTuple_SetItem(to_return,1,PyFloat_FromDouble(vec.y));
    return to_return;
}

template <void (sc_type::*setter_func)(num_type,num_type)>
static int SoftCircle_vec_set(SoftCircleObject* self, PyObject* value, void* closure){
    if(value == NULL){
        PyErr_SetString(PyExc_TypeError, "You cannot delete this attribute.");
        return -1;
    }
    if(!PyTuple_Check(value)){
        PyErr_SetString(PyExc_TypeError, "Value must be a floating point number.");
        return -1;
    }
    (self->sc->*(setter_func))(PyFloat_AS_DOUBLE(PyTuple_GET_ITEM(value,0)),PyFloat_AS_DOUBLE(PyTuple_GET_ITEM(value,1)));
    return 0;
}

static PyMemberDef SoftCircle_members[] = {
    {NULL},
};

static PyMethodDef SoftCircle_methods[] = {
    {NULL},
};

static PyGetSetDef SoftCircle_getsetters[] = {
    {"eval_space", (getter) SoftCircle_get_eval_space, NULL, "", NULL},
    {"m", (getter) SoftCircle_get<&sc_type::get_m>, (setter) SoftCircle_set<&sc_type::set_m>, "", NULL},
    {"r", (getter) SoftCircle_get<&sc_type::get_r>, (setter) SoftCircle_set<&sc_type::set_r>, "", NULL},
    {"f", (getter) SoftCircle_get<&sc_type::get_f>, (setter) SoftCircle_set<&sc_type::set_f>, "", NULL},
    {"t", (getter) SoftCircle_get<&sc_type::get_t>, (setter) SoftCircle_set<&sc_type::set_t>, "", NULL},
    {"k", (getter) SoftCircle_get<&sc_type::get_k>, (setter) SoftCircle_set<&sc_type::set_k>, "", NULL},
    {"a", (getter) SoftCircle_get<&sc_type::get_a>, (setter) SoftCircle_set<&sc_type::set_a>, "", NULL},
    {"b", (getter) SoftCircle_get<&sc_type::get_b>, (setter) SoftCircle_set<&sc_type::set_b>, "", NULL},
    {"position", (getter) SoftCircle_vec_get<&sc_type::get_pos>, (setter) SoftCircle_vec_set<&sc_type::set_pos>, "", NULL},
    {"velocity", (getter) SoftCircle_vec_get<&sc_type::get_vel>, (setter) SoftCircle_vec_set<&sc_type::set_vel>, "", NULL},
    {"acceleration", (getter) SoftCircle_vec_get<&sc_type::get_acc>, (setter) SoftCircle_vec_set<&sc_type::set_acc>, "", NULL},
    {NULL}
};

static PyTypeObject SoftCircleType = {
    .ob_base = PyVarObject_HEAD_INIT(NULL,0)
    .tp_name = "soft_circles_module.Soft_Circle",
    .tp_basicsize = sizeof(SoftCircleObject),
    .tp_itemsize = 0,
    .tp_dealloc = (destructor) SoftCircle_dealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = PyDoc_STR("Eval space object."),
    .tp_methods = SoftCircle_methods,
    .tp_members = SoftCircle_members,
    .tp_getset = SoftCircle_getsetters,
    .tp_init = (initproc) SoftCircle_init,
    .tp_new = SoftCircle_new,
};

#endif