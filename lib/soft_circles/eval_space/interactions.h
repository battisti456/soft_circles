#include "./eval_space.h"

template <class T>
void Eval_Space<T>::set_es_ids() {
    interaction_map_dim = soft_circles.size();
    free(interaction_map);
    interaction_map = (bool*) malloc(sizeof(bool)*interaction_map_dim*interaction_map_dim);
    clear_interactions();
    unsigned int id = 0;
    for(Soft_Circle<T> * sc : soft_circles){
        sc->set_es_id(id++);
    }
};

template <class T>
bool Eval_Space<T>::get_interacted(Soft_Circle<T>* sc1, Soft_Circle<T>* sc2){
    return interaction_map[sc1->get_es_id() + sc2->get_es_id()*interaction_map_dim];
}

template <class T>
void Eval_Space<T>::set_interacted(Soft_Circle<T> *sc1, Soft_Circle<T>* sc2, bool _set){
    unsigned int id1 = sc1->get_es_id();
    unsigned int id2 = sc2->get_es_id();
    interaction_map[id1 + id2*interaction_map_dim] = _set;
    interaction_map[id2 + id1*interaction_map_dim] = _set;
}

template <class T>
void Eval_Space<T>::clear_interactions(){
    unsigned int total = interaction_map_dim*interaction_map_dim;
    for(unsigned int i = 0; i < total; i++){
        interaction_map[i] = false;
    }
    for(unsigned int i = 0; i <interaction_map_dim; i++){
        interaction_map[i + i*interaction_map_dim] = true;
    }
}