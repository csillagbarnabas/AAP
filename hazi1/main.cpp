#include <iostream>
#include <math.h>

using namespace std;

void solve(double a, double b, double c){
    double s = b*b-4*a*c;
    if ( s < 0.0 ){
        std::cout << "No solution. The discriminant is negative.\n" ;
        return;
    }
    if ( s != 0.0 ){
        double sq1 = (-b + sqrt(s))/(2*a);
        double sq2 = (-b - sqrt(s))/(2*a);
        std::cout << "The first solution:" << sq1 << "\n" ;
        std::cout << "The second solution:" << sq2 << "\n" ;
    }
    if ( s == 0.0 ){
        double sq = -b / (2*a);
        std::cout << "The solution:" << sq << "\n" ;
    }
}
int main(int, char**) {
    double a = 1.0;
    double b = 2.0;
    double c = 1.0;
    solve(a,b,c);
}
