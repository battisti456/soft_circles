#include "soft_circles/eval_space.h"

int main() {
    Eval_Space<float> es = Eval_Space<float>(0,0,1,1);
    es.tick(0.1);
}