#ifndef SOFT_CIRCLES_KEEPER
#define SOFT_CIRCLES_KEEPER

#include "soft_circle.h"

namespace softcircles {

template <class T>
class Keeper{
    public:
    virtual void calc(const Soft_Circle<T>* sc, bool& should_apply, vec2<T>& dt_pos, vec2<T>& dt_vel) const {
        should_apply = false;
    }
};

template <class T>
class Keeper_Instance{
    private:
    const Keeper<T>* kp;
    const Soft_Circle<T>* sc;
    bool should_apply = false;
    vec2<T> dt_pos;
    vec2<T> dt_vel;
    public:
    Keeper_Instance(const Keeper<T>* kp, const Soft_Circle<T>* sc):kp(kp),sc(sc){}
    virtual bool calc(){kp->calc(sc,should_apply,dt_pos,dt_vel);return should_apply;}
    virtual void apply(Soft_Circle<T>* _sc){
        _sc->set_pos(_sc->get_pos()+dt_pos);
        _sc->set_vel(_sc->get_vel()+dt_vel);
    }
};

template <class T>
class Momentum_Keeper:public Keeper<T>{
    private:
    T mca = 0;
    T mct = 0;
    public:
    Momentum_Keeper(T mca, T mct): mca(mca), mct(mct) {}
    void calc(const Soft_Circle<T>* sc, bool& should_apply, vec2<T>& dt_pos, vec2<T>& dt_vel) const {
        pos_calc(sc,should_apply,dt_pos);
        if(!should_apply){return;}
        vel_calc(sc,dt_pos,dt_vel);
    }
    virtual void pos_calc(const Soft_Circle<T>* sc, bool& should_apply, vec2<T>& dt_pos) const {
        should_apply = false;
    }
    void vel_calc(const Soft_Circle<T>* sc, const vec2<T>& dt_pos, vec2<T>& dt_vel) const {
        vec2<T> dt_pos_norm = dt_pos.normalize();
        vec2<T> vel = sc->get_vel();
        vec2<T> axial = dt_pos_norm*dt_pos_norm.dot(vel);
        dt_vel = vel - (axial*mca+(vel - axial)*mct);
    }
};

template <class T>
class Box_Keeper:public Momentum_Keeper<T>{
    private:
    T left, up, right, down;
    public:

    Box_Keeper<T>(T mca, T mct, T left, T up, T right, T down): Momentum_Keeper(mca,mct), left(left), up(up), right(right), down(down){}

    void pos_calc(const Soft_Circle<T>* sc, bool& should_apply, vec2<T>& dt_pos) const {
        vec2<T> pos = sc->get_pos();
        vec2<T> new_pos;
        T r = sc.get_r();
        if(left + r < pos.x){new_pos.x = left + r; should_apply = true;}
        if(right - r > pos.x){new_pos.x = right - r; should_apply = true;}
        if(down + r < pos.y){new_pos.y = down + r; should_apply = true;}
        if(up - r > pos.y){new_pos.y = up - r; should_apply = true;}
        if(!should_apply){return;}
        dt_pos = new_pos - pos;
    }
};

}

#endif