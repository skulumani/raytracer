#include "geometry.hpp"

// members for Vec class
template<size_t DIM, typename T>
Vec<DIM, T>::Vec( void ) {
    for (size_t ii=DIM; ii--; _data[ii] = T());
}

template<size_t DIM, typename T>
T& Vec<DIM, T>::operator [] (const size_t ii) {
    assert(ii < DIM);
    return _data[ii];
}

template<size_t DIM, typename T>
const T& Vec<DIM, T>::operator [] (const size_t ii) const {
    assert(ii < DIM);
    return _data[ii];
}

// Vec<2, T> class
/* template<typename T> */
/* Vec<2, T>::Vec( void ) { */
/*     x = T(); */
/*     y = T(); */
/* } */

/* template<typename T> */
/* Vec<2, T>::Vec(T X, T Y) { */
/*     x = X; */
/*     y = Y; */
/* } */

/* template <> class Vec<2, int>; */

