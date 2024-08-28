class A{
    public:
    void do_something0(int val);
    void do_something1(double val);
    void do_something2(char val);
    void do_something3(char* val);
}

template <class T, void (A::*do_)(T)>
void A_do_something(A* self, T val){
    self->*do_(val);
}

template <void (A::*do_)(int)>
void A_do_something<int,do_>(A* self, int val){
    //some other steps for this case
    self->*do_(val);
}

int main() {
    A a;
    A_do_something<&A::do_something0>(5);
}