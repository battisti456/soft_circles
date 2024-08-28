#ifndef SOFT_CIRCLE_OBJECT
#define SOFT_CIRCLE_OBJECT

#define PY_SSIZE_T_CLEAN
#include "_es_bindable.h"
#include "./soft_circle_module.h"

template<class T>
using sc_getter = T (sc_type::*)() const;
template<class T>
using sc_setter = void (sc_type::*)(T);


typedef struct SoftCircleObject{
    _EsBindableObject esbo;
    sc_type* sc = nullptr;
    std::size_t index = 0;
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

static PyObject* SoftCircle__on_bound(SoftCircleObject *self, PyObject *arg);

static PyObject* SoftCircle__on_unbound(SoftCircleObject *self, PyObject *arg);

template <sc_getter<num_type> getter_func>
static PyObject* SoftCircle_get(SoftCircleObject* self, void* closure);

template <sc_setter<num_type> setter_func>
static int SoftCircle_set(SoftCircleObject* self, PyObject* value, void* closure);

template <sc_getter<vec_type> getter_func>
static PyObject* SoftCircle_vec_get(SoftCircleObject* self, void* closure);

template <sc_setter<vec_type> setter_func>
static int SoftCircle_vec_set(SoftCircleObject* self, PyObject* value, void* closure);

template <sc_getter<bool> getter_func>
static PyObject* SoftCircle_bool_get(SoftCircleObject* self, void* closure);

template <sc_setter<bool> setter_func>
static int SoftCircle_bool_set(SoftCircleObject* self, PyObject* value, void* closure);

template <sc_getter<std::size_t> getter_func>
static PyObject* SoftCircle_size_get(SoftCircleObject* self, void* closure);

template <sc_setter<std::size_t> setter_func>
static int SoftCircle_size_set(SoftCircleObject* self, PyObject* value, void* closure);

static PyMemberDef SoftCircle_members[] = {
    {NULL},
};

static PyMethodDef SoftCircle_methods[] = {
    {"_on_bound", (PyCFunction) SoftCircle__on_bound, METH_O, ""},
    {"_on_unbound", (PyCFunction) SoftCircle__on_unbound, METH_O, ""},
    {NULL},
};

static PyGetSetDef SoftCircle_getsetters[] = {
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
    {"is_immovable", (getter) SoftCircle_bool_get<&sc_type::is_immovable>, (setter) SoftCircle_bool_set<&sc_type::set_is_immovable>,"",NULL},
    {"is_tangible", (getter) SoftCircle_bool_get<&sc_type::is_tangible>, (setter) SoftCircle_bool_set<&sc_type::set_is_tangible>,"",NULL},
    {"oosb", (getter) SoftCircle_size_get<&sc_type::get_raw_oosb>, (setter) SoftCircle_size_set<&sc_type::set_raw_oosb>,"",NULL},
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
    .tp_base = &_EsBindableType,
    .tp_init = (initproc) SoftCircle_init,
    .tp_new = SoftCircle_new,
};

#include "soft_circle/soft_circle_methods.h"
#include "soft_circle/soft_circle_getset.h"

#endif