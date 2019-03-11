#include <iostream>
#include <vector>
#include <array>
#include <numeric>

using namespace std;

auto b(vector<double> const& x, vector<double> const& y){
    const int n = static_cast<int>(x.size());
    const auto xv0 = accumulate(x.begin(), x.end(), 0.0);
    const auto yv0 = accumulate(y.begin(), y.end(), 0.0);
    const auto xv = xv0 / n;
    const auto yv = yv0 / n;
    const auto l = [xv](double a,double b){
        const int n = 2;
        return a + pow((b-xv), n);
    };
    auto sum = (x[0] - xv)*(y[0] - yv);
    for (int i = 1; i < n;i++){
        sum += (x[i] - xv)*( y[i] - yv);
    }
    const auto xsum2 = accumulate(x.begin(), x.end(),0.0, l);
    if (xsum2 == 0.0){
        array<double, 2> E = {0.0,yv};
        return E;  
    }
    const auto b = sum / xsum2;
    const auto m = yv - b * xv;
    array<double, 2> E = {b,m};
    return E;
}

int main(int, char**) {
    vector<double> A = {1,2,3,4};
    vector<double> B = {3,5,7,9};
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
