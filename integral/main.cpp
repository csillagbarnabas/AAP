#include <iostream>
#include <math.h>
using namespace std;

double f(double x){
    double gg = pow(cos(x),3);
    return gg;
}

double integrator(double a, double b,int n){
    double h = (b-a)/n;
    double sum = f(a) + f(b);
    int i = 0;
    while(i < n){
        double p = a + i*h;
        sum += 2*f(p);
        i++;
    }
    double eredmeny = h*sum/2;
    return eredmeny;
}

void printelo(double a, double b, int N){
    cout << "a:" << a << endl;
    cout << "b:" << b << endl;
    int i = 1;
    double  n = 0;
    while ( i <= N){
        n = pow(10,i);
        double e = integrator(a,b,n);
        cout << "n : solution" << n << ":" << e << endl;
        i++;
    }
}

int main(){
    std::cout.precision(16);
    double a = -1.0;
    double b = 3.0;
    int N = 7;
    cout << "The function:cos^3(x)" << endl;
    printelo(a,b,N);
    double g = 0.78305;
    cout << "Wolfframalpha:" << g << endl;
    return 0;
}
