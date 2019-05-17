#include <iostream>
#include <random>
#include <array>
#include <execution>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <chrono>
#include <fstream>

template<typename T>
T sq(T a){
    return a*a;
}

auto err = [](auto str){ std::cout << "Time measurement error: " << str << "\n"; std::exit(-1); };

auto lregression(std::vector<double> const& x, std::vector<double> const& y){
    const int n = static_cast<int>(x.size());
    const auto xv0 = std::accumulate(x.begin(), x.end(), 0.0);
    const auto yv0 = std::accumulate(y.begin(), y.end(), 0.0);
    const auto xv = xv0 / n;
    const auto yv = yv0 / n;
    const auto l = [xv](double a,double b){
        return a + sq(b-xv);
    };
    const auto g = [xv,yv](double a,double b){
        return (a-xv) * (b-yv);
    };
    const auto sum = std::inner_product(x.begin(), x.end(), y.begin(), 0.0, std::plus<>(), g);
    const auto xsum2 = std::accumulate(x.begin(), x.end(),0.0, l);
    if (xsum2 == 0.0){
        return std::array<double, 2> {0.0,yv};
    }
    const auto m = sum / xsum2;
    const auto b = yv - m * xv;
    return std::array<double, 2> {b,m};
}
auto par_regression(std::vector<double> const& x, std::vector<double> const& y){
    const int n = static_cast<int>(x.size());
    auto add = [](auto const& x, auto const& y){ return x + y; };
    auto division = [n](auto x){ return x/n; };
    auto nothing = [](auto x){ return x; };
    auto policy = std::execution::par;
    const auto xv=std::transform_reduce(policy, x.begin(), x.end(), 0.0, add,division);
    const auto yv=std::transform_reduce(policy, y.begin(), y.end(), 0.0, add,division);
    const auto l = [xv](double a,double b){
        return a + sq(b-xv);
    };
    const auto g = [xv,yv](double a,double b){
        return (a-xv) * (b-yv);
    };
    const auto sum = std::transform_reduce(policy,x.begin(), x.end(), y.begin(),0.0,std::plus<>(),g);
    const auto xsum2 = std::transform_reduce(policy, x.begin(), x.end(), 0.0, l,nothing);
    if (xsum2 == 0.0){
        return std::array<double, 2> {0.0,yv};
    }
    const auto m = sum / xsum2;
    const auto b = yv - m * xv;
    return std::array<double, 2> {b,m};
}
double t_m_lp_step(int j){
    double m0 = 0.0560, b0 = -4.20, sigma = 0.3140;
    std::mt19937 gen(42);
    std::vector<double> x(10000*j);
    std::vector<double> y(10000*j);
    for(int i=0; i<10000*j; ++i){
        std::normal_distribution<double> distr(m0*i*0.001+b0,sigma);
        x[i] = i*0.001;
        y[i] = distr(gen);
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    const auto p = par_regression(x,y);
    auto t2 = std::chrono::high_resolution_clock::now();
    return (static_cast<std::chrono::duration<double, std::micro>>(t2-t1)).count();
}
double t_m_l_step(int j){
    double m0 = 0.0560, b0 = -4.20, sigma = 0.3140;
    std::mt19937 gen(42);
    std::vector<double> x(10000*j);
    std::vector<double> y(10000*j);
    for(int i=0; i<10000*j; ++i){
        std::normal_distribution<double> distr(m0*i*0.001+b0,sigma);
        x[i] = i*0.001;
        y[i] = distr(gen);
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    const auto p = lregression(x,y);
    auto t2 = std::chrono::high_resolution_clock::now();
    return (static_cast<std::chrono::duration<double, std::micro>>(t2-t1)).count();
}
auto t_m_l_step_test(int j){
    double m0 = 0.0560, b0 = -4.20, sigma = 0.3140;
    std::mt19937 gen(42);
    std::vector<double> x(10000*j);
    std::vector<double> y(10000*j);
    for(int i=0; i<10000*j; ++i){
        std::normal_distribution<double> distr(m0*i*0.001+b0,sigma);
        x[i] = i*0.001;
        y[i] = distr(gen);
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    const auto p = lregression(x,y);
    auto t2 = std::chrono::high_resolution_clock::now();
    return p;
}
auto t_m_lp_step_test(int j){
    double m0 = 0.0560, b0 = -4.20, sigma = 0.3140;
    std::mt19937 gen(42);
    std::vector<double> x(10000*j);
    std::vector<double> y(10000*j);
    for(int i=0; i<10000*j; ++i){
        std::normal_distribution<double> distr(m0*i*0.001+b0,sigma);
        x[i] = i*0.001;
        y[i] = distr(gen);
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    const auto p = par_regression(x,y);
    auto t2 = std::chrono::high_resolution_clock::now();
    return p;
}
void time_measurement_sequence(int const& M, int const& F, std::ofstream& ofile1,std::ofstream& ofile2){
    if( M < 2)                              { err("upper limit.");   }
    if( F < 1)                              { err("the sampling is too small.");   }
    for(int i = 1; i < M; ++i){
        std::vector<double> w(F);
        for(int j = 0; j < F; ++j){
            w[j] = t_m_l_step(i);
        }
        ofile1 << *min_element(w.begin(), w.end()) << ",";
    }
    for(int i = 1; i < M; ++i){
        std::vector<double> w(F);
        for(int j = 0; j < F; ++j){
            w[j] = t_m_lp_step(i);
        }
        ofile2 << *min_element(w.begin(), w.end()) << ",";
    }
}
int main(){
    int M = 100;
    int F = 10;
    double ml = t_m_l_step_test(M)[1];
    double bl = t_m_l_step_test(M)[0];
    if(std::fabs(bl +4.2) > 10.0){
        std::cout << "The difference between the bl-s more than 0.1!" << std::endl;
        std::cout << ml << std::endl;
        exit(-1);
    }
    if(std::fabs(ml - 0.0560) > 0.1){
        std::cout << "The difference between the ml-s more than 0.01!" << std::endl;
        std::cout << ml << std::endl;
        exit(-1);
    }
    double mlp = t_m_lp_step_test(M)[1];
    double blp = t_m_lp_step_test(M)[0];
    if(std::fabs(blp +4.2) > 10.0){
        std::cout << "The difference between the bl-s more than 0.1!" << std::endl;
        std::cout << mlp << std::endl;
    }
    if(std::fabs(mlp - 0.0560) > 0.1){
        std::cout << "The difference between the ml-s more than 0.01!" << std::endl;
        std::cout << mlp << std::endl;
    }
    std::ofstream ofile1("simple.txt");
    if(ofile1.is_open()){
        std::ofstream ofile2("parallel.txt");
        if(ofile2.is_open()){
            time_measurement_sequence(M,F,ofile1,ofile2);
        ofile2.close();
        }
        else{
            std::cout << "Unable to open file" << std::endl;
        }
    ofile1.close();
    }
    else{
        std::cout << "Unable to open file" << std::endl;
    }
}
