#include "./eval_space.h"
#include "./soft_circle.h"


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