#include <cmath>
#include <ostream>
#include <istream>
#include <sstream>
template<typename T>
struct Vector3{
    T x, y, z;
    Vector3<T>& operator+=( Vector3<T> const& v ){
        x += v.x; y += v.y; z +=v.z;
    return *this;
    }
    Vector3<T>& operator-=( Vector3<T> const& v ){
        x -= v.x; y -= v.y;  z -=v.z;
    return *this;
    }
    Vector3<T>& operator*=( T const& v ){
        x = x*v; y = y*v;  z =z * v;
    return *this;
    }
    Vector3<T>& operator/=( T const& v ){
        x = x/v; y = y/v;   z =z / v;
    return *this;
    }
};
template<typename T>
Vector3<T> operator+( Vector3<T> const& a, Vector3<T> const& b ){
    return Vector3<T>{ a.x + b.x, a.y + b.y, a.z + b.z };
}
template<typename T>
Vector3<T> operator*( Vector3<T> const& a, T const& b ){
    return Vector3<T>{ a.x *b, a.y*b, a.z * b };
}
template<typename T>
Vector3<T> operator*( T const& b, Vector3<T> const& a){
    return Vector3<T>{ b*a.x, b*a.y, b*a.z };
}
template<typename T>
Vector3<T> operator/( Vector3<T> const& a, T const& b ){
    return Vector3<T>{ a.x/b, a.y / b, a.z/b };
}
template<typename T>
Vector3<T> operator-( Vector3<T> const& a, Vector3<T> const& b ){
    return Vector3<T>{ a.x - b.x, a.y - b.y, a.z - b.z };
}
template<typename T>
T sq(T x){
    return x*x;
}
template<typename T, typename F>
T dot(Vector3<T> const& u, Vector3<F> const& v){
    return u.x * v.x + u.y * v.y + u.z * v.z;
}
template<typename T>
T sqlength(Vector3<T> const& v){
    return sq(v.x)+sq(v.y)+sq(v.z);
}
template<typename T>
T length(Vector3<T> const& v){
    return std::sqrt(sqlength(v));
}
template<typename T>
Vector3<T> normalize(Vector3<T> const& v){
    return v/length(v);
}
template<typename T>
std::ostream& operator<<( std::ostream& o, Vector3<T> const& v )
{
    o << v.x << ", " << v.y << ", " << v.z << std::endl;
    return o;
}
std::istream& operator>>( std::istream& i, Vector3<int>& v )
{
    std::string tmp;
    std::getline(i, tmp);
    if(tmp.size() > 0){
        std::stringstream ss(tmp);
        std::getline(ss, tmp, ',');
        v.x = std::stoi(tmp);
        std::getline(ss, tmp, ',');
        v.y = std::stoi(tmp);
        std::getline(ss, tmp, ',');
        v.z = std::stoi(tmp);
    }
    return i;
}
std::istream& operator>>( std::istream& i, Vector3<double>& v )
{
    std::string tmp;
    std::getline(i, tmp);
    if(tmp.size() > 0){
        std::stringstream ss(tmp);
        std::getline(ss, tmp, ',');
        v.x = std::stod(tmp);
        std::getline(ss, tmp, ',');
        v.y = std::stod(tmp);
        std::getline(ss, tmp, ',');
        v.z = std::stod(tmp);
    }
    return i;
}