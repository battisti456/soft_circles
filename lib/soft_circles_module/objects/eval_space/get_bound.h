#include "./eval_space.h"
#include "./bound_iter.h"


template <PyObject* type>
static PyObject* EvalSpace_get_bound(EvalSpaceObject* self, void* closure){
    return (PyObject*) BoundIter_raw_new(&BoundIterType,self,type);
}