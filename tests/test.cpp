#include <vector>
#include <iostream>

int main(){
    std::vector<int> vec = {1,2,3,4,5,6};
    int& val = vec[2];
    vec.erase(vec.begin());
    val += 10;
    for(int num : vec){
        std::cout << num << ',';
    }
    return 0;
}