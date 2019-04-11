#include <iostream>
#include "Matrix.h"
#include <random>
#include <chrono>
#include <fstream>

auto err = [](auto str){ std::cout << "Time measurement error: " << str << "\n"; std::exit(-1); };
auto randomvek = [](int i){
    std::mt19937 gen(42);
    std::normal_distribution<double> distr(0,1);
    std::vector<double> data(i*i);
    std::generate(data.begin(),
    data.end(),
    [&]{ return distr(gen); });
    return data;

};

double t_m_p_step(int i){
    std::vector<double>data = randomvek(i);
    std::vector<double>data2 = randomvek(i);
    Matrix<double> M = {i,data};
    Matrix<double> F = {i,data2};
    auto t0 = std::chrono::high_resolution_clock::now();
    Matrix<double> E = M*F;
    auto t1 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();
}
void time_measurement_sequence(int N, int K, int F, std::ofstream ofile){
    if( K < 2)                              { err("low limit.");     }
    if( N == K)                             { err("upper limit.");   }
    if( N < 2)                              { err("upper limit.");   }
    if( F < 1)                              { err("the sampling is too small.");   }
    for(int i = K; i < N; ++i){
        std::vector<double> w{};
        w.resize(F);
        for(int j = 0; j < F; ++j){
            w[j] = t_m_p_step(i);
        }
        ofile << *min_element(w.begin(), w.end()) << ",";
    }
}

int main(int, char**) {
    auto t0 = std::chrono::high_resolution_clock::now();
    int N = 700;
    int K = 600;
    int F = 10;
    std::ofstream ofile("data6.txt");
    if(ofile.is_open()){
        if( K < 2)                              { err("low limit.");     }
        if( N == K)                             { err("upper limit.");   }
        if( N < 2)                              { err("upper limit.");   }
        if( F < 1)                              { err("the sampling is too small.");   }
        for(int i = K; i < N; ++i){
            std::vector<double> w{};
            w.resize(F);
            for(int j = 0; j < F; ++j){
                w[j] = t_m_p_step(i);
            }
        ofile << *min_element(w.begin(), w.end()) << ",";
        }
    ofile.close();
    }
    else{
        std::cout << "Unable to open file" << std::endl;
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << "It's all took " << std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count() << " miliseconds." << std::endl;
}
