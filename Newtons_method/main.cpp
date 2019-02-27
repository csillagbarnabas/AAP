#include <iostream>
#include <math.h>
#include <stdlib.h>
double xf(double x){
    return exp(x)-x-3;
    }

double dxf(double x){
     return exp(x)-1;
     }

void nmethod(double x0, double n){
    std::cout.precision(16);
    double x1;
    do{
        x1 =x0 -xf(x0)/dxf(x0);
        x0=x1;
    }while(abs(x1-x0) > n);
    std::cout << "The solution:" << x1 <<"\n";
}
int main(){
    double x0 = 2.0;
    double n = 0.00001;
    std::cout << "The equation: exp(x)-x-3=0"<<"\n";
    std::cout << "First x:" << x0 <<"\n";
    nmethod(x0,n);
    return 0;
}
