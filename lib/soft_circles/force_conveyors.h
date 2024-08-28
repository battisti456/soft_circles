#ifndef FORCE_CONVEYORS
#define FORCE_CONVEYORS

#include "vec2.h"
#include "soft_circle.h"
#include <cmath>

template <class T>
class Force_Conveyor{
    public:
    virtual vec2<T> force(const Soft_Circle<T> * sc) const {return vec2<T>();};
};

template <class T>
class Soft_Circle_Gravity:public Force_Conveyor<T> {
    private:
    T g;
    const Soft_Circle<T> * g_sc;
    public:
    Soft_Circle_Gravity<T>(const Soft_Circle<T>* sc, T set_G){g_sc = sc; g = set_G;};

    vec2<T> force(const Soft_Circle<T> * sc) const override {
        vec2<T> dist = g_sc->get_pos() - sc->get_pos();
        return (
            g*(sc->get_m())*(g_sc->get_m())
            /(pow(dist.length(),2)))
            *dist.normalize();
    };
};

template <class T>
class Point_Force: public Force_Conveyor<T> {
    private:
    vec2<T> pos;
    T f;
    public:
    Point_Force<T>(vec2<T> new_pos, T new_f){pos = new_pos; f = new_f;}

    vec2<T> force(const Soft_Circle<T> * sc) const override {
        vec2<T> dist = pos - sc->get_pos();
        return f*dist.normalize();
    }
};

template <class T>
class Simple_Drag: public Force_Conveyor<T> {
    private:
    T c;
    public:
    Simple_Drag<T>(T _c){c = _c;}

    vec2<T> force(const Soft_Circle<T> * sc) const override {
        vec2<T> vel = sc->get_vel();
        return -vel.normalize()*c*vel.length()*vel.length();
    }
};

#endif