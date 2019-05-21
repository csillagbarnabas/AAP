#include <iostream>
#include "Matrix_parallel.h"
#include <random>
#include <chrono>

auto err = [](auto str){ std::cout << "Time measurement error: " << str << "\n"; std::exit(-1); };

auto randomvek = [](int i){
    std::mt19937 gen(42);
    std::normal_distribution<double> distr(0,1);
    return Matrix<double>(Idx1{}, [&](auto){return distr(gen);}, i);

};

double t_m_p_step(int i){
    Matrix<double> M = randomvek(i);
    Matrix<double> F = randomvek(i);
    auto t1 = std::chrono::high_resolution_clock::now();
    Matrix<double> E = M*F;
    auto t2 = std::chrono::high_resolution_clock::now();
    return (static_cast<std::chrono::duration<double, std::milli>>(t2-t1)).count();
}

int main(int, char**) {
    int N =4000;
    std::cout << "The multiplication of two matrices with size of two " << N << "X" << N <<
    " took " << t_m_p_step(N) << " milliseconds." << std::endl;
}