#include "./eval_space.h"

#if defined DEBUG_EVAL_TICK
    #define D(x) x;
#else
    #define D(x)
#endif


template <class T>
void Eval_Space<T>::tick(T t) {
    D(printf("tick\n"))
    make_divs();
    evaluate_forces();
    tick_soft_circles(t);
    actuate_out_of_scope_behavior();
    clear_interactions();
};

#undef D