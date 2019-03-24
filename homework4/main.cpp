#include <iostream>
#include "vector2.h"


template<typename T, typename F>
void comp_sc(T a, F b){
    if (std::abs(a-b) < 1e-14){}
    else{
        std::cout << "The solution is " << a <<", and this isn't correct.It should be" << b <<"." << std::endl;
    }
}
template<typename T, typename F>
void comp_vec(Vector2<T> const& u, Vector2<F> const& v){
    if (std::abs((u-v).x) < 1e-14 && std::abs((u-v).y) < 1e-14){}
    else{
        std::cout << "The solution is (" << u <<"), and this isn't correct. It should be (" << v <<")." << std::endl; 
    }
}
int main(int, char**) {
    Vector2<double> A = {-2.0,5.0};
    Vector2<double> B = {2.0,7.0};
    Vector2<double> C = {3.0,-4.0};
    double g = 2.0;
    std::cout << "A vector:" << A << std::endl;
    std::cout << "B vector:" << B << std::endl;
    std::cout << "C vector:" << C << std::endl;
    std::cout << "g = "<< g << std::endl;
    std::cout << "Test of A+=B." << std::endl;
    comp_vec(A+=B,Vector2<double>{0.0,12.0});
    Vector2<double> A1 = {-2.0,5.0};
    std::cout << "Test of A-=B." << std::endl;
    comp_vec(A1-=B,Vector2<double>{-4.0,-2.0});
    Vector2<double> A2 = {-2.0,5.0};
    std::cout << "Test of A*=g." << std::endl;
    comp_vec(A2*=g,Vector2<double>{-4.0,10.0});
    Vector2<double> A3 = {-2.0,5.0};
    std::cout << "Test of A+C." << std::endl;
    comp_vec(A3+C,Vector2<double>{1.0,1.0});
    std::cout << "Test of C*g." << std::endl;
    comp_vec(C*g,Vector2<double>{6.0,-8.0});
    std::cout << "Test of g*C." << std::endl;
    comp_vec(C*g,Vector2<double>{6.0,-8.0});
    std::cout << "Test of C/g." << std::endl;
    comp_vec(C/g,Vector2<double>{1.5,-2.0});
    std::cout << "Test of A-C." << std::endl;
    comp_vec(A3-C,Vector2<double>{-5.0,9.0});
    std::cout << "Test of length function." << std::endl;
    comp_sc(length(A3),sqrt(29.0));
    std::cout << "Test of sqlength function." << std::endl;
    comp_sc(sqlength(A3),29.0);
    std::cout << "Test of dot function." << std::endl;
    comp_sc(dot(A3,B),31.0);
    std::cout << "Test of normalize function." << std::endl;
    if (length(A3) < 1e-14){
        std::cout << "Error: the length of A is 0." << std::endl;
    }
    else{
        comp_vec(normalize(C),Vector2<double>{3.0/5.0,-4.0/5.0});
    }
}
