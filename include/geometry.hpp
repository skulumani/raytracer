#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>
#include <cassert>
#include <vector>
#include <iostream>

// create some vector objects
template<size_t DIM, typename T> 
class vec {

    public:

        vec( void );
        virtual ~vec( void );
   
        T& operator [] (const size_t ii);
        const T& operator [] (const size_t ii) const;

    private:
        T _data[DIM];
};

template <typename T> 
class vec<2,T> {
    public:
    vec( void );
    /* vec(T X, T Y) : x(X), y(Y) {} */
    vec(T X, T Y);
    
    virtual ~vec( void );

    template <class U> 
    vec<2,T>(const vec<2,U> &v);

          T& operator[](const size_t i)       { assert(i<2); return i<=0 ? x : y; }
    const T& operator[](const size_t i) const { assert(i<2); return i<=0 ? x : y; }
    T x,y;
};

#endif
