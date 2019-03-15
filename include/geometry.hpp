#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>
#include <cassert>
#include <vector>
#include <iostream>

#include <Eigen/Dense>
#include <Eigen/StdVector>

// create some vector objects
template<size_t DIM, typename T> 
class Vec {

    public:

        Vec( void );
        virtual ~Vec( void ) {}

        T& operator [] (const size_t ii);

        const T& operator [] (const size_t ii) const;

    private:
        T _data[DIM];
};


// typedefs for useful objects
typedef Vec<2, float> Vec2f;
typedef Vec<3, float> Vec3f;
typedef Vec<3, int  > Vec3i;
typedef Vec<4, float> Vec4f;

template <typename T> 
class Vec<2,T> {
    public:
        Vec( void ) : x(T()), y(T()) {}
        /* Vec( void ); */
        Vec(T X, T Y) : x(X), y(Y) {}
    
        virtual ~Vec( void ) {}

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
        T x, y;
};

template <typename T> 
class Vec<3,T> {
    public:
        Vec() : x(T()), y(T()), z(T()) {}
        Vec(T X, T Y, T Z) : x(X), y(Y), z(Z) {}

        T& operator[](const size_t i) {
            assert(i<3);
            return i<=0 ? x : (1==i ? y : z);
        }
        const T& operator[](const size_t i) const {
            assert(i<3);
            return i<=0 ? x : (1==i ? y : z);
        }

        float norm() {
            return std::sqrt(x*x+y*y+z*z); 
        }
        Vec<3,T>& normalize(T l=1) {
            *this = (*this)*(l/norm());
            return *this; 
        }
    private:
        T x,y,z;
};

template <typename T> 
class Vec<4,T> {
    public:
        Vec() : x(T()), y(T()), z(T()), w(T()) {}
        Vec(T X, T Y, T Z, T W) : x(X), y(Y), z(Z), w(W) {}

        T& operator[](const size_t i) {
            assert(i<4);
            return i<=0 ? x : (1==i ? y : (2==i ? z : w));
        }
        const T& operator[](const size_t i) const {
            assert(i<4);
            return i<=0 ? x : (1==i ? y : (2==i ? z : w));
        }
    private:
        T x,y,z,w;
};

template<size_t DIM,typename T>
T operator*(const Vec<DIM,T>& lhs, const Vec<DIM,T>& rhs) {
    T ret = T();
    for (size_t i=DIM; i--; ret+=lhs[i]*rhs[i]);
    return ret;
}

template<size_t DIM,typename T>
Vec<DIM,T> operator+(Vec<DIM,T> lhs, const Vec<DIM,T>& rhs) {
    for (size_t i=DIM; i--; lhs[i]+=rhs[i]);
    return lhs;
}

template<size_t DIM,typename T>
Vec<DIM,T> operator-(Vec<DIM,T> lhs, const Vec<DIM,T>& rhs) {
    for (size_t i=DIM; i--; lhs[i]-=rhs[i]);
    return lhs;
}

// vector * constant
template<size_t DIM,typename T,typename U> 
Vec<DIM,T> operator*(const Vec<DIM,T> &lhs, const U& rhs) {
    Vec<DIM,T> ret;
    for (size_t i=DIM; i--; ret[i]=lhs[i]*rhs);
    return ret;
}

template<size_t DIM, typename T, typename U>
Vec<DIM, T> operator*(const U& lhs, const Vec<DIM, T>& rhs) {
    Vec<DIM, T> ret;
    for (size_t ii=DIM; ii--; ret[ii]=lhs * rhs[ii]);
    return ret;
}

template<size_t DIM,typename T> 
Vec<DIM,T> operator-(const Vec<DIM,T> &lhs) {
    return lhs*T(-1);
}

template <typename T> 
Vec<3,T> cross(Vec<3,T> v1, Vec<3,T> v2) {
    return Vec<3,T>(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}

template <size_t DIM, typename T> 
std::ostream& operator<<(std::ostream& out, const Vec<DIM,T>& v) {
    for(unsigned int i=0; i<DIM; i++) out << v[i] << " " ;
    return out ;
}

struct Material {
    private:
        Eigen::Vector3f diffuse_color;

    public:
        Material( void );
        Material( const Eigen::Ref<const Eigen::Vector3f>& color);
        Material(const float& r_in, const float& g_in, const float& b_in);
        
        Eigen::Vector3f get_diffuse( void );
};

// sphere class
class Sphere {
    private:
        Eigen::Vector3f center;
        float radius;
        Material material;

    public:
        
        Sphere( void );
        Sphere(const float& xc_in, const float& yc_in, const float& zc_in, const float& r_in);
        Sphere(const float& xc_in, const float& yc_in, const float& zc_in, const float& r_in,
                const Material& m_in);
        Sphere(const Eigen::Ref<const Eigen::Vector3f>& center_in, const float& radius_in);
        Sphere(const Eigen::Ref<const Eigen::Vector3f>& center_in, const float& radius_in, 
                const Material& m_in);
        virtual ~Sphere( void ) {};

        Material get_material( void ) const;

        bool ray_intersect(const Eigen::Vector3f& origin,
                           const Eigen::Vector3f& view_direction,
                           float& t0) const;
};

Eigen::Vector3f cast_ray(const Eigen::Ref<const Eigen::Vector3f>& orig,
        const Eigen::Ref<const Eigen::Vector3f>& dir,
        const Sphere& sphere);

Eigen::Vector3f cast_ray(const Eigen::Ref<const Eigen::Vector3f>& orig,
        const Eigen::Ref<const Eigen::Vector3f>& dir,
        const std::vector<Sphere>& spheres);

#endif
