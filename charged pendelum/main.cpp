#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include "..\headers\vector3.h"
#include <fstream>
#include <list>

template<typename T, typename F, typename RHS, typename C>
auto cpendcasum(std::vector<T> q,std::vector<Vector3<F>> rq, Vector3<F> rp, RHS f, C q0){
    T sum = (T)0;
    for(int i = 0; i < rq.size(); ++i){
        sum += f(rq[i],rp)*q0 * q[i]/(length(rq[i]-rp)*sqlength(rq[i]-rp));
    }
    return sum;
}
template<typename State, typename C, typename kg, typename M>
auto cpenda(Vector3<State> r,Vector3<State> v, std::vector<Vector3<double>> rq, C q0,
std::vector<C> q,kg m, M l){
    State phi = r.z;
    r.z = - l * cos(r.z);
    return Vector3<State>{-cpendcasum(q,rq,r,[](Vector3<State> a, Vector3<State> b){return a.x-b.x;},q0)/m,
    -cpendcasum(q,rq,r,[](Vector3<State> a, Vector3<State> b){return a.y-b.y;},q0)/m,
    cos(phi) * sq(v.z) / sin(phi) - 9.81 / (l *sin(phi)) - cpendcasum(q,rq,r,[](Vector3<State> a, Vector3<State> b)
    {return a.y-b.y;},q0)/(m * l * sin(phi))};
}
template<typename State, typename T, typename C, typename kg, typename M>
void cpendsolve_rk4(Vector3<State> r0,Vector3<State> v0, std::vector<Vector3<double>> rq,T t0, T t1, int N, C q0,
std::vector<C> q,kg m, M l,std::ofstream& ttxt,std::ofstream& xtxt,std::ofstream& ytxt,std::ofstream& ztxt){
    T t = t0; 
    Vector3<State> r = r0;
    Vector3<State> v = v0;
    T h = (t1-t0)/N;
    std::vector<Vector3<State>> rs(N);
    std::vector<double> ts(N);
    int i = 0;
    while(i < N){
        rs[i] = r;
        ts[i] = t;
        Vector3<State> kv1 = cpenda(r,v,rq,q0,q,m,l); //mivel az egyenletekben nincs t, ezért nem is léptetem
        Vector3<State> kv2 = cpenda(r + (h * (T)0.5) * kv1,v,rq,q0,q,m,l);
        Vector3<State> kv3 = cpenda(r + (h * (T)0.5) * kv2,v,rq,q0,q,m,l);
        Vector3<State> kv4 = cpenda(r + h * kv3,v,rq,q0,q,m,l);
        v = v + (kv1 + kv4 + (T)2 * (kv2 + kv3)) * (h / (T)6);
        Vector3<State> kr1 = v;
        Vector3<State> kr2 = v + (h * (T)0.5) * kr1;
        Vector3<State> kr3 = v + (h * (T)0.5) * kr2;
        Vector3<State> kr4 = v + h * kr3;
        r = r + (kr1 + kr4 + (T)2 * (kr2 + kr3)) * (h / (T)6);
        t = t + h; //csak az idő múlását mérem vele
        ++i;
    }
    for(int j = 0; j < N; ++j){
        xtxt << rs[j].x <<std::endl;
        ytxt << rs[j].y <<std::endl;
        ztxt << - l* cos(rs[j].z) <<std::endl;
        ttxt << ts[j] <<std::endl;

    }
}
int main(int, char**) {
    std::vector<double> q{1.0,2.0};
    double q0 = -1.0;
    double l = 5.0;
    Vector3<double> r0{1.5,1.5,acos(sqrt(1-(sq(r0.x)+sq(r0.y))/sq(l)))}; //x,y,phi
    Vector3<double> v0{0.0,0.0,0.0}; //x,y,phi
    std::vector<Vector3<double>> rq(2);
    rq[0]={2.0,3.0,4.0}; //x,y,z
    rq[1]={-2.0,-3.0,4.0}; //x,y,z
    double time = 0.0;
    double m = 1.0;
    int N = 10000;
    std::ofstream ofilet("t.txt");
    if(ofilet.is_open()){
        std::ofstream ofilex("x.txt");
        if(ofilex.is_open()){
            std::ofstream ofiley("y.txt");
            if(ofiley.is_open()){
                std::ofstream ofilez("z.txt");
                if(ofilez.is_open()){
                cpendsolve_rk4(r0,v0,rq,time,time+1.0, N,q0,q,m,l,ofilet,ofilex,ofiley,ofilez);
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
    std::cout << "Hello, world!\n";
}