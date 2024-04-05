#include "../my_array.h"

using namespace my_containers;

int main() {
    MyArray<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(99);
    if(a.size() != 3) return 1;
    if(a[2] != 99) return 1;
    
    return 0;
}