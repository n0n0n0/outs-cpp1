#include "../my_array.h"

using namespace my_containers;

int main() {
    MyArray<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    return !(a.size() == 3);
}