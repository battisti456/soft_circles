#ifndef EVAL_SPACE
#define EVAL_SPACE

#include "force_conveyors.h"
#include "soft_circle.h"
#include "vec2.h"//By: Chan Jer Shan, provided under the MIT License
#include <vector>
#include <thread>

#if defined DEBUG_EVAL_SPACE
    #define D(x) x;
#else
    #define D(x)
#endif


template <class T>
class Soft_Circle_Link{
    private:
        Soft_Circle<T> *soft_circle;
        Soft_Circle_Link<T> *next = nullptr;
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
        unsigned int num_div_x;
        unsigned int num_div_y;
        unsigned int num_divs;
        T x_div_size;
        T y_div_size;

        unsigned int interaction_map_dim;
        bool * interaction_map = nullptr;

        bool get_interacted(Soft_Circle<T>* sc1, Soft_Circle<T>* sc2);
        void set_interacted(Soft_Circle<T> *sc1, Soft_Circle<T>* sc2, bool _set);
        void set_interacted(Soft_Circle<T> *sc1, Soft_Circle<T>* sc2) {set_interacted(sc1,sc2,true);}
        void clear_interactions();

        OutOfScopeBehavior oosb = UNDEFINED;

        Soft_Circle_Link<T>** divs = nullptr;

        void eval_main();
    public:
        std::vector<Soft_Circle<T>> _soft_circles;
        std::vector<const Force_Conveyor<T>*> forces;
        Eval_Space(T x_size, T y_size, unsigned int x_divs, unsigned int y_divs);
        ~Eval_Space();


        OutOfScopeBehavior get_oosb() const {return oosb;}
        void set_oosb(OutOfScopeBehavior new_oosb){oosb = new_oosb;}

        void make_divs();
        void add_to_div(int i, Soft_Circle<T> *sc) const;
        void clear_divs() const;
        void clear_div(int i) const;

        void evaluate_forces();
        void actuate_out_of_scope_behavior();
        void tick_soft_circles(T t);
        void tick(T t);

        void set_es_ids();

        bool out_of_scope(const Soft_Circle<T> * sc){
            vec2<T> pos = sc->get_pos();
            return pos.x < 0 || pos.y < 0 || pos.x > x || pos.y > y;
        }

        bool do_oosb(Soft_Circle<T> *sc, OutOfScopeBehavior oosb);

        void oosb_keep_in(Soft_Circle<T> *sc);
};

template <class T>
Eval_Space<T>::Eval_Space(T x_size, T y_size, unsigned int x_divs, unsigned int y_divs){
    x = x_size;
    y = y_size;
    num_div_x = x_divs; 
    num_div_y = y_divs;
    num_divs = num_div_x*num_div_y;
    x_div_size = x/num_div_x;
    y_div_size = y/num_div_y;

    divs = (Soft_Circle_Link<T>**) malloc(sizeof(Soft_Circle_Link<T>*)*num_divs);
    for(unsigned i = 0; i < num_divs; i++){divs[i] = nullptr;};
};

template <class T> 
Eval_Space<T>::~Eval_Space() {
    clear_divs();
    free(divs);
    free(interaction_map);
};

template <class T>
void Eval_Space<T>::make_divs() {
    D(printf("Making divs...\n"))
    clear_divs();
    vec2<T> pos;
    int j,k;
    for (Soft_Circle<T> &sc : _soft_circles) {
        //D(printf("Making div for %lu...\n",(unsigned long long int) sc))
        if(out_of_scope(&sc)){continue;}
        if(!sc.is_tangible()){continue;}
        pos = sc.get_pos();
        j = (int) (pos.x/x_div_size);
        k = (int) (pos.y/y_div_size);
        add_to_div(j+k*num_div_x,&sc);
    }
};

template <class T>
void Eval_Space<T>::add_to_div(int i, Soft_Circle<T>* sc) const {
    //D(printf("Adding %lu to div %d...\n",(unsigned long long int) sc,i))
    divs[i] = new Soft_Circle_Link<T>(sc,divs[i]);
};

template<class T>
void Eval_Space<T>::clear_divs() const {
    //D(printf("Clearing divs...\n"))
    for (unsigned int i = 0; i < num_divs; i++){
        clear_div(i);
    }
};

template <class T>
void Eval_Space<T>::clear_div(int i) const {
    if(divs[i] != nullptr){
        D(printf("Clearing div %d; %lu != %lu...\n",i,(unsigned long int) divs[i], (unsigned long int) nullptr))
        delete divs[i];
        divs[i] = nullptr;
    }
};

template <class T>
void Eval_Space<T>::tick_soft_circles(T t) {
    for(Soft_Circle<T> &sc : _soft_circles) {
        //D(printf("Ticking sc...\n"))
        sc.tick(t);
    }
};

template <class T>
void Eval_Space<T>::evaluate_forces() {
    D(printf("Evaluating forces...\n"))
    eval_main();
};

template <class T>
void Eval_Space<T>::actuate_out_of_scope_behavior(){
    for(Soft_Circle<T> &sc : _soft_circles){
        if(!out_of_scope(&sc)){continue;}
        if(do_oosb(&sc,sc.get_oosb())){continue;}//try to follow sc oosb
        if(do_oosb(&sc,oosb)){continue;}//try to follow own oosb
        do_oosb(&sc,IGNORE);//else, just ignore
    }
}

#undef D

#include "eval_space/evaluate_forces.h"
#include "eval_space/oosb.h"
#include "eval_space/interactions.h"
#include "eval_space/tick.h"

#endif