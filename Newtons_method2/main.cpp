#include <iostream>
#include <cmath>
#include <stdlib.h>

template<typename T, typename F, typename G, typename E>
void nmethod(T xf, F dxf, G x0, E n){
    std::cout.precision(16);
    if (n <= 0){
        std::cout << "Error: n must be bigger than zero."<<"\n";
    }
    else{
        G x1 = x0;
        do{
            x1 =x0 -xf(x0)/dxf(x0);
            x0=x1;
        }while(abs(xf(x0)/dxf(x0)) > n);
        std::cout << "The solution:" << x1 <<"\n";
    }
}
int main(){
    double x0 = 10.0;
    double n = 0.00001;
    std::cout << "The equation: x*x - 612 = 0"<<"\n";
    std::cout << "First x:" << x0 <<"\n";
    std::cout << "n:" << n <<"\n";
    nmethod([](double x){ return x*x - 612.0; },[](double x){ return 2.0*x; }, x0, n);
    return 0;
}