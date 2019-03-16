#include <iostream>
#include "vector2.h"

using namespace std;

int main(int, char**) {
    Vector2<double> A = {-2.0,3.6};
    Vector2<double> B = {1.42,1.0};
    Vector2<double> C = {1.9,-4.0};
    double g = 2.0;
    Vector2<double> D = A += B;
    Vector2<double> A1 = {-2.0,3.6};
    Vector2<double> G = A1 -= B;
    Vector2<double> A2 = {-2.0,3.6};
    Vector2<double> E = A2 *= g;
    Vector2<double> A3 = {-2.0,3.6};
    Vector2<double> F = A3 + C;
    Vector2<double> K = C * g;
    Vector2<double> L = g * C;
    Vector2<double> M = C / g;
    Vector2<double> N = A3 - C;
    cout << "A vector: (-2.0,3.6)" << endl;
    cout << "B vector: (1.42,1.0)" << endl;
    cout << "C vector: (1.9,-4.0)" << endl;
    cout << "g = "<< g << endl;
    cout << "Tests of the operators (only the first components):" << endl;
    cout << "A_1 += B_1, A_1 =" << D.x << endl;
    cout << "A_1 -= B_1, A_1=" << G.x << endl;
    cout << "A_1 *= g, A_1=" << E.x << endl;
    cout << "A_1 + C_1 = " << F.x << endl;
    cout << "C_1 * g = " << K.x << endl;
    cout << "g * C_1 = " << L.x << endl;
    cout << "C_1 / g = " << M.x << endl;
    cout << "A_1 - C_1 = " << N.x << endl;
}
