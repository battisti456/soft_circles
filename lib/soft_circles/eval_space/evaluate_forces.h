#include "./eval_space.h"
#include <cmath>

#if defined DEBUG_EVAL_SPACE_EVALUATE_FORCES
    #define D(x) x;
#else
    #define D(x)
#endif


template <class T>
void Eval_Space<T>::eval_main() {
    D(printf("Entering eval_main...\n"))
    threads.reserve(eval_row_threads_size+eval_col_threads_size*eval_num_threads_y);
    std::thread * row_threads = &threads.front();
    std::thread * col_threads = row_threads+eval_row_threads_size;
    for(int r = 0; r < 3; r++){
        D(printf("Launching row threads r = %d\n",r))
        for(int i = 0; i < eval_num_threads_y; i++) {
            new (&(row_threads[i])) std::thread(&Eval_Space<T>::eval_row, this, i*3+r, col_threads+i*eval_col_threads_size);
        }
        for(int i = 0; i < eval_num_threads_y; i++) {
            row_threads[i].join();
        }
    }
};

template <class T>
void Eval_Space<T>::eval_row(int row, std::thread *col_threads){
    if(row >= num_div_y){return;}
    for (int c = 0; c < 3; c++) {
        D(printf("Launching col threads c = %d\n",c))
        for(int i = 0; i < eval_num_threads_x; i ++){
            new (&col_threads[i]) std::thread(&Eval_Space<T>::eval_index, this, row, i*3+c);
        }
        for (int i = 0; i < eval_num_threads_x; i++) {
            col_threads[i].join();
        }
    }
};

template <class T>
void Eval_Space<T>::eval_index(int row, int col){
    if(col >= num_div_x){return;}
    Soft_Circle<T> *sc, *o_sc;
    Soft_Circle_Link<T> *scl, *o_scl;
    scl = divs[col+row*num_div_x];
    while(scl != nullptr){
        sc = scl->get_soft_circle();
        for(unsigned int o_row = row-1; o_row<=row+1;o_row++){
            if(o_row < 0 || o_row >= num_div_y){continue;};
            for(unsigned int o_col = col -1; o_col <= col+1;o_col++){
                if(o_col < 0 || o_col >= num_div_x){continue;};
                o_scl=divs[o_col+o_row*num_div_x];
                while(o_scl != nullptr){
                    o_sc = o_scl->get_soft_circle();
                    if(o_sc != sc) {sc->include(o_sc);};
                    o_scl = o_scl->get_next();
                }
            }
        }
        scl = scl->get_next();
    }
};

#undef D