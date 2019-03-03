#include <iostream>
#include <cmath>

template<typename T, typename F, typename G, typename E>
void nmethod(T xf, F dxf, G x0, E n){
    std::cout.precision(16);
    G dx = -xf(x0)/dxf(x0);
    do{
        x0 += dx;
        dx = -xf(x0)/dxf(x0);
    }while(std::abs(dx) > n);
    std::cout << "The solution:" << x0 <<"\n";
}
int main(){
    double x0 = 10.0;
    double n = - 0.00001;
    std::cout << "The equation: x*x - 612 = 0"<<"\n";
    std::cout << "First x:" << x0 <<"\n";
    std::cout << "n:" << n <<"\n";
    std::cout << "Wolframalpha: +/- 24.7386337537060"<<"\n";
    if (n <= 0){
        std::cout << "Error: n must be bigger than zero. So now we are going to use the absulute value of n."<<"\n";
        double n1 = std::abs(n);
        nmethod([](double x){ return x*x - 612.0; },[](double x){ return 2.0*x; }, x0, n1);
        return 0;

    }
    nmethod([](double x){ return x*x - 612.0; },[](double x){ return 2.0*x; }, x0, n);
    return 0;
}
