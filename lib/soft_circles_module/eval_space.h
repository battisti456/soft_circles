#include "./soft_circle_module.h"
#include <algorithm>


#if defined DEBUG_EVAL_SPACE
    #define D(x) x;
#else
    #define D(x)
#endif

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
    sc_type * sc = get_ptr<sc_type>(sc_capsule);
    es_type * es = get_ptr<es_type>(es_capsule);
    D(printf("Adding sc%llu to es%llu...\n",sc,es))
    es->soft_circles.push_back(sc);

    es->set_es_ids();
    return Py_None;
}

static PyObject *method_remove_soft_circle_from_eval_space(PyObject *self, PyObject *args){
    PyObject *sc_capsule, *es_capsule;
    if(!PyArg_ParseTuple(args,"OO",&es_capsule,&sc_capsule)){return NULL;}
    sc_type *sc = get_ptr<sc_type>(sc_capsule);
    es_type *es = get_ptr<es_type>(es_capsule);
    std::vector<sc_type *>::iterator location = std::find(es->soft_circles.begin(),es->soft_circles.end(),sc);
    if(location == es->soft_circles.end()){
        PyErr_Format(
            PyExc_IndexError,
            "Soft circle was not in eval space to be removed."
        );
        return NULL;
    }
    es->soft_circles.erase(location);
    return Py_None;
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
    return Py_None;
}

static PyObject *method_add_reaction_to_eval_space(PyObject *self, PyObject *args){
    PyObject *re_capsule, *es_capsule;
    if(!PyArg_ParseTuple(args,"OO",&es_capsule,&re_capsule)){return NULL;};
    re_type *re = get_ptr<re_type>(re_capsule);
    es_type *es = get_ptr<es_type>(es_capsule);
    es->reactions.push_back(re);
    return Py_None;
}

#undef D