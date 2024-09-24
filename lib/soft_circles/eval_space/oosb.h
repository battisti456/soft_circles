#include "../eval_space.h"

#if defined DEBUG_EVAL_SPACE_OOSB
    #define D(x) x;
#else
    #define D(x)
#endif

namespace softcircles {

template <class T>
void Eval_Space<T>::actuate_out_of_scope_behavior(){
    D(printf("Actuating out of scope behavior...\n"))
    for(Soft_Circle<T> &sc : _soft_circles){
        if(!out_of_scope(&sc)){continue;}
        if(do_oosb(&sc,sc.get_oosb())){continue;}//try to follow sc oosb
        if(do_oosb(&sc,oosb)){continue;}//try to follow own oosb
        do_oosb(&sc,IGNORE);//else, just ignore
    }
}

template <class T>
bool Eval_Space<T>::do_oosb(Soft_Circle<T> * sc, OutOfScopeBehavior oosb){
    switch(sc->get_oosb()){
        case KEEP_IN:
            oosb_keep_in(sc);
            break;
        case IGNORE:
            break;
        case SET_IMMOVABLE:
            sc->set_is_immovable(false);
            break;
        case SET_INTANGIBLE:
            sc->set_is_tangible(false);
            break;
        case SET_IMMOVABLE_AND_INTANGIBLE:
            sc->set_is_immovable(false);
            sc->set_is_tangible(false);
            break;
        case UNDEFINED:
        default:
            return false;
    }
    return true;
}

template <class T>
void Eval_Space<T>::oosb_keep_in(Soft_Circle<T> * sc){
    vec2<T> pos = sc->get_pos();
    vec2<T> vel = sc->get_vel();
    if(pos.x < left){
        pos.x = left;
        vel.x = 0;
    } else if (pos.x > right){
        pos.x = right;
        vel.x = 0;
    }
    if (pos.y < down){
        pos.y = down;
        vel.y = 0;
    } else if (pos.y > top){
        pos.y = top;
        vel.y = 0;
    }
    sc->set_pos(pos);
    sc->set_vel(vel);
}

}

#undef D