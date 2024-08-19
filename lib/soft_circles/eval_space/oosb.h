#include "./eval_space.h"


template <class T>
bool Eval_Space<T>::do_oosb(Soft_Circle<T> * sc, OutOfScopeBehavior oosb){
    switch(sc->get_oosb()){
        case KEEP_IN:
            oosb_keep_in(sc);
            break;
        case IGNORE:
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
    if(pos.x < 0){
        pos.x = 0;
        vel.x = 0;
    } else if (pos.x > x){
        pos.x = x;
        vel.x = 0;
    }
    if (pos.y < 0){
        pos.y = 0;
        vel.y = 0;
    } else if (pos.y > y){
        pos.y = y;
        vel.y = 0;
    }
    sc->set_pos(pos);
    sc->set_vel(vel);
}