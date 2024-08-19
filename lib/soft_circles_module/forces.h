#include "./soft_circle_module.h"


static PyObject *method_make_soft_circle_gravity(PyObject *self, PyObject *args) {
    PyObject *capsule;
    num_type g;
    if(!PyArg_ParseTuple(args,"Od",&capsule,&g)){return NULL;};
    sc_type *sc = get_ptr<sc_type>(capsule);
    return store_ptr<fc_type>(new Soft_Circle_Gravity<num_type>(sc,g));
}

static PyObject *method_make_point_force(PyObject *self, PyObject *args) {
    num_type x,y,g;
    if(!PyArg_ParseTuple(args,"ddd",&x,&y,&g)){return NULL;};
    return store_ptr<fc_type>(new Point_Force<num_type>(vec2<num_type>(x,y),g));
}

static PyObject *method_make_simple_drag(PyObject *self, PyObject *args) {
    num_type c;
    if(!PyArg_ParseTuple(args,"d",&c)){return NULL;}
    return store_ptr<fc_type>(new Simple_Drag<num_type>(c));
}

static PyObject *method_make_simple_stillness(PyObject *self, PyObject *args) {
    num_type vel_on, f_off;
    if(!PyArg_ParseTuple(args,"dd",&vel_on,&f_off)){return NULL;}
    return store_ptr<re_type>(new Simple_Stillness<num_type>(vel_on,f_off));
}