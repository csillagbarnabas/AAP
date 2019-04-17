#include <iostream>
#include "Matrix.h"
#include "vector2.h"
#include <fstream>
#include <vector>
#include <numeric>


int main(int, char**) {
    Matrix<double> M{3,{1.23,4.56,3.14,-4.23,9.87,-6.54,3.21,0.19,2.93}};
    std::ofstream ofile2("data2.txt");
    if(ofile2.is_open()){
        ofile2 << M;
    ofile2.close();
    }
    std::vector<double> v(9);
    Matrix<double> A(3,v);
    std::ifstream ofile("data.txt");
    if(ofile.is_open()){
        ofile >> A;
    ofile.close();
    }
    Vector2<double>v1;
    Vector2<double>v2 = {1.3,-7.4};
    std::ifstream vfile("vdat1.txt");
    if(vfile.is_open()){
        vfile >> v1;
    vfile.close();
    }
    std::ofstream vfile2("vdat2.txt");
    if(vfile2.is_open()){
        vfile2 << v2;
    vfile2.close();
    }
    std::cout << "The read vector: " << std::endl;
    std::cout << v1 << std::endl;
    std::cout << "The writed vector: " << std::endl;
    std::cout << v2 << std::endl;
    std::cout << "The read matrix: " << std::endl;
    std::cout << A << std::endl;
    std::cout << "The writed matrix: " << std::endl;
    std::cout << M << std::endl;
}
