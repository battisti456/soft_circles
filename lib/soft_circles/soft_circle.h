#ifndef SOFT_CIRCLE
#define SOFT_CIRCLE

#include "vec2.h"//By: Chan Jer Shan, provided under the MIT License
#include <cmath>

namespace softcircles {

enum OutOfScopeBehavior {
    KEEP_IN,
    IGNORE,
    UNDEFINED,
    SET_IMMOVABLE,
    SET_INTANGIBLE,
    SET_IMMOVABLE_AND_INTANGIBLE,
};

template <class T>
T curve_func(const T& a, const T& b, const T& _d){
    T v = 1-pow(_d,a);
    return v*v*v+3*v*v*b*_d;
}

template <class T>
class Soft_Circle {
    private:
        vec2<T> pos = vec2<T>();
        vec2<T> vel = vec2<T>();
        vec2<T> acc = vec2<T>();

        vec2<T> net_force = vec2<T>();

        T m = 1;//the mass (or resistance to force) of a circle a = F/m
        T r = 0.5;//the radius of influence of the circle
        T f = 0;//the f parameter in F(v) = vf
        T t = 0.5;//the t parameter in s(d) = t*c(d/(r))
        T k = 0;//unused
        T a = 2.9;//the a parameter in c(_d) = (1-_d^a)^3+3(1-_d^a)^2*x*b
        T b = -0.175;//the b parameter in c(_d) = (1-_d^a)^3+3(1-_d^a)^2*x*b

        unsigned int es_id;

        bool immovable = false;
        bool tangible = true;

        OutOfScopeBehavior oosb = UNDEFINED;
    public:
        Soft_Circle(){}
        Soft_Circle(T s_m, T s_r, T s_f, T s_t, T s_k, T s_a, T s_b);

        void include(vec2<T> force);
        void include(Soft_Circle<T>* other);
        void tick(T dt);
        vec2<T> repelling_force(const Soft_Circle<T>* other) const;
        vec2<T> friction_force(const Soft_Circle<T>* other) const;

        void set_es_id(unsigned int _es_id){es_id = _es_id;}
        void set_pos(T x, T y) {pos.set(x,y);};
        void set_pos(vec2<T> new_pos) {pos.set(new_pos.x,new_pos.y);};
        void set_vel(T x, T y) {vel.set(x,y);};
        void set_vel(vec2<T> new_vel) {vel.set(new_vel.x,new_vel.y);};
        void set_acc(T x, T y) {acc.set(x,y);};
        void set_acc(vec2<T> new_acc) {acc.set(new_acc.x,new_acc.y);};
        
        unsigned int get_es_id() const {return es_id;}
        vec2<T> get_pos() const {return pos;};
        vec2<T> get_vel() const {return vel;};
        vec2<T> get_acc() const {return acc;};
        T get_m() const {return m;};
        T get_r() const {return r;};
        T get_f() const {return f;};
        T get_t() const {return t;};
        T get_k() const {return k;};
        T get_a() const {return a;};
        T get_b() const {return b;};
        void set_m(T val){m = val;}
        void set_r(T val){r = val;}
        void set_f(T val){f = val;}
        void set_t(T val){t = val;}
        void set_k(T val){k = val;}
        void set_a(T val){a = val;}
        void set_b(T val){b = val;}

        vec2<T> get_net_force() const {return net_force;}

        OutOfScopeBehavior get_oosb() const {return oosb;};
        void set_oosb(OutOfScopeBehavior new_oosb){oosb = new_oosb;};

        std::size_t get_raw_oosb() const {return (std::size_t) oosb;}
        void set_raw_oosb(std::size_t new_oosb){oosb = (OutOfScopeBehavior) new_oosb;}

        bool is_immovable() const {return immovable;}
        bool is_tangible() const {return tangible;}
        void set_is_immovable(bool set_value) {immovable = set_value;}
        void set_is_tangible(bool set_value) {tangible = set_value;}

        bool operator==(const Soft_Circle<T> & sc) const {return this == &sc;};
};

template <class T>
Soft_Circle<T>::Soft_Circle(T s_m, T s_r, T s_f, T s_t, T s_k, T s_a, T s_b) {
    m = s_m;
    r = s_r;
    f = s_f;
    t = s_t;
    k = s_k;
    a = s_a;
    b = s_b;
};

template <class T>
void Soft_Circle<T>::include(vec2<T> force) {
    net_force += force;
}

template <class T>
void Soft_Circle<T>::include(Soft_Circle<T>* other) {
    include(repelling_force(other));
    include(friction_force(other));
}

template <class T>
void Soft_Circle<T>::tick(T dt) {
    if (immovable){
    } else {
        set_acc(net_force/m);
    }
    net_force.set(0,0);
    set_pos(pos + vel*dt + acc*(dt*dt/2));
    set_vel(vel + acc*dt);
};

template <class T>
vec2<T> Soft_Circle<T>::repelling_force(const Soft_Circle<T>* other) const {
    //see https://www.desmos.com/calculator/qqfglogu3g
    vec2<T> diff = (pos - other->pos);
    T total_r = r + other->r;
    T d = total_r - diff.length();
    if(d <= 0) {return vec2<T>();};

    T c = curve_func(a+other->a,b+other->b,d/total_r);
    T s = c*(k+other->k);
    return s*diff.normalize();
};

template <class T>
vec2<T> Soft_Circle<T>::friction_force(const Soft_Circle<T>* other) const {
    return vec2<T>();
    vec2<T> diff = (vel - other->get_vel());
    T total_f = f + other->get_f();
    return diff*total_f;
};

}

#endif