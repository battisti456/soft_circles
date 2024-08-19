#define DEBUG_EVAL_SPACE

#include "soft_circle_module.h"


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
    {"get_soft_circle_out_of_scope_behavior",method_get_soft_circle_out_of_scope_behavior, METH_VARARGS, ""},
    {"set_soft_circle_out_of_scope_behavior",method_set_soft_circle_out_of_scope_behavior, METH_VARARGS, ""},
    {"make_soft_circle_gravity",method_make_soft_circle_gravity, METH_VARARGS, ""},
    {"make_point_force",method_make_point_force, METH_VARARGS, ""},
    {"make_simple_drag",method_make_simple_drag, METH_VARARGS, ""},
    {"make_simple_stillness",method_make_simple_stillness, METH_VARARGS, ""},
    {"make_eval_space",method_make_eval_space, METH_VARARGS, ""},
    {"add_soft_circle_to_eval_space",method_add_soft_circle_to_eval_space, METH_VARARGS, ""},
    {"remove_soft_circle_from_eval_space",method_remove_soft_circle_from_eval_space, METH_VARARGS, ""},
    {"tick_eval_space",method_tick_eval_space, METH_VARARGS, ""},
    {"add_force_conveyor_to_eval_space",method_add_force_conveyor_to_eval_space, METH_VARARGS, ""},
    {"add_reaction_to_eval_space",method_add_reaction_to_eval_space, METH_VARARGS, ""},
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

