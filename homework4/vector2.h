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
};
template<typename T>
Vector2<T> operator+( Vector2<T> const& a, Vector2<T> const& b ){
    return Vector2<T>{ a.x + b.x, a.y + b.y };
}
template<typename T>
Vector2<T> operator*( Vector2<T> const& a, T const& b ){
    return Vector2<T>{ b*a.x, b*a.y };
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