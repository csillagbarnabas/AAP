#include <iostream>
#include "Matrix.h"
#include <random>
#include <chrono>

auto err = [](auto str){ std::cout << "Time measurement error: " << str << "\n"; std::exit(-1); };

double t_m_p_step(int i){
    std::random_device rd{};
    std::mt19937 gen(rd());
    std::normal_distribution<double> distr(110,25);
    std::vector<double> data(i*i);
    std::generate(data.begin(),
    data.end(),
    [&]{ return distr(gen); });
    std::random_device rd2{};
    std::mt19937 gen2(rd2());
    std::normal_distribution<double> distr2(110,25);
    std::vector<double> data2(i*i);
    std::generate(data2.begin(),
    data2.end(),
    [&]{ return distr2(gen2); });
    Matrix<double> M = {i,data};
    Matrix<double> F = {i,data2};
    auto t0 = std::chrono::high_resolution_clock::now();
    Matrix<double> E = M*F;
    auto t1 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();
}
void time_measurement_sequence(int N, int K, int F){
    if( K < 2)                              { err("low limit.");     }
    if( N == K)                             { err("upper limit.");   }
    if( N < 2)                              { err("upper limit.");   }
    if( F < 1)                              { err("the sampling is too small.");   }
    std::cout << "The measured calculation time of the multiplication of matrices for each size (from " << K << " to "
    << N << "): " << std::endl;
    for(int i = K; i < N; ++i){
        std::vector<double> w{};
        w.resize(F);
        for(int j = 0; j < F; ++j){
            w[j] = t_m_p_step(i);
        }
        std::cout << *min_element(w.begin(), w.end()) << ",";
    }
}
void time_measurs_printer(int N, int K, int F){
    time_measurement_sequence(N,K,F);
    std::cout << " that's all." << std::endl;
}

int main(int, char**) {
    int N = 350;
    int K = 100;
    int F = 30;
    time_measurs_printer(N,K,F);
}