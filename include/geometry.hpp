#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>
#include <cassert>
#include <vector>
#include <iostream>

// create some vector objects
template<size_t DIM, typename T> 
class Vec {

    public:

        Vec( void ) {
            for (size_t ii=DIM; ii--; _data[ii] = T());
        }
   
        T& operator [] (const size_t ii) {
            assert(ii < DIM);
            return _data[ii];
        };

        const T& operator [] (const size_t ii) const {
            assert(ii < DIM);
            return _data[ii];
        }

    private:
        T _data[DIM];
};

template <typename T> 
class Vec<2,T> {
    public:
        Vec( void ) : x(T()), y(T()) {}
        Vec(T X, T Y) : x(X), y(Y) {}

        template <class U> 
            Vec<2,T>(const Vec<2,U> &v);

        T& operator[](const size_t i) {
            assert(i<2); 
            return i<=0 ? x : y; 
        }

        const T& operator[](const size_t i) const {
            assert(i<2); 
            return i<=0 ? x : y; 
        }

    private:
        T x,y;
};

#endif
