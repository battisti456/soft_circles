#ifndef EVAL_SPACE
#define EVAL_SPACE

#include "force_conveyors.h"
#include "soft_circle.h"
#include "vec2.h"//By: Chan Jer Shan, provided under the MIT License
#include <vector>


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

        OutOfScopeBehavior oosb = UNDEFINED;

        Soft_Circle_Link<T>** divs = nullptr;
    public:
        std::vector<Soft_Circle<T>*> soft_circles;
        std::vector<const Force_Conveyor<T>*> forces;
        std::vector<const Reaction_Force<T>*> reactions;

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
};

template <class T>
void Eval_Space<T>::make_divs() {
    #ifdef DEBUG_EVAL_TICK
        printf("Making divs...\n");
    #endif
    clear_divs();
    vec2<T> pos;
    int j,k;
    for (Soft_Circle<T> * const& sc : soft_circles) {
        #ifdef DEBUG_EVAL_TICK
            printf("Making div for %lu...\n",(unsigned long long int) sc);
        #endif
        if(out_of_scope(sc)){continue;}
        pos = sc->get_pos();
        j = (int) (pos.x/x_div_size);
        k = (int) (pos.y/y_div_size);
        add_to_div(j+k*num_div_x,sc);
    }
};

template <class T>
void Eval_Space<T>::add_to_div(int i, Soft_Circle<T>* sc) const {
    #ifdef DEBUG_EVAL_TICK
        printf("Adding %lu to div %d...\n",(unsigned long long int) sc,i);
    #endif
    divs[i] = new Soft_Circle_Link<T>(sc,divs[i]);
};

template<class T>
void Eval_Space<T>::clear_divs() const {
    #ifdef DEBUG_EVAL_TICK
        printf("Clearing divs...\n");
    #endif
    for (int i = 0; i < num_divs; i++){
        clear_div(i);
    }
};

template <class T>
void Eval_Space<T>::clear_div(int i) const {
    if(divs[i] != nullptr){
        #ifdef DEBUG_EVAL_TICK
            printf("Clearing div %d; %lu != %lu...\n",i,(unsigned long int) divs[i], (unsigned long int) nullptr);
        #endif
        delete divs[i];
        divs[i] = nullptr;
    }
};

template <class T>
void Eval_Space<T>::evaluate_forces() {
    #ifdef DEBUG_EVAL_TICK
        printf("Evaluating forces...\n");
    #endif
    Soft_Circle<T> *sc, *o_sc;
    Soft_Circle_Link<T> *scl, *o_scl;
    for(unsigned int j = 0; j < num_div_x; j++) {
        for(unsigned int k = 0; k < num_div_y; k++) {
            #ifdef DEBUG_EVAL_TICK
                printf("Analyzing block (%d,%d) -> div %d\n",j,k,j+k*num_div_x);
            #endif
            scl = divs[j+k*num_div_x];
            while(scl != nullptr){
                sc = scl->get_soft_circle();
                for(unsigned int o_j = j-1; o_j<=j+1;o_j++){
                    if(o_j < 0 || o_j >= num_div_x){continue;};
                    for(unsigned int o_k = k -1; o_k <= k+1;o_k++){
                        if(o_k < 0 || o_k >= num_div_y){continue;};
                        #ifdef DEBUG_EVAL_TICK
                            printf("Looking at neighbor (%d,%d) -> div %d\n",o_j,o_k,o_j+o_k*num_div_x);
                        #endif
                        o_scl=divs[o_j+o_k*num_div_x];
                        while(o_scl != nullptr){
                            o_sc = o_scl->get_soft_circle();
                            
                            if(o_sc != sc) {sc->include(o_sc);};
                            #ifdef DEBUG_EVAL_TICK
                                printf("Other from %lu -> %lu\n",o_scl,o_scl->get_next());
                            #endif
                            o_scl = o_scl->get_next();
                        }
                    }
                }
                #ifdef DEBUG_EVAL_TICK
                    printf("Main from %lu -> %lu\n",scl,scl->get_next());
                #endif
                scl = scl->get_next();
            }
        }
    }
    for(Soft_Circle<T> * sc: soft_circles) {
        for(const Force_Conveyor<T> * frc : forces){
            sc->include(frc->force(*sc));
        }
        for(const Reaction_Force<T> * frc: reactions){
            sc->include(frc->force(*sc));
        }
    }
};

template <class T>
void Eval_Space<T>::actuate_out_of_scope_behavior(){
    for(Soft_Circle<T> * sc : soft_circles){
        if(!out_of_scope(sc)){continue;}
        if(do_oosb(sc,sc->get_oosb())){continue;}//try to follow sc oosb
        if(do_oosb(sc,oosb)){continue;}//try to follow own oosb
        do_oosb(sc,IGNORE);//else, just ignore
    }
}

template <class T>
void Eval_Space<T>::tick_soft_circles(T t) {
    for(Soft_Circle<T> * sc : soft_circles) {
        #ifdef DEBUG_EVAL_TICK
            printf("Ticking sc...\n");
        #endif
        sc->tick(t);
    }
};

template <class T>
void Eval_Space<T>::tick(T t) {
    make_divs();
    evaluate_forces();
    tick_soft_circles(t);
    actuate_out_of_scope_behavior();
};

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

#include "eval_space_oosb.cpp"

#endif