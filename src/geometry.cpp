#include "geometry.hpp"

// members for Vec class
template<size_t DIM, typename T>
Vec<DIM, T>::Vec( void ) {
    for (size_t ii=DIM; ii--; _data[ii] = T());
}
