#include <iostream>
#include "vector3.h"


template<typename T, typename F, typename G>
void comp_sc(T a, F b, G str){
    if (std::abs(a-b) < 1e-14){}
    else{
        std::cout<< str << std::endl;
        std::cout << "The solution is " << a <<", and this isn't correct.It should be" << b <<"." << std::endl;
    }
}
template<typename T, typename F, typename G>
void comp_vec(Vector3<T> const& u, Vector3<F> const& v, G str){
    if (std::abs((u-v).x) < 1e-14 && std::abs((u-v).y) < 1e-14){}
    else{
        std::cout<< str << std::endl;
        std::cout << "The solution is (" << u <<"), and this isn't correct. It should be (" << v <<")." << std::endl; 
    }
}
int main(int, char**) {
    Vector3<double> A = {-2.0,5.0,3.0};
    Vector3<double> B = {2.0,7.0,-10};
    Vector3<double> C = {3.0,-4.0,5.0};
    double g = 2.0;
    comp_vec(A+=B,Vector3<double>{0.0,12.0,-7.0},"Error in the test of A+=B!");
    Vector3<double> A1 = {-2.0,5.0,3.0};
    comp_vec(A1-=B,Vector3<double>{-4.0,-2.0,13.0},"Error in the test of A-=B!");
    Vector3<double> A2 = {-2.0,5.0,3.0};
    comp_vec(A2*=g,Vector3<double>{-4.0,10.0,6.0},"Error in the test of A*=B!");
    Vector3<double> A3 = {-2.0,5.0,3.0};
    comp_vec(A3+C,Vector3<double>{1.0,1.0,8.0},"Error in the test of A+B!");
    comp_vec(C*g,Vector3<double>{6.0,-8.0,10.0},"Error in the test of C*g!");
    comp_vec(g*C,Vector3<double>{6.0,-8.0,10.0},"Error in the test of g*C!");
    comp_vec(C/g,Vector3<double>{1.5,-2.0,2.5},"Error in the test of C/g!");
    comp_vec(A3-C,Vector3<double>{-5.0,9.0,-2.0},"Error in the test of A-C!");
    comp_sc(length(A3),sqrt(38.0),"Error in the test of length function!");
    comp_sc(sqlength(A3),38.0,"Error in the test of sqlength function!");
    comp_sc(dot(A3,B),1.0,"Error in the test of dot function!");
    if (length(A3) < 1e-14){
        std::cout << "Error: the length of A is 0." << std::endl;
    }
    else{
        comp_vec(normalize(C),Vector3<double>{3.0/sqrt(50.0),-4.0/sqrt(50.0),5.0/sqrt(50.0)},"Error in the test of normalize function!");
    }
}
