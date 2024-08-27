//#define DEBUG_EVAL_SPACE
//#define DEBUG_EVAL_TICK
//#define DEBUG_SOFT_CIRCLE
//#define DEBUG_EVAL_SPACE_EVALUATE_FORCES

#include "soft_circle_module.h"


static PyMethodDef SoftCirclesMethods[] = {
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef soft_circles_module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "soft_circles",
    .m_doc = "A simple hello world test.",
    .m_size = -1,
    .m_methods = SoftCirclesMethods
};

PyMODINIT_FUNC PyInit_soft_circles_module(void) {
    PyObject *m;
    if (PyType_Ready(&EvalSpaceType) < 0){
        return NULL;
    }
    if (PyType_Ready(&SoftCircleType) < 0){
        return NULL;
    }

    m = PyModule_Create(&soft_circles_module);

    if(m == NULL){
        return NULL;
    }

    BindException = PyErr_NewExceptionWithDoc(
        "soft_circles_module.BindException",
        NULL,
        NULL,
        NULL
    );

    if(!BindException){
        return NULL;
    }

    Py_INCREF(BindException);
    Py_INCREF(&EvalSpaceType);
    Py_INCREF(&SoftCircleType);
    if(
        PyModule_AddObject(m, "BindException", BindException) < 0 ||
        PyModule_AddObject(m, "Eval_Space", (PyObject*) &EvalSpaceType) < 0 ||
        PyModule_AddObject(m, "Soft_Circle", (PyObject*) &SoftCircleType) < 0
        ){
        Py_DECREF(BindException);
        Py_DECREF(&EvalSpaceType);
        Py_DECREF(&SoftCircleType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
};

