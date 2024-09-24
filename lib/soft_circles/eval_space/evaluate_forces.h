#include "../eval_space.h"
#include <cmath>
#include "Quadtree.h"

#if defined DEBUG_EVAL_SPACE_EVALUATE_FORCES
    #define D(x) x;
#else
    #define D(x)
#endif

namespace softcircles {

template<class T>
const auto affect_box = [](Soft_Circle<T> *sc){
    vec2<T> pos = sc->get_pos();
    T d = sc->get_r()*2;
    return quadtree::Box<T>(pos.x-sc->get_r(),pos.y+sc->get_r(),d,d);
};

template <class T>
using QuadTree = quadtree::Quadtree<Soft_Circle<T>*,decltype(affect_box<T>),std::equal_to<Soft_Circle<T>*>,T>;

template <class T>
void Eval_Space<T>::evaluate_forces() {
    D(printf("Evaluating forces...\n"))
    eval_main();
};


template <class T>
void Eval_Space<T>::eval_main() {
    D(printf("Making Quadtree...\n"))
    QuadTree<T> quads(eval_box,affect_box<T>);
    for (Soft_Circle<T>& sc : _soft_circles){
        quads.add(&sc);
    }
    auto interactions = quads.findAllIntersections();
    vec2<T> force;
    D(printf("Evaluating soft circle interactions...\n"))
    for(std::pair<Soft_Circle<T>*,Soft_Circle<T>*> pair : interactions){
        force = vec2<T>();
        force += pair.first->repelling_force(pair.second);
        force += pair.first->friction_force(pair.second);
        pair.first->include(force);
        pair.second->include(-force);
    }
    D(printf("Applying the forces...\n"))
    for(Soft_Circle<T> & sc : _soft_circles){
        for(const Force_Conveyor<T> * fc : forces){
            sc.include(fc->force(&sc));
        }
    }
};

}

#undef D