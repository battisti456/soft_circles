#include "./eval_space.h"
#include <cmath>

#if defined DEBUG_EVAL_SPACE_EVALUATE_FORCES
    #define D(x) x;
#else
    #define D(x)
#endif


template <class T>
void Eval_Space<T>::eval_main() {
    Soft_Circle<T> *sc, *o_sc;
    Soft_Circle_Link<T> *scl, *o_scl;
    for(unsigned int j = 0; j < num_div_x; j++) {
        for(unsigned int k = 0; k < num_div_y; k++) {
            //D(printf("Analyzing block (%d,%d) -> div %d\n",j,k,j+k*num_div_x))
            scl = divs[j+k*num_div_x];
            while(scl != nullptr){
                sc = scl->get_soft_circle();
                for(unsigned int o_j = j-1; o_j<=j+1;o_j++){
                    if(o_j < 0 || o_j >= num_div_x){continue;};
                    for(unsigned int o_k = k -1; o_k <= k+1;o_k++){
                        if(o_k < 0 || o_k >= num_div_y){continue;};
                        //D(printf("Looking at neighbor (%d,%d) -> div %d\n",o_j,o_k,o_j+o_k*num_div_x))
                        o_scl=divs[o_j+o_k*num_div_x];
                        while(o_scl != nullptr){
                            o_sc = o_scl->get_soft_circle();
                            if(!get_interacted(sc,o_sc)) {
                                sc->include(o_sc); 
                                set_interacted(sc,o_sc);
                                D(printf("sc%llu and sc%llu interacted\n",sc,o_sc))
                            };
                            //D(printf("Other from %lu -> %lu\n",o_scl,o_scl->get_next()))
                            o_scl = o_scl->get_next();
                        }
                    }
                }
                //D(printf("Main from %lu -> %lu\n",scl,scl->get_next()))
                scl = scl->get_next();
            }
        }
    }
    for(Soft_Circle<T> &sc: _soft_circles) {
        for(const Force_Conveyor<T> * frc : forces){
            sc.include(frc->force(&sc));
        }
        for(const Reaction_Force<T> * frc: reactions){
            sc.include(frc->force(&sc));
        }
    }
};


#undef D