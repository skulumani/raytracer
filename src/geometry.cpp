#include "geometry.hpp"

template<size_t DIM, typename T> 
vec<DIM, T>::vec() {
    for (size_t ii=DIM; ii--; _data[ii] = T());
}

template<size_t DIM, typename T>
T& vec<DIM, T>::operator[] (const size_t ii) {
    assert(ii < DIM);
    return _data[ii];
}

template<size_t DIM, typename T>
const T& vec<DIM, T>::operator [] (const size_t ii) const {
    assert(ii < DIM);
    return _data[ii];
}

template<typename T>
vec<2, T>::vec( void ) {
    x = T();
    y = T();
}

template <typename T>
vec<2, T>::vec( T x_in, T y_in) {
    x = x_in;
    y = y_in;
}

// template specialization
template <> vec<2, float>::vec( void );
template <> vec<2, float>::vec(float x_in, float y_in);
