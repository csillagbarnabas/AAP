#include <iostream>
#include <vector>
#include <array>
#include <numeric>


using namespace std;
double sq(double x){
    return x*x;
    }

auto b(vector<double> const& x, vector<double> const& y){
    const int n = static_cast<int>(x.size());
    const auto xv0 = accumulate(x.begin(), x.end(), 0.0);
    const auto yv0 = accumulate(y.begin(), y.end(), 0.0);
    const auto xv = xv0 / n;
    const auto yv = yv0 / n;
    const auto l = [xv](double a,double b){
        return a + sq(b-xv);
    };
    const auto f = [xv,yv](double a,double b){
        return (a-xv)*(b-yv);
    };
    const auto sum = inner_product(x.begin(), x.end(), y.begin(), 0.0, plus<>(), f);
    const auto xsum2 = accumulate(x.begin(), x.end(),0.0, l);
    if (xsum2 == 0.0){
        return  array<double, 2>{0.0,yv};  
    }
    const auto b = sum / xsum2;
    const auto m = yv - b * xv;
    return array<double, 2>{b,m};
}

int main(int, char**) {
    vector<double> A = {1.0,2.0,3.0,4.0};
    vector<double> B = {3.0,5.0,7.0,9.0};
    size_t n = A.size();
    size_t m = B.size();
    if(n == 0.0){
        cout << "Empty vector or vectors!" << endl;
        return 0;
    }
    if(m != n){
        cout << "The size of the vectors are not equal!" << endl;
        return 0;
    }
    const auto p = b(A,B);
    cout << "The steepness of the line: " << p[0] << endl;
    cout << "The y-intercept: " << p[1] << endl;
}
