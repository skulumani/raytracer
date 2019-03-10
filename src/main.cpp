#include "geometry.hpp"

int main() {
    
    Eigen::Matrix<double, 1, 2> a;
    a << 1, 2;
    std::cout << a(1) << std::endl;
    return 0;
}
