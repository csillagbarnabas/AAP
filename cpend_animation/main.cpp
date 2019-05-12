#include <iostream>
#include <array>
#include <random>
#include "miniwindow.h"
#include <vector>
#include <numeric>
#include <cmath>
#include <fstream>
#include <list>
template<typename T>
auto changedp(Vector3<T> const& r){//x,y,z
    auto R = sqrt(sq(r.x)+sq(r.y)+sq(r.z));
    return Vector3<T>{R,acos(r.z/R),atan2(r.y,r.x)};
}
template<typename T>
auto changepd(Vector3<T> const& r){//r,phi,theta
    auto sy = sin(r.y);
    return Vector3<T>{r.x*sy*cos(r.z),r.x*sy*sin(r.z),r.x*cos(r.y)};//x,y,z
}
template<typename T>
auto dcomponentssumphi(Vector3<T> const& r1, Vector3<T> const& r2){
    return r1.x+r1.y+r1.z-r2.x-r2.y-r2.z;
}
template<typename T>
auto dcomponentssumtheta(Vector3<T> const& r1, Vector3<T> const& r2){
    return r1.x+r1.y-r2.x-r2.y;
}
template<typename T, typename F, typename C>
auto cpendcasumphi(std::vector<T> const& q,std::vector<Vector3<F>> const& rq, Vector3<F> const& r, C const& q0){
    T sum = (T)0;
    for(int i = 0; i < rq.size(); ++i){
        sum += dcomponentssumphi(rq[i],r) * q0 * q[i]/(length(rq[i]-r)*sqlength(rq[i]-r));
    }
    return sum;
}
template<typename T, typename F, typename C> //külön tesztre készült fv, ami csak az új részeket tartalmazza
auto cpendcasum(std::vector<T> const& q,std::vector<Vector3<F>> const& rq, Vector3<F> const& r, C const& q0){
    T sum = (T)0;
    for(int i = 0; i < rq.size(); ++i){
        sum += q0 * q[i]/(length(rq[i]-r)*sqlength(rq[i]-r));
    }
    return sum;
}
template<typename T, typename F, typename C>
auto cpendcasumtheta(std::vector<T> const& q,std::vector<Vector3<F>> const& rq, Vector3<F> const& r, C const& q0){
    T sum = (T)0;
    for(int i = 0; i < rq.size(); ++i){
        sum += dcomponentssumtheta(rq[i],r) * q0 * q[i]/(length(rq[i]-r)*sqlength(rq[i]-r));
    }
    return sum;
}
template<typename State, typename C, typename kg, typename M>
auto cpenda( Vector3<State> const& r, Vector3<State> const& v, std::vector<Vector3<double>> const& rq, C const& q0,
std::vector<C> const& q,kg const& m, M const& l){
    Vector3<State> rd{changepd(r)};
    auto sy = sin(r.y); auto cy = cos(r.y); auto cz = cos(r.z); auto sz = sin(r.z);
    return Vector3<State>{(State)0,//9.81 is the gravitational acceleration in Hungary
    sy*cy*sq(v.z)+(double)9.81*sy/l - cpendcasumphi(q,rq,rd,q0)*(cy*cz+cy*sz-sy)/(m*l),
    -2*cy*sq(r.z)/sy-cpendcasumtheta(q,rq,rd,q0)*(sz-cz)/(m*l*sy)};
}
template<typename State, typename T, typename C, typename kg, typename M, typename Callback>
auto cpendsolve_rk4(Vector3<State> & r,Vector3<State>& v, std::vector<Vector3<double>> const& rq,
T const& t0,T const& t1, int const& N, C const& q0,std::vector<C> const& q,kg const& m, M const& l,
Callback cb){
    T h = (t1-t0)/N;
    r=changedp(r);
    T t = t0;
    int i = 0;
    while(i < N){
        Vector3<State> kv1 = cpenda(r,v,rq,q0,q,m,l); //mivel az egyenletekben nincs t, ezért nem is léptetem
        Vector3<State> kv2 = cpenda(r + (h * (T)0.5) * kv1,v + (h * (T)0.5) * kv1,rq,q0,q,m,l);
        Vector3<State> kv3 = cpenda(r + (h * (T)0.5) * kv2,v + (h * (T)0.5) * kv2,rq,q0,q,m,l);
        Vector3<State> kv4 = cpenda(r + h * kv3,v + h * kv3,rq,q0,q,m,l);
        Vector3<State> kr1 = v;
        Vector3<State> kr2 = v + (h * (T)0.5) * kr1;
        Vector3<State> kr3 = v + (h * (T)0.5) * kr2;
        Vector3<State> kr4 = v + h * kr3;
		v = v + (kv1 + kv4 + (T)2 * (kv2 + kv3)) * (h / (T)6);
        r = r + (kr1 + kr4 + (T)2 * (kr2 + kr3)) * (h / (T)6);
        t = t + h;
		cb(r);
        ++i;
    }
	return r;
}

struct App
{
	MainWindow wnd;
	std::vector<double> q;
    double q0;
    Vector3<double> r;
    Vector3<double> v0;
    double l;
    std::vector<Vector3<double>> rq;
    double time;
    double m;
    int N;
	std::vector<Vector3<double>> r1;
	std::vector<double> t;
	App()
	{
		q={-1.0,-2.0,1.0,1.0};
    	q0 = 1.0;
    	r={120.0,-200.0,-90}; //descartian
    	v0={0.0,0.0,0.0}; //polar
    	l = length(r);
    	rq.resize(4);
    	rq[0]={-1000.0,5000.0,3000.0}; //descartian
    	rq[1]={7000.0,3000.0,-8000.0}; //descartian
    	rq[2]={5000.0,6000.0,-7000.0}; //descartian
    	rq[3]={1000.0,2000.1,-9000.0}; //descartian
    	time = 0.0;
    	m = 1.0;
    	N = 30000;
		t.resize(N+1);
		r1.resize(N+1);
	}

	int enterApp()
	{
		wnd.window.eventDriven = false;
		wnd.mouseHandler([&](Mouse const&){ });
		wnd.resizeHandler([&](int /*w*/, int /*h*/, StateChange /*sc*/){} );
		wnd.idleHandler([&]
		{
			r =cpendsolve_rk4(r,v0,rq,time,time+4.0,N,q0,q,m,l,[this](Vector3<double> const& r)
			{
				r1.push_back(changepd(r)+Vector3<double>{300.0,300.0,0.0});
			} );
		});
		wnd.exitHandler([&]{});
		wnd.renderHandler( [&](SoftwareRenderer& p)
		{
			if(r1.size() > 4)
			{
                p.forall_pixels([](auto, auto, auto){ return color(255, 255, 255); });
		            for(int i=1; i<r1.size(); ++i)
		        {
			        p.line((int)r1[i-1].x, (int)r1[i-1].y, (int)r1[i].x, (int)r1[i].y, [&](auto){ return color(255, 64, 0); });
		        }
			}
		});
        bool res = wnd.open(L"C++ App", {42, 64}, {640, 480}, true, [&]{ return true; });
		std::cout<< r1[N-1] << std::endl;
		return res ? 0 : -1;
	}
};

//#ifdef _WIN32
//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
//#else
int main()
//#endif
{
	return App{}.enterApp();
}