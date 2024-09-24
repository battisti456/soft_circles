#ifndef EVAL_SPACE
#define EVAL_SPACE

#include "force_conveyors.h"
#include "keeper.h"
#include "soft_circle.h"
#include "vec2.h"//By: Chan Jer Shan, provided under the MIT License
#include <vector>

#include "Quadtree.h"

#if defined DEBUG_EVAL_SPACE
    #define D(x) x;
#else
    #define D(x)
#endif

namespace softcircles {

template <class T>
class Eval_Space{
    private:
        T left, top, right, down;
        T x_size;
        T y_size;

        OutOfScopeBehavior oosb = UNDEFINED;

        void eval_main();

        quadtree::Box<T> eval_box;

        void make_tree();
    public:
        std::vector<Soft_Circle<T>> _soft_circles;
        std::vector<const Force_Conveyor<T>*> forces;
        std::vector<const Keeper<T>*> keepers;

        Eval_Space(T _left, T _top, T _right, T _bottom) {set_dim(_left,_top,_right,_bottom);};

        void set_dim(T _left, T _top, T _right, T _bottom);

        OutOfScopeBehavior get_oosb() const {return oosb;}
        void set_oosb(OutOfScopeBehavior new_oosb){oosb = new_oosb;}

        void evaluate_forces();
        void actuate_out_of_scope_behavior();
        void tick_soft_circles(T t);
        void tick(T t);

        void set_es_ids();

        bool out_of_scope(const Soft_Circle<T> * sc){
            vec2<T> pos = sc->get_pos();
            return pos.x < left || pos.y < down || pos.x > right || pos.y > top;
        }

        bool do_oosb(Soft_Circle<T> *sc, OutOfScopeBehavior oosb);

        void oosb_keep_in(Soft_Circle<T> *sc);
};

template <class T>
void Eval_Space<T>::set_dim(T _left, T _top, T _right, T _bottom){
    left = _left;
    top = _top;
    right = _right;
    down = _bottom;
    x_size = right-left;
    y_size = top-down;
    eval_box = quadtree::Box<T>(left,top,x_size,y_size);
};

}

#undef D

#include "eval_space/oosb.h"
#include "eval_space/evaluate_forces.h"
#include "eval_space/tick.h"

#endif