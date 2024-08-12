#ifndef SOFT_CIRCLE
#define SOFT_CIRCLE

#include "vec2.h"//By: Chan Jer Shan, provided under the MIT License

template <class T>
class Soft_Circle {
    private:
        vec2<T> pos = vec2<T>();
        vec2<T> vel = vec2<T>();
        vec2<T> acc = vec2<T>();

        vec2<T> net_force = vec2<T>();

        T m;//the mass (or resistance to force) of a circle a = F/m
        T r;//the radius of influence of the circle
        T f;//the f parameter in F(v) = vf
        T t;//the t parameter in s(d) = t(1/(1+exp(-kd))^a*(1+b)-b
        T k;//the k parameter in s(d) = t(1/(1+exp(-kd))^a*(1+b)-b
        T a;//the a parameter in s(d) = t(1/(1+exp(-kd))^a*(1+b)-b
        T b;//the b parameter in s(d) = t(1/(1+exp(-kd))^a*(1+b)-b
    public:
        Soft_Circle(T s_m, T s_r, T s_f, T s_t, T s_k, T s_a, T s_b);

        void include(vec2<T> &force);
        void include(Soft_Circle<T>* other);
        void tick(T dt);
        vec2<T> repelling_force(Soft_Circle<T>* other) const;
        vec2<T> friction_force(Soft_Circle<T>* other) const;

        void set_pos(T x, T y) {pos = {x,y};};
        void set_pos(vec2<T> new_pos) {pos = new_pos;};
        
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
void Soft_Circle<T>::include(vec2<T> &force) {
    net_force += force;
}

template <class T>
void Soft_Circle<T>::include(Soft_Circle<T>* other) {
    include(repelling_force(other));
    include(friction_force(other));
}

template <class T>
void Soft_Circle<T>::tick(T dt) {
    acc = net_force/m;
    net_force.set(0,0);
    pos += vel*dt + acc*(dt*dt/2);
    vel += acc*dt;
};

template <class T>
vec2<T> Soft_Circle<T>::repelling_force(Soft_Circle<T>* other) const {
    vec2<T> diff = (pos - other->get_pos());
    T d = diff.length();
    if(d > r + other->r) {return vec2<T>();};
    T total_k = (k+other->get_k());
    T total_a = (a+other->get_a());
    T total_b = (b+other->get_b());
    T total_t = (t+other->get_t());
    T s = total_t*pow((1/(1+exp(-total_k*d))),total_a)*(1+total_b)-total_b;
    return s*diff.normalize();
};

template <class T>
vec2<T> Soft_Circle<T>::friction_force(Soft_Circle<T>* other) const {
    vec2<T> diff = (vel - other->get_vel());
    T total_f = f + other->get_f();
    return diff*total_f;
};

#endif