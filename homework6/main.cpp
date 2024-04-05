#include <iostream>
#include "my_array.h"

using namespace std;
using namespace my_containers;

ostream& operator<<(ostream& os, const MyArray<int> &a) {
    os << "MyArray: ";
    for(size_t i = 0; i < a.size(); i++) {
        os << a[i] << " ";
    }
    os << std::endl;

    return os;
}

int main(int argc, char* argv[])
{
    cout << "Hello hw6! \n";

    MyArray<int> a;
    a.push_back(1);
    a.push_back(3);
    a.push_back(5);
    a.push_back(8);
    a.push_back(9);
    a.push_back(12);

    std::cout << a;
    std::cout << "count: " << a.size() << "\n";

    a.insert(22, 2);

    std::cout << a;
    std::cout << "count: " << a.size() << "\n";

    a.insert(0, 0);

    std::cout << a;
    std::cout << "count: " << a.size() << "\n";

    a.erase(2, 2);

    std::cout << a;
    std::cout << "count: " << a.size() << "\n";

    std::cout << "a[3]: " << a[3] << "\n";

    a.erase(3, 10);
    std::cout << a;
    std::cout << "count: " << a.size() << "\n";

    a.erase(4, 4);
    std::cout << a;
    std::cout << "count: " << a.size() << "\n";

    return 0;
}