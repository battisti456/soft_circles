#include "../eval_space.h"

#if defined DEBUG_EVAL_TICK
    #define D(x) x;
#else
    #define D(x)
#endif

namespace softcircles {

template <class T>
void Eval_Space<T>::tick(T t) {
    D(printf("Ticking with dt = %f...\n",t))
    evaluate_forces();
    tick_soft_circles(t);
    actuate_out_of_scope_behavior();
    D(printf("End tick...\n"))
};

template <class T>
void Eval_Space<T>::tick_soft_circles(T t) {
    D(printf("Ticking soft circles...\n"))
    Keeper_Instance<T> kpi(nullptr,nullptr);
    for(Soft_Circle<T> &sc : _soft_circles) {
        //D(printf("Ticking sc...\n"))
        sc.tick(t);
    }
    for(const Keeper<T>* kp : keepers){
        for(Soft_Circle<T>& sc : _soft_circles){
            kpi = Keeper_Instance<T>(kp,&sc);
            if(kpi.calc()){
                kpi.apply(&sc);
            }
        }
    }
};

}

#undef D