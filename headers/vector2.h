#include <cmath>
#include <ostream>
#include <istream>
#include <sstream>
template<typename T>
struct Vector2{
    T x, y;
    Vector2<T>& operator+=( Vector2<T> const& v ){
        x += v.x; y += v.y;
    return *this;
    }
    Vector2<T>& operator-=( Vector2<T> const& v ){
        x -= v.x; y -= v.y;
    return *this;
    }
    Vector2<T>& operator*=( T const& v ){
        x = x*v; y = y*v;
    return *this;
    }
    Vector2<T>& operator/=( T const& v ){
        x = x/v; y = y/v;
    return *this;
    }
};
template<typename T>
Vector2<T> operator+( Vector2<T> const& a, Vector2<T> const& b ){
    return Vector2<T>{ a.x + b.x, a.y + b.y };
}
template<typename T>
Vector2<T> operator*( Vector2<T> const& a, T const& b ){
    return Vector2<T>{ a.x *b, a.y*b };
}
template<typename T>
Vector2<T> operator*( T const& b, Vector2<T> const& a){
    return Vector2<T>{ b*a.x, b*a.y };
}
template<typename T>
Vector2<T> operator/( Vector2<T> const& a, T const& b ){
    return Vector2<T>{ a.x/b, a.y / b };
}
template<typename T>
Vector2<T> operator-( Vector2<T> const& a, Vector2<T> const& b ){
    return Vector2<T>{ a.x - b.x, a.y - b.y };
}
template<typename T>
T sq(T x){
    return x*x;
}
template<typename T, typename F>
T dot(Vector2<T> const& u, Vector2<F> const& v){
    return u.x * v.x + u.y * v.y;
}
template<typename T>
T sqlength(Vector2<T> const& v){
    return sq(v.x)+sq(v.y);
}
template<typename T>
T length(Vector2<T> const& v){
    return std::sqrt(sqlength(v));
}
template<typename T>
Vector2<T> normalize(Vector2<T> const& v){
    return v/length(v);
}
template<typename T>
std::ostream& operator<<( std::ostream& o, Vector2<T> const& v )
{
    o << v.x << "," << v.y << std::endl;
    return o;
}
std::istream& operator>>( std::istream& i, Vector2<int>& v )
{
    std::string tmp;
    std::getline(i, tmp);
    if(tmp.size() > 0){
        std::stringstream ss(tmp);
        std::getline(ss, tmp, ',');
        v.x = std::stoi(tmp);
        std::getline(ss, tmp, ',');
        v.y = std::stoi(tmp);

    }
    return i;
}
std::istream& operator>>( std::istream& i, Vector2<double>& v )
{
    std::string tmp;
    std::getline(i, tmp);
    if(tmp.size() > 0){
        std::stringstream ss(tmp);
        std::getline(ss, tmp, ',');
        v.x = std::stod(tmp);
        std::getline(ss, tmp, ',');
        v.y = std::stod(tmp);

    }
    return i;
}