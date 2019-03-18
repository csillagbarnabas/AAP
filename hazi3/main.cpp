#include <iostream>
#include <vector>
#include <array>
#include <numeric>

using namespace std;

template<typename T>
T sq(T a){
    return a*a;
}

auto lregression(vector<double> const& x, vector<double> const& y){
    const int n = static_cast<int>(x.size());
    const auto xv0 = accumulate(x.begin(), x.end(), 0.0);
    const auto yv0 = accumulate(y.begin(), y.end(), 0.0);
    const auto xv = xv0 / n;
    const auto yv = yv0 / n;
    const auto l = [xv](double a,double b){
        return a + sq(b-xv);
    };
    const auto g = [xv,yv](double a,double b){
        return (a-xv) * (b-yv);
    };
    const auto sum = inner_product(x.begin(), x.end(), y.begin(), 0.0, plus<>(), g);
    const auto xsum2 = accumulate(x.begin(), x.end(),0.0, l);
    if (xsum2 == 0.0){
        return array<double, 2> {0.0,yv};
    }
    const auto b = sum / xsum2;
    const auto m = yv - b * xv;
    return array<double, 2> {b,m};
}

int main(int, char**) {
    cout << "First test:" << endl;
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
    const auto p = lregression(A,B);
    cout << "The steepness of the line: " << p[0] << endl;
    cout << "The y-intercept: " << p[1] << endl;
    cout << "Second test:" << endl;
    vector<double> x = {-10,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10};
    vector<double> y = {56.22, 53.46, 52.08, 50.7 , 49.32, 47.94, 46.56, 45.18, 43.8 ,42.42, 41.04, 39.66, 38.28, 36.9 , 35.52, 34.14, 32.76, 31.38, 30.0  , 28.62};
    size_t k = x.size();
    size_t j = y.size();
    if(k == 0.0){
        cout << "Empty vector or vectors!" << endl;
        return 0;
    }
    if(j != k){
        cout << "The size of the vectors are not equal!" << endl;
        return 0;
    }
    const auto q = lregression(x,y);
    cout << "The steepness of the line: " << q[0] << ", With Python3:" << -1.38 << endl;
    cout << "The y-intercept: " << q[1] << ", With Python3:" << 42.42 << endl;
}
