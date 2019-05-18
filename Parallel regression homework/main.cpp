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
#include <string>

template<typename T>
T sq(T a){
    return a*a;
}
auto err = [](auto str){ std::cout << "Measurement error: " << str << std::endl; std::exit(-1); };
auto lregression(std::vector<double> const& x, std::vector<double> const& y){
    const int n = static_cast<int>(x.size());
    auto division = [n](auto x){ return x/n; };
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
template<typename M, typename G, typename L,typename N>
auto t_m_step(int const& j,M const& m0,L const& b0,N const& sigma, G & gen,int S){
    std::vector<double> x(40000*j);
    std::vector<double> y(40000*j);
    for(int i=0; i<40000*j; ++i){
        std::normal_distribution<double> distr(m0*i*0.001+b0,sigma);
        x[i] = i*0.001;
        y[i] = distr(gen);
    }
    std::chrono::steady_clock::time_point t1;
    std::chrono::steady_clock::time_point t2;
    std::array<double, 2> p;
    t1 = std::chrono::high_resolution_clock::now();
    if(S == 0){
        t1 = std::chrono::high_resolution_clock::now();
        p = lregression(x,y);
        t2 = std::chrono::high_resolution_clock::now();
    }
    if(S == 1){
        t1 = std::chrono::high_resolution_clock::now();
        p = par_regression(x,y);
        t2 = std::chrono::high_resolution_clock::now();
    }
    std::array<double, 3> Pt;
    Pt[0] = p[0];
    Pt[1] = p[1];
    Pt[2] = (static_cast<std::chrono::duration<double, std::micro>>(t2-t1)).count();
    return Pt;
}
template<typename T, typename G, typename L,typename N>
void time_measurement_sequence(int const& M, int const& F, std::ofstream& ofile1,std::ofstream& ofile2,
std::ofstream& ofile3,std::ofstream& ofile4,T const& m0,L const& b0,N const& sigma, G & gen){
    if( M < 2)                              { err("upper limit.");   }
    if( F < 1)                              { err("the sampling is too small.");   }
    std::vector<double> w3(F);
    for(int i = 1; i < M+1; ++i){
        for(int j = 0; j < F; ++j){
            const auto pt = t_m_step(i,m0,b0,sigma,gen,0);
            w3[j] = pt[2];
            ofile3 << pt[0] << std::endl;
            ofile3 << pt[1] << std::endl;
        }
        ofile1 << *min_element(w3.begin(), w3.end()) << ",";
    }
    for(int i = 1; i < M+1; ++i){
        for(int j = 0; j < F; ++j){
            const auto pt = t_m_step(i,m0,b0,sigma,gen,1);
            w3[j] = pt[2];
            ofile4 << pt[0] << std::endl;
            ofile4 << pt[1] << std::endl;
        }
        ofile2 << *min_element(w3.begin(), w3.end()) << ",";
    }
}
int main(){
    double m0 = 0.0560, b0 = -4.20, sigma = 0.03140;
    std::mt19937 gen(42);
    int M = 2;
    int F = 10;
    double bt = 1.0;
    double mt = 0.0560;
    std::array<double, 3> Pl = t_m_step(M,m0,b0,sigma,gen,0);
    std::array<double, 3> Plp = t_m_step(M,m0,b0,sigma,gen,1);
    if(std::fabs(Pl[0] -b0) > bt){ err("bl");}
    if(std::fabs(Pl[1] -m0) > mt){ err("ml");}
    if(std::fabs(Plp[0] -b0) > bt){ err("blp");}
    if(std::fabs(Plp[1] -m0) > mt){ err("mlp");}
    std::ofstream ofile1("simple.txt");
    if(ofile1.is_open()){
        std::ofstream ofile2("parallel.txt");
        if(ofile2.is_open()){
            std::ofstream ofile3("simple_solutions.txt");
            if(ofile3.is_open()){
                 std::ofstream ofile4("parallel_solutions.txt");
                if(ofile4.is_open()){
                    time_measurement_sequence(M,F,ofile1,ofile2,ofile3,ofile4,m0,b0,sigma,gen);
                    ofile4.close();
                }
                else{
                    std::cout << "Unable to open file" << std::endl;
                }
                ofile3.close();
            }
            else{
                std::cout << "Unable to open file" << std::endl;
            }
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
