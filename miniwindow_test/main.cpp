#include <iostream>
#include <array>
#include <random>
#include "miniwindow.h"
#include <fstream>

template<typename State, typename T, typename RHS, typename Callback> 
auto solve_rk4(State y0, T t0, T t1, T h, RHS f, Callback cb)
{
	T t = t0;
	State y = y0;
	while(t < t1)
	{
		if(t + h > t1){ h = t1 - t; }
		State k1 = f(t, y);
		State k2 = f(t + h * (T)0.5, y + (h * (T)0.5) * k1);
		State k3 = f(t + h * (T)0.5, y + (h * (T)0.5) * k2);
		State k4 = f(t + h,          y +  h           * k3);
	
        y = y + (k1 + k4 + (T)2 * (k2 + k3)) * (h / (T)6);
		t = t + h;
		cb(t, y);
	}
	return y;
}
void txt(std::vector<Vector2<double>> const& data,std::ofstream& xtxt,std::ofstream& ytxt){
		for(int i=0;i<data.size();++i){
			xtxt << data[i].x << std::endl;
			ytxt << data[i].y << std::endl;
		}
	}
struct App
{
	MainWindow wnd;

	Vector2<double> state;
	double time, h;
	double a, b, c, d;

	std::vector<Vector2<double>> data;

	App()
	{
		a = 20., b = 1., c = 30.0, d = 1.;
		h = 0.00002;
		time = 0.0;
		state = {8.0, 12.0};
	}

	int enterApp(std::ofstream& xtxt,std::ofstream& ytxt)
	{
		wnd.window.eventDriven = false;

		wnd.mouseHandler([&](Mouse const&){ });
		wnd.resizeHandler([&](int /*w*/, int /*h*/, StateChange /*sc*/){} );
		wnd.idleHandler([&]
		{
			state = solve_rk4(state, time, time + 0.001, h,
			[this](double const& t, Vector2<double> const& s)->Vector2<double>
			{
				return {a*s.x - b*s.x*s.y, d*s.x*s.y - c*s.y };
			},
			[this](double const& t, Vector2<double> const& state)
			{
				//std::cout << t << "   " << state.x << "   " << state.y << "\n";
				data.push_back(state);
			} );
		});
		wnd.exitHandler([&]{});

		wnd.renderHandler( [&](SoftwareRenderer& r)
		{
			r.forall_pixels([](auto, auto, auto){ return color(255, 255, 255); });
			if(data.size() > 4)
			{
				r.myline(color(128, 128, 128),data);
				for(int i=1; i<data.size(); ++i)
			{
				r.line((int)data[i-1].x, (int)data[i-1].y, (int)data[i].x, (int)data[i].y, [&](auto){ return color(128, 128, 128); });
			}
			}
		});

		bool res = wnd.open(L"C++ App", {42, 64}, {640, 480}, true, [&]{ return true; });
		txt(data,xtxt,ytxt);
		return res ? 0 : -1;
	}
};

//#ifdef _WIN32
//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
//#else
int main()
//#endif
{
	std::ofstream ofilex("xt.txt");
    if(ofilex.is_open()){
		std::ofstream ofiley("yt.txt");
    	if(ofiley.is_open()){
			return App{}.enterApp(ofilex,ofiley);
    		ofiley.close();
    	}
    	ofilex.close();
    }
}