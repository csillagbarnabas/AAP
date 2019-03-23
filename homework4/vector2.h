#include <cmath>
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
std::ostream& operator<<( std::ostream& o, Vector2<T> const& v )
{
o << v.x << " " << v.y;
return o;
}
template<typename T>
std::istream& operator>>( std::istream& i, Vector2<T> const& v )
{
i >> v.x;
i >> v.y;
return i;
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
