#include <iostream>
#include "vector2.h"
#include <cmath>

using namespace std;

template<typename T>
T sq(T x){
    return x*x;
}

template<typename T, typename F>
T dot(Vector2<T> const& u, Vector2<F> const& v){
    return u.x * v.x + u.y * v.y;
}
template<typename T>
T length(Vector2<T> const& v){
    return sqrt(sq(v.x)+sq(v.y));
}

template<typename T>
T sqlength(Vector2<T> const& v){
    return sq(v.x)+sq(v.y);
}
template<typename T, typename F>
void comp_sc(T a, F b){
    if (abs(a-b) < pow(10,-14)){
        cout << "The solution is " << a << ", and this is correct." << endl;
    }
    else{
        cout << "The solution is " << a <<", and this isn't correct." << endl;
    }
}
template<typename T, typename F>
void comp_vec(Vector2<T> const& u, Vector2<F> const& v){
    if (abs((u-v).x) < pow(10,-14) && abs((u-v).y) < pow(10,-14)){
        cout << "The solution is (" << u << "), and this is correct." << endl;
    }
    else{
        cout << "The solution is (" << u <<"), and this isn't correct." << endl; 
    }
}
template<typename T>
Vector2<T> normalize(Vector2<T> const& v){
    T a = length(v);
    return Vector2<T>{v.x/a,v.y/a};
}
int main(int, char**) {
    Vector2<double> A = {-2.0,5.0};
    Vector2<double> B = {2.0,7.0};
    Vector2<double> C = {3.0,-4.0};
    double g = 2.0;
    cout << "A vector:" << A << endl;
    cout << "B vector:" << B << endl;
    cout << "C vector:" << C << endl;
    cout << "g = "<< g << endl;
    cout << "Test of A+=B:" << endl;
    comp_vec(A+=B,Vector2<double>{0.0,12.0});
    Vector2<double> A1 = {-2.0,5.0};
    cout << "Test of A-=B:" << endl;
    comp_vec(A1-=B,Vector2<double>{-4.0,-2.0});
    Vector2<double> A2 = {-2.0,5.0};
    cout << "Test of A*=g:" << endl;
    comp_vec(A2*=g,Vector2<double>{-4.0,10.0});
    Vector2<double> A3 = {-2.0,5.0};
    cout << "Test of A+C:" << endl;
    comp_vec(A3+C,Vector2<double>{1.0,1.0});
    cout << "Test of C*g:" << endl;
    comp_vec(C*g,Vector2<double>{6.0,-8.0});
    cout << "Test of g*C:" << endl;
    comp_vec(C*g,Vector2<double>{6.0,-8.0});
    cout << "Test of C/g:" << endl;
    comp_vec(C/g,Vector2<double>{1.5,-2.0});
    cout << "Test of A-C:" << endl;
    comp_vec(A3-C,Vector2<double>{-5.0,9.0});
    cout << "Test of length function. Length of A:" << endl;
    comp_sc(length(A3),sqrt(29.0));
    cout << "Test of sqlength function:" << endl;
    comp_sc(sqlength(A3),29.0);
    cout << "Test of dot function:" << endl;
    comp_sc(dot(A3,B),31.0);
    cout << "Test of normalize function:" << endl;
    comp_vec(normalize(C),Vector2<double>{3.0/5.0,-4.0/5.0});
}
