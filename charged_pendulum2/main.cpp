#include "cpendfuncs.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <fstream>
#include <list>
void tester(){
    auto err = [](auto str){ std::cout << "cpendfuncs.h error in: " << str << "\n"; std::exit(-1); };
    Vector3<double> T{1.0,2.0,3.0};
    Vector3<double> M = changedp(T);
    Vector3<double> Nt = changepd(M);
    if(length(T-Nt) > 1e-14){err("change functions");}
    Vector3<double> A{-1.0,2.5,3.5};
    if(dcomponentssumphi(T,A)-1.0 > 1e-15){err("dcomponentssumphi");}
    if(dcomponentssumtheta(T,A)-1.5 > 1e-15){err("dcomponentssumtheta");}
    std::vector<double> q{1.0,2.0};
    double q0 = -1.0;
    Vector3<double> r0{20,30,40}; //x,y,z
    std::vector<Vector3<double>> rq(2);
    rq[0]={-10.0,0.0,0.0}; //x,y,z
    rq[1]={-20.0,0.0,0.0};
    if(cpendcasum(q,rq,r0,q0)+1/(sqrt(3400)*3400)+2/(sqrt(4100)*4100) > 1e-14){err("cpendcasum");}
    Vector3<double> v0{0.0,0.3,-2.0};
    double l = sqrt(sqv(r0.x) + sqv(r0.y) + sqv(r0.z));
    double m = 1.0;
    Vector3<double> result{0, -0.7896348289808466, 499.58387781204715}; //calculated with python3
    if(length(cpenda(r0,v0,rq,q0,q,m,l)-result) > 1e-15){err("cpenda");}
}
int main(int, char**) {
    tester();
    std::vector<double> q{-1.0,-2.0,1.0,1.0};
    double q0 = 1.0;
    Vector3<double> r0{120.0,200.0,-90}; //descartian
    Vector3<double> v0{0.0,0.0,0.0}; //polar
    double l = length(r0);
    std::vector<Vector3<double>> rq(4);
    rq[0]={-1000.0,5000.0,3000.0}; //descartian
    rq[1]={7000.0,3000.0,-8000.0}; //descartian
    rq[2]={5000.0,6000.0,-7000.0}; //descartian
    rq[3]={1000.0,2000.1,-9000.0}; //descartian
    double time = 0.0;
    double m = 1.0;
    int N = 100000;
    std::ofstream ofilet("t.txt");
    if(ofilet.is_open()){
        std::ofstream ofilex("x.txt");
        if(ofilex.is_open()){
            std::ofstream ofiley("y.txt");
            if(ofiley.is_open()){
                std::ofstream ofilez("z.txt");
                if(ofilez.is_open()){
                    std::ofstream ofilevx("vx.txt");
                    if(ofilevx.is_open()){
                        std::ofstream ofilevy("vy.txt");
                        if(ofilevy.is_open()){
                            std::ofstream ofilevz("vz.txt");
                            if(ofilevz.is_open()){
                                cpendsolve_rk4_txt(r0,v0,rq,time,time+4.0, N,q0,q,m,l,ofilet,ofilex,ofiley,ofilez,
                                ofilevx,ofilevy,ofilevz);
                            ofilevz.close();
                            }
                        ofilevy.close();
                        }
                    ofilevx.close();
                    }
                ofilez.close();
                }
            else{
                std::cout << "Unable to open file z.txt" << std::endl;
            }
            ofiley.close();
            }
            else{
                std::cout << "Unable to open file y.txt" << std::endl;
            }
        ofilex.close();
        }
        else{
            std::cout << "Unable to open file x.txt" << std::endl;
        }
    ofilet.close();
    }
    else{
        std::cout << "Unable to open file t.txt" << std::endl;
    }
    double x0 = 10.0;
    double vx0 = 2.5;
    double k = 0.3;
    double gamma = 0.7;
    std::ofstream ofiley("xg.txt");
    if(ofiley.is_open()){
        std::ofstream ofilez("tg.txt");
        if(ofilez.is_open()){
                        solve_rk4(x0,vx0,time,time + 20.0,N,k,m,gamma,ofilez,ofiley,[k,m,gamma](double x,double vx){
                return -k*x/m - gamma*vx/m;
            });
            ofilez.close();
        }
        else{
            std::cout << "Unable to open file z.txt" << std::endl;
        }
        ofiley.close();
    }
    std::cout << "Hello, world!\n";
}
