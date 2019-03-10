#include <iostream>
#include "geometry.hpp"

int main() {
    

    typedef Vec<2, float> Vec2f;

    Vec2f a(1.0, 2.0);
    std::cout << a[1] << std::endl;
    return 0;
}
