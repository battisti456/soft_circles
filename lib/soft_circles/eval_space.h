#ifndef EVAL_SPACE
#define EVAL_SPACE

#include "soft_circle.h"
#include "vec2.h"//By: Chan Jer Shan, provided under the MIT License
#include <list>

template <class T>
class Soft_Circle_Link{
    private:
        Soft_Circle<T> *soft_circle;
        Soft_Circle_Link<T> *next;
    public:
        Soft_Circle_Link(Soft_Circle<T> *sc){soft_circle = sc;};
        Soft_Circle_Link(Soft_Circle<T> *sc, Soft_Circle_Link<T> *next_link){soft_circle = sc; next = next_link;};
        ~Soft_Circle_Link(){delete next;};

        Soft_Circle<T>* get_soft_circle() const {return soft_circle;};
        Soft_Circle_Link<T>* get_next() const {return next;};
};

template <class T>
class Eval_Space{
    private:
        T x;
        T y;
        int num_div_x;
        int num_div_y;
        int num_divs;
        T x_div_size;
        T y_div_size;

        std::list<Soft_Circle<T>> lst{};
        Soft_Circle_Link<T>** divs = nullptr;
    public:
        Eval_Space(T x_size, T y_size, int x_divs, int y_divs);
        ~Eval_Space();

        void make_divs();
        void add_to_div(int i, Soft_Circle<T> *sc) const;
        void clear_divs() const;
        void clear_div(int i) const;

        void add_soft_circle(Soft_Circle<T> const &sc) const;
        void remove_soft_circle(Soft_Circle<T> const &sc) const;

        void evaluate_forces() const;
        void tick_soft_circles(T t) const;
        void tick(T t) const;
};

template <class T>
Eval_Space<T>::Eval_Space(T x_size, T y_size, int x_divs, int y_divs){
    x = x_size;
    y = y_size;
    num_div_x = x_divs; 
    num_div_y = y_divs;
    num_divs = num_div_x*num_div_y;
    x_div_size = x/num_div_x;
    y_div_size = y/num_div_y;

    divs = (Soft_Circle_Link<T>**) malloc(sizeof(Soft_Circle_Link<T>*)*num_divs);
};

template <class T> 
Eval_Space<T>::~Eval_Space() {
    clear_divs();
    free(divs);
};

template <class T>
void Eval_Space<T>::make_divs() {
    clear_divs();
    vec2<T> pos;
    int j,k;
    for (Soft_Circle<T> const& sc : lst) {
        pos = sc.get_pos()
        j = (int) (pos.x/x_div_size);
        k = (int) (pos.y/y_div_size);
        add_to_div(j+k*num_div_x,&sc);
    }
};

template <class T>
void Eval_Space<T>::add_to_div(int i, Soft_Circle<T>* sc) const {
    divs[i] = &Soft_Circle_Link<T>(sc,divs[i]);
}

template<class T>
void Eval_Space<T>::clear_divs() const {
    for (int i = 0; i < num_divs; i++){
        clear_div(i);
    }
}

template<class T>
void Eval_Space<T>::add_soft_circle(Soft_Circle<T> const &sc) const {
    lst.push_back(sc);
}

template<class T>
void Eval_Space<T>::remove_soft_circle(Soft_Circle<T> const &sc) const {
    lst.remove(sc);
}

template <class T>
void Eval_Space<T>::clear_div(int i) const {
    if(divs[i] != nullptr){
        delete divs[i];
        divs[i] = nullptr;
    }
}

template <class T>
void Eval_Space<T>::evaluate_forces() const {
    Soft_Circle<T> *sc, *o_sc;
    Soft_Circle_Link<T> *scl, *o_scl;
    for(int j = 0; j < num_div_x; j++) {
        for(int k = 0; k < num_div_y; k++) {
            scl = divs[j+k*num_div_x];
            while(scl != nullptr){
                sc = scl->get_soft_circle();
                for(int o_j = j-1; o_j<=j+1;o_j++){
                    if(o_j < 0 || o_j >= num_div_x){continue;};
                    for(int o_k = k -1; o_k <= k+1;o_k++){
                        if(o_k < 0 || o_k >= num_div_y){continue;};
                        o_scl=divs[o_j+o_k*num_div_x];
                        while(o_scl != nullptr){
                            o_sc = o_scl->get_soft_circle();
                            if(o_sc == sc) {continue;};
                            sc->include(o_sc);
                            o_scl = o_scl->get_next();
                        }
                    }
                }
                scl = scl->get_next();
            }
        }
    }
}

template <class T>
void Eval_Space<T>::tick_soft_circles(T t) const {
    for(Soft_Circle<T> & sc : lst) {
        sc.tick(t);
    }
}

template <class T>
void Eval_Space<T>::tick(T t) const {
    evaluate_forces();
    tick_soft_circles(t);
}

#endif