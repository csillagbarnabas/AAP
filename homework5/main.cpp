#include <iostream>
#include "..\headers\Matrix.h"
template<typename T, typename F, typename G>
void comp_matrix(Matrix<T> const& A, Matrix<F> const& B, G str){
	if(A.Nsize() != B.Nsize()){
		std::cout << "Matrix.h error in: " << str << "[N size]" << "\n";
		std::exit(-1);
	}
	if(A.datasize() != B.datasize()){
		std::cout << "Matrix.h error in: " << str << "[datasize]" << "\n";
		std::exit(-1);
	}
	for(int i = 0; i < A.Nsize()*A.Nsize(); ++i){
		if (A[i] - B[i] > 1e-13 ){
			std::cout << "Matrix.h error in: " << str << "[elements]" << "\n";
			std::exit(-1);
		}
	}
}
int main(int, char**) {
    auto err = [](auto str){ std::cout << "Matrix.h error in: " << str << "\n"; std::exit(-1); };
    //Test default constructor:
	{
		Matrix<double> u;
		if(u.datasize() != 0)         { err("default contructor test [datasize]");           }
		if(u.Nsize() != 0)         { err("default contructor test [Nsize]");           }
		if(u.begin() != u.end())  { err("default contructor test [begin == end]");   }
		if(u.cbegin() != u.cend()){ err("default contructor test [cbegin == cend]"); }
	}
    //Test list initialization and indexing:
    {
        Matrix<double> a{3,{3.1, -5.2, 9.3,4.2,5.3,6.4,7.5,8.6,9.7}};
		if(a.datasize() != 9)                            { err("initializer list constructor test [datasize]"); }
		if(a.Nsize() != 3)                            { err("initializer list constructor test [Nsize]"); }
		if(a[0] != 3.1 || a[1] != -5.2 || a[2] != 9.3 || a[3] != 4.2 || a[4] != 5.3 || a[5] != 6.4 || a[6] != 7.5 ||
        a[7] != 8.6 || a[8] != 9.7){ err("initializer list constructor test [indexing with []]");   }
		if(3.1 != a(0,0) || -5.2 != a(0,1) || 9.3 != a(0,2) || 4.2 != a(1,0) || 5.3 != a(1,1) || 6.4 != a(1,2) || 
        7.5 != a(2,0) || 8.6 != a(2,1) || 9.7 != a(2,2)){ err("initializer list constructor test [indexing with ()]");   }
		if(++ ++ ++ ++ ++ ++ ++ ++ ++(a.begin()) != a.end() )
        { err("initializer list constructor test [begin + 9 == end]");   }
		if(++ ++ ++ ++ ++ ++ ++ ++ ++(a.cbegin()) != a.cend() )
        { err("initializer list constructor test [cbegin + 9 == cend]"); }
	}
    //Test copy constructor:
    {
		Matrix<double> a{3,{3.1, 5.2, 9.3,4.2,5.3,6.4,-7.5,8.6,9.7}};
		Matrix<double> b{a};
		if(b.datasize() != 9)                            { err("copy constructor test [datasize]");               }
		if(b.Nsize() != 3)                            { err("copy constructor test [N size]");           }
		if(b[0] != 3.1 || b[1] != 5.2 || b[2] != 9.3 || b[3] != 4.2 || b[4] != 5.3 || b[5] != 6.4 || b[6] != -7.5 || 
        b[7] != 8.6 || b[8] != 9.7){ err("copy constructor test [elements]");           }
        if(3.1 != b(0,0) || 5.2 != b(0,1) || 9.3 != b(0,2) || 4.2 != b(1,0) || 5.3 != b(1,1) || 6.4 != b(1,2) || 
        -7.5 != b(2,0) || 8.6 != b(2,1) || 9.7 != b(2,2)){ err("copy constructor test (src elements)");   }
		if(++ ++ ++ ++ ++ ++ ++ ++ ++(b.begin()) != b.end() )         
        { err("copy constructor test [begin + 9 == end]");   }
		if(++ ++ ++ ++ ++ ++ ++ ++ ++(b.cbegin()) != b.cend() )       
        { err("copy constructor test [cbegin + 9 == cend]"); }
		if(a.datasize() != 9)                            { err("copy constructor test [src datasize]");           }
		if(a.Nsize() != 3)                            { err("copy constructor test [src N size]");           }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 4.2 || a[4] != 5.3 || a[5] != 6.4 || a[6] != -7.5 || 
        a[7] != 8.6 || a[8] != 9.7){ err("copy constructor test [src elements]");       }
        if(3.1 != a(0,0) || 5.2 != a(0,1) || 9.3 != a(0,2) || 4.2 != a(1,0) || 5.3 != a(1,1) || 6.4 != a(1,2) || 
        -7.5 != a(2,0) || 8.6 != a(2,1) || 9.7 != a(2,2)){ err("copy constructor test (src elements)");   }
	}
	//Test move construktor:
    {
		Matrix<double> a{3,{3.1, 5.2, -9.3,4.2,5.3,6.4,7.5,8.6,9.7}};
		Matrix<double> b{ std::move(a) };
		if(b.datasize() != 9)                            { err("move constructor test [datasize]");               }
		if(b.Nsize() != 3)                            { err("move constructor test [N size]");               }
		if(b[0] != 3.1 || b[1] != 5.2 || b[2] != -9.3 || b[3] != 4.2 || b[4] != 5.3 || b[5] != 6.4 || b[6] != 7.5 || 
        b[7] != 8.6 || b[8] != 9.7){ err("move constructor test [elements]");           }
        if(3.1 != b(0,0) || 5.2 != b(0,1) || -9.3 != b(0,2) || 4.2 != b(1,0) || 5.3 != b(1,1) || 6.4 != b(1,2) || 
        7.5 != b(2,0) || 8.6 != b(2,1) || 9.7 != b(2,2)){ err("move constructor test (src elements)");   }
		if(++ ++ ++ ++ ++ ++ ++ ++ ++(b.begin()) != b.end() )         
        { err("move constructor test [begin + 9 == end]");   }
		if(++ ++ ++ ++ ++ ++ ++ ++ ++(b.cbegin()) != b.cend() )       
        { err("move constructor test [cbegin + 9 == cend]"); }
		if(a.datasize() != 0)                            { err("move constructor test [src datasize]");           }
		if(a.Nsize() != 0)                            { err("move constructor test [src Nsize]");           }
        if(a.begin() != a.end())                     { err("move constructor test [src begin == src end]"); }
	}
    //Test assignment:
    {
		Matrix<double> a{3,{3.1, 5.2, 9.3,4.2,5.3,6.4,7.5,8.6,-9.7}};
		Matrix<double> b = a;
		if(b.datasize() != 9)                            { err("assignment test [datasize]");               }
		if(b.Nsize() != 3)                            { err("assignment test [N size]");               }
		if(b[0] != 3.1 || b[1] != 5.2 || b[2] != 9.3 || b[3] != 4.2 || b[4] != 5.3 || b[5] != 6.4 || b[6] != 7.5 || 
        b[7] != 8.6 || b[8] != -9.7){ err("assignment test [elements]");           }
        if(3.1 != b(0,0) || 5.2 != b(0,1) || 9.3 != b(0,2) || 4.2 != b(1,0) || 5.3 != b(1,1) || 6.4 != b(1,2) || 
        7.5 != b(2,0) || 8.6 != b(2,1) || -9.7 != b(2,2)){ err("assignment test (src elements)");   }
		if(a.datasize() != 9)                            { err("assignment test [src datasize]");           }
		if(a.Nsize() != 3)                            { err("assignment test [src N size]");           }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 4.2 || a[4] != 5.3 || a[5] != 6.4 || a[6] != 7.5 || 
        a[7] != 8.6 || a[8] != -9.7){ err("assignment test [src elements]");       }
        if(3.1 != a(0,0) || 5.2 != a(0,1) || 9.3 != a(0,2) || 4.2 != a(1,0) || 5.3 != a(1,1) || 6.4 != a(1,2) || 
        7.5 != a(2,0) || 8.6 != a(2,1) || -9.7 != a(2,2)){ err("assignment test (src elements)");   }
	}
    //Test self assignment:
    {
		Matrix<double> a{3,{3.1, 5.2, 9.3,4.2,5.3,6.4,7.5,8.6,-9.7}};
		a = a;
		if(a.datasize() != 9)                            { err("self assignment test [src datasize]");           }
		if(a.Nsize() != 3)                            { err("self assignment test [src N size]");           }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 4.2 || a[4] != 5.3 || a[5] != 6.4 || a[6] != 7.5 || 
        a[7] != 8.6 || a[8] != -9.7){ err("self assignment test [src elements]");       }
        if(3.1 != a(0,0) || 5.2 != a(0,1) || 9.3 != a(0,2) || 4.2 != a(1,0) || 5.3 != a(1,1) || 6.4 != a(1,2) || 
        7.5 != a(2,0) || 8.6 != a(2,1) || -9.7 != a(2,2)){ err("self assignment test (src elements)");   }
	}
	//Test move assignment:
    {
		Matrix<double> a{3,{3.1, 5.2, 9.3,4.2,5.3,6.4,7.5,8.6,-9.7}};
		Matrix<double> b = std::move(a);
		if(b.datasize() != 9)                            { err("move assignment test [datasize]");               }
		if(b.Nsize() != 3)                            { err("move assignment test [N size]");               }
		if(b[0] != 3.1 || b[1] != 5.2 || b[2] != 9.3 || b[3] != 4.2 || b[4] != 5.3 || b[5] != 6.4 || b[6] != 7.5 || 
        b[7] != 8.6 || b[8] != -9.7){ err("move assignment test [elements]");           }
        if(3.1 != b(0,0) || 5.2 != b(0,1) || 9.3 != b(0,2) || 4.2 != b(1,0) || 5.3 != b(1,1) || 6.4 != b(1,2) || 
        7.5 != b(2,0) || 8.6 != b(2,1) || -9.7 != b(2,2)){ err("move assignment test (src elements)");   }
		if(a.datasize() != 0)                            { err("move assignment test [src datasize]");           }
		if(a.Nsize() != 0)                            { err("move assignment test [src N size]");           }
	}
    //Test operator- (l-value, l-value)
	{
		Matrix<double> a{3,{3.1, 5.2, 9.3,4.2,5.3,6.4,7.5,8.6,-9.7}};
		Matrix<double> b{3,{1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9}};
		Matrix<double> ref{3,{2.0,3.0,6.0,-0.2,-0.2,-0.2,-0.2,-0.2,-19.6}};
		Matrix<double> res = a - b;
		if(a.datasize() != 9)                              { err("operator- test (l-value, l-value) [src datasize1]");     }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 4.2 || a[4] != 5.3 || a[5] != 6.4 || a[6] != 7.5 || 
        a[7] != 8.6 || a[8] != -9.7)  { err("operator- test (l-value, l-value) [src elements]"); }
		if(b.datasize() != 9)                              { err("operator- test (l-value, l-value) [src datasize2]");     }
		if(b[0] != 1.1 || b[1] != 2.2 || b[2] != 3.3 || b[3] != 4.4 || b[4] != 5.5 || b[5] != 6.6 || b[6] != 7.7 || 
        b[7] != 8.8 || b[8] != 9.9){ err("operator- test (l-value, l-value) [src elements]"); }
		if(res.datasize() != 9)                            { err("operator- test (l-value, l-value) [datasize]");         }
		comp_matrix(res, ref, "operator- test (l-value, l-value)");
	}
    //Test operator- (r-value, l-value)
	{
		Matrix<double> a{3,{3.1, 5.2, 9.3,4.2,5.3,6.4,7.5,8.6,9.7}};
		Matrix<double> b{3,{1.1,-2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9}};
		Matrix<double> ref{3,{2.0,7.4,6.0,-0.2,-0.2,-0.2,-0.2,-0.2,-0.2}};
		Matrix<double> res = std::move(a) - b;
		if(a.datasize() != 0)                              { err("operator- test (r-value, l-value) [src datasize1]");   }
		if(b.datasize() != 9)                              { err("operator- test (r-value, l-value) [src datasize2]");     }
		if(b[0] != 1.1 || b[1] != -2.2 || b[2] != 3.3 || b[3] != 4.4 || b[4] != 5.5 || b[5] != 6.6 || b[6] != 7.7 || 
        b[7] != 8.8 || b[8] != 9.9){ err("operator- test (r-value, l-value) [src elements]"); }
		if(a.Nsize() != 0)                              { err("operator- test (r-value, l-value) [src Nsize1]");   }
		if(res.datasize() != 9)                            { err("operator- test (r-value, l-value) [datasize]");         }
		comp_matrix(ref,res,"operator- test (r-value, l-value)");
	}
    //Test operator- (l-value, r-value)
	{
		Matrix<double> a{3,{-3.1, 5.2, 9.3,4.2,5.3,6.4,7.5,8.6,9.7}};
		Matrix<double> b{3,{1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9}};
		Matrix<double> ref{3,{-4.2,3.0,6.0,-0.2,-0.2,-0.2,-0.2,-0.2,-0.2}};
		Matrix<double> res = a - std::move(b);
		if(a.datasize() != 9)                              { err("operator- test (l-value, r-value) [src datasize1]");     }
		if(a[0] != -3.1 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 4.2 || a[4] != 5.3 || a[5] != 6.4 || a[6] != 7.5 || 
        a[7] != 8.6 || a[8] != 9.7)  { err("operator- test (l-value, r-value) [src elements]"); }
		if(b.datasize() != 0)                              { err("operator- test (l-value, r-value) [src datasize2]");     }
		if(b.Nsize() != 0)                              { err("operator- test (l-value, r-value) [src Nsize2]");     }
		if(res.datasize() != 9)                            { err("operator- test (l-value, r-value) [datasize]");         }
		comp_matrix(ref,res,"operator- test (l-value, r-value)");
	}
	//Test operator- (r-value, r-value)
	{
		Matrix<double> a{3,{3.1, 5.2, 9.3,4.2,5.3,6.4,7.5,8.6,9.7}};
		Matrix<double> b{3,{1.1,2.2,3.3,-4.4,5.5,6.6,7.7,8.8,9.9}};
		Matrix<double> ref{3,{2.0,3.0,6.0,8.6,-0.2,-0.2,-0.2,-0.2,-0.2}};
		Matrix<double> res = std::move(a) - std::move(b);
		if(a.Nsize() != 0)                              { err("operator- test (r-value, r-value) [src Nsize1]");	}
		if(a.datasize() != 0)                              { err("operator- test (r-value, r-value) [src datasize1]"); }
		if(b.datasize() != 9)                              { err("operator- test (r-value, r-value) [src datasize2]"); }
		if(res.datasize() != 9)                            { err("operator- test (r-value, r-value) [datasize]");      }
		comp_matrix(ref,res,"operator- test (r-value, r-value)");
	}
	//Test operator+ (l-value, l-value)
	{
		Matrix<double> a{3,{3.1, 5.2, 9.3,4.2,5.3,6.4,7.5,8.6,9.7}};
		Matrix<double> b{3,{1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,-9.9}};
		Matrix<double> ref{3,{4.2,7.4,12.6,8.6,10.8,13.0,15.2,17.4,-0.2}};
		Matrix<double> res = a + b;
		if(a.datasize() != 9)                              { err("operator+ test (l-value, l-value) [src datasize1]");     }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 4.2 || a[4] != 5.3 || a[5] != 6.4 || a[6] != 7.5 || 
        a[7] != 8.6 || a[8] != 9.7)  { err("operator+ test (l-value, l-value) [src elements]"); }
		if(b.datasize() != 9)                              { err("operator+ test (l-value, l-value) [src datasize2]");     }
		if(b[0] != 1.1 || b[1] != 2.2 || b[2] != 3.3 || b[3] != 4.4 || b[4] != 5.5 || b[5] != 6.6 || b[6] != 7.7 || 
        b[7] != 8.8 || b[8] != -9.9){ err("operator+ test (l-value, l-value) [src elements]"); }
		if(res.datasize() != 9)                            { err("operator+ test (l-value, l-value) [datasize]");         }
		comp_matrix(ref,res,"operator+ test (l-value, l-value)");
	}
	//Test operator+ (r-value, l-value)
	{
		Matrix<double> a{3,{3.1, 5.2, 9.3,4.2,5.3,6.4,7.5,-8.6,9.7}};
		Matrix<double> b{3,{1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9}};
		Matrix<double> ref{3,{4.2,7.4,12.6,8.6,10.8,13.0,15.2,0.2,19.6}};
		Matrix<double> res = std::move(a) + b;
		if(a.datasize() != 0)                              { err("operator+ test (r-value, l-value) [src datasize1]");     }
		if(a.Nsize() != 0)                              { err("operator+ test (r-value, l-value) [src Nsize1]");     }
		if(b.datasize() != 9)                              { err("operator+ test (r-value, l-value) [src datasize2]");     }
		if(b[0] != 1.1 || b[1] != 2.2 || b[2] != 3.3 || b[3] != 4.4 || b[4] != 5.5 || b[5] != 6.6 || b[6] != 7.7 || 
        b[7] != 8.8 || b[8] != 9.9){ err("operator+ test (r-value, l-value) [src elements]"); }
		if(res.datasize() != 9)                            { err("operator+ test (r-value, l-value) [datasize]");         }
		comp_matrix(ref,res,"operator+ test (r-value, l-value)");
	}
	//Test operator+ (l-value, r-value)
	{
		Matrix<double> a{3,{-3.1, 5.2, 9.3,4.2,5.3,6.4,7.5,8.6,9.7}};
		Matrix<double> b{3,{1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9}};
		Matrix<double> ref{3,{-2.0,7.4,12.6,8.6,10.8,13.0,15.2,17.4,19.6}};
		Matrix<double> res = a + std::move(b);
		if(a.datasize() != 9)                              { err("operator+ test (l-value, r-value) [src datasize1]");     }
		if(a[0] != -3.1 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 4.2 || a[4] != 5.3 || a[5] != 6.4 || a[6] != 7.5 || 
        a[7] != 8.6 || a[8] != 9.7)  { err("operator+ test (l-value, r-value) [src elements]"); }
		if(b.datasize() != 0)                              { err("operator+ test (l-value, r-value) [src datasize2]");     }
		if(b.Nsize() != 0)                              { err("operator+ test (l-value, r-value) [src Nsize2]");     }
		if(res.datasize() != 9)                            { err("operator+ test (l-value, r-value) [datasize]");         }
		comp_matrix(ref,res,"operator+ test (l-value, r-value)");
	}
	//Test operator+ (r-value, r-value)
	{
		Matrix<double> a{3,{3.1, -5.2, 9.3,4.2,5.3,6.4,7.5,8.6,9.7}};
		Matrix<double> b{3,{1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9}};
		Matrix<double> ref{3,{4.2,-3.0,12.6,8.6,10.8,13.0,15.2,17.4,19.6}};
		Matrix<double> res = std::move(a) + std::move(b);
		if(a.datasize() != 0)                              { err("operator+ test (r-value, r-value) [src datasize1]");     }
		if(a.Nsize() != 0)                              { err("operator+ test (r-value, r-value) [src Nsize1]");     }
		if(b.datasize() != 9)                              { err("operator+ test (r-value, r-value) [src datasize2]");     }
		if(res.datasize() != 9)                            { err("operator+ test (r-value, r-value) [datasize]");         }
		comp_matrix(ref,res,"operator+ test (r-value, r-value)");
	}
	//Test +=:
	{
		Matrix<double> a{3,{3.1, 5.2, 9.3,4.2,5.3,6.4,7.5,8.6,9.7}};
		Matrix<double> b{3,{1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9}};
		Matrix<double> ref{3,{4.2,7.4,12.6,8.6,10.8,13.0,15.2,17.4,19.6}};
		a += b;
		if(a.datasize() != 9)                              { err("operator+= test [src datasize1]");     }
		if(b.datasize() != 9)                              { err("operator+= test [src datasize2]");     }
		if(b[0] != 1.1 || b[1] != 2.2 || b[2] != 3.3 || b[3] != 4.4 || b[4] != 5.5 || b[5] != 6.6 || b[6] != 7.7 || 
        b[7] != 8.8 || b[8] != 9.9){ err("operator+= test [src elements]"); }
		comp_matrix(ref,a,"operator+= test");
	}
	//Test operator-=:
	{
		Matrix<double> a{3,{3.1, 5.2, 9.3,4.2,5.3,6.4,7.5,8.6,-9.7}};
		Matrix<double> b{3,{1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9}};
		Matrix<double> ref{3,{2.0,3.0,6.0,-0.2,-0.2,-0.2,-0.2,-0.2,-19.6}};
		a -= b;
		if(a.datasize() != 9)                              { err("operator-= test [src datasize1]");     }
		if(b.datasize() != 9)                              { err("operator-= test [src datasize2]");     }
		if(b[0] != 1.1 || b[1] != 2.2 || b[2] != 3.3 || b[3] != 4.4 || b[4] != 5.5 || b[5] != 6.6 || b[6] != 7.7 || 
        b[7] != 8.8 || b[8] != 9.9){ err("operator-= test [src elements]"); }
		comp_matrix(ref,a,"operator-= test");
	}
	//Test *=:
	{
		Matrix<double> a{3,{3.1, 5.2, 9.3,-4.2,5.3,6.4,7.5,8.6,9.7}};
		Matrix<double> ref{3,{6.2,10.4,18.6,-8.4,10.6,12.8,15.0,17.2,19.4}};
		a *= 2.0;
		if(a.datasize() != 9)                            { err("operator*= test [datasize]");         }
		comp_matrix(ref,a,"operator*= test");
	}
	//Test operator* (l-value, scalar)
	{
		Matrix<double> a{3,{3.1, -5.2, 9.3,4.2,5.3,6.4,7.5,8.6,9.7}};
		Matrix<double> ref{3,{6.2,-10.4,18.6,8.4,10.6,12.8,15.0,17.2,19.4}};
		Matrix<double> res{3,{}};
		res = a * 2.0;
		if(res.datasize() != 9)                            { err("operator* (l-value, scalar) test [datasize]");         }
		comp_matrix(ref,res,"operator* (l-value, scalar) test");
	}
	//Test operator* (r-value, scalar)
	{
		Matrix<double> a{3,{3.1, 5.2, 9.3,4.2,5.3,6.4,7.5,-8.6,9.7}};
		Matrix<double> ref{3,{6.2,10.4,18.6,8.4,10.6,12.8,15.0,-17.2,19.4}};
		Matrix<double> res{3,{}};
		res = std::move(a) * 2.0;
		if(a.datasize() != 0)                              { err("operator* test (r-value, scalar) [src datasize]");	}
		if(a.Nsize() != 0)                              { err("operator* test (r-value, scalar) [src Nsize]");	}
		if(res.datasize() != 9)                            { err("operator* (r-value, scalar) test [datasize]");         }
		comp_matrix(ref,res,"operator* (r-value, scalar) test");
	}
	//Test operator* (scalar, l-value)
	{
		Matrix<double> a{3,{3.1, 5.2, -9.3,4.2,5.3,6.4,7.5,8.6,9.7}};
		Matrix<double> ref{3,{6.2,10.4,-18.6,8.4,10.6,12.8,15.0,17.2,19.4}};
		Matrix<double> res{3,{}};
		res = 2.0 * a;
		if(res.datasize() != 9)                            { err("operator* (scalar, l-value) test [datasize]");         }
		comp_matrix(ref,res,"operator* (scalar, l-value) test");
	}
	//Test operator* (scalar, r-value)
	{
		Matrix<double> a{3,{3.1, 5.2, 9.3,4.2,5.3,6.4,7.5,-8.6,9.7}};
		Matrix<double> ref{3,{6.2,10.4,18.6,8.4,10.6,12.8,15.0,-17.2,19.4}};
		Matrix<double> res{3,{}};
		res = 2.0 * std::move(a);
		if(a.datasize() != 0)                              { err("operator* test (scalar, r-value) [src datasize]");	}
		if(a.Nsize() != 0)                              { err("operator* test (scalar, r-value) [src Nsize]");	}
		if(res.datasize() != 9)                            { err("operator* (scalar, r-value) test [datasize]");         }
		comp_matrix(ref,res,"operator* (scalar, r-value) test");
	}
	//Test operator/ (l-value, scalar)
	{
		Matrix<double> a{3,{3.1, 5.2, 9.3,4.2,-5.3,6.4,7.5,8.6,9.7}};
		Matrix<double> ref{3,{1.55, 2.6,4.65,2.1,-2.65,3.2,3.75,4.3,4.85}};
		Matrix<double> res{3,{}};
		res = a / 2.0;
		if(res.datasize() != 9)                            { err("operator/ (l-value, scalar) test [datasize]");         }
		comp_matrix(ref,res,"operator/ (l-value, scalar) test");
	}
	//Test operator/ (r-value, scalar)
	{
		Matrix<double> a{3,{3.1, 5.2, -9.3,4.2,5.3,6.4,7.5,8.6,9.7}};
		Matrix<double> ref{3,{1.55, 2.6,-4.65,2.1,2.65,3.2,3.75,4.3,4.85}};
		Matrix<double> res{3,{}};
		res = std::move(a) / 2.0;
		if(a.datasize() != 0)                              { err("operator/ test (r-value, scalar) [src datasize]");     }
		if(a.Nsize() != 0)                              { err("operator/ test (r-value, scalar) [src Nsize]");     }
		if(res.datasize() != 9)                            { err("operator/ (r-value, scalar) test [datasize]");         }
		comp_matrix(ref,res,"operator/ (r-value, scalar) test");
	}
	//Test operator* (l-value, l-value)
	{
		Matrix<double> a{3,{3.1, 5.2, 9.3,4.2,5.3,6.4,7.5,8.6,9.7}};
		Matrix<double> b{3,{1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9}};
		Matrix<double> ref{3,{97.9,117.26,136.62,77.22,94.71,112.2,120.78,149.16,177.54}};
		Matrix<double> res = a * b;
		if(a.datasize() != 9)                              { err("operator* test (l-value, l-value) [src datasize1]");     }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 4.2 || a[4] != 5.3 || a[5] != 6.4 || a[6] != 7.5 || 
        a[7] != 8.6 || a[8] != 9.7)  { err("operator* test (l-value, l-value) [src elements]"); }
		if(b.datasize() != 9)                              { err("operator+ test (l-value, l-value) [src datasize2]");     }
		if(b[0] != 1.1 || b[1] != 2.2 || b[2] != 3.3 || b[3] != 4.4 || b[4] != 5.5 || b[5] != 6.6 || b[6] != 7.7 || 
        b[7] != 8.8 || b[8] != 9.9){ err("operator* test (l-value, l-value) [src elements]"); }
		if(res.datasize() != 9)                            { err("operator* test (l-value, l-value) [datasize]");         }
		comp_matrix(ref,res,"operator* test (l-value, l-value)");
	}
	//Test operator* (r-value, l-value)
	{
		Matrix<double> a{3,{3.1, 5.2, 9.3,4.2,5.3,6.4,7.5,8.6,9.7}};
		Matrix<double> b{3,{1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9}};
		Matrix<double> ref{3,{97.9,117.26,136.62,77.22,94.71,112.2,120.78,149.16,177.54}};
		Matrix<double> res = std::move(a) * b;
		if(a.datasize() != 0)                              { err("operator* test (r-value, l-value) [src datasize1]");	}
		if(a.Nsize() != 0)                              { err("operator* test (r-value, l-value) [src Nsize1]");	}
		if(b.datasize() != 9)                              { err("operator+ test (r-value, l-value) [src datasize2]");     }
		if(b[0] != 1.1 || b[1] != 2.2 || b[2] != 3.3 || b[3] != 4.4 || b[4] != 5.5 || b[5] != 6.6 || b[6] != 7.7 || 
        b[7] != 8.8 || b[8] != 9.9){ err("operator* test (r-value, l-value) [src elements]"); }
		if(res.datasize() != 9)                            { err("operator* test (r-value, l-value) [datasize]");         }
		comp_matrix(ref,res,"operator* test (r-value, l-value)");
	}
	//Test operator* (l-value, r-value)
	{
		Matrix<double> a{3,{3.1, 5.2, 9.3,4.2,5.3,6.4,7.5,8.6,9.7}};
		Matrix<double> b{3,{1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9}};
		Matrix<double> ref{3,{97.9,117.26,136.62,77.22,94.71,112.2,120.78,149.16,177.54}};
		Matrix<double> res = a * std::move(b);
		if(a.datasize() != 9)                              { err("operator* test (l-value, r-value) [src datasize1]");    }
		if(b.datasize() != 0)                              { err("operator* test (l-value, r-value) [src datasize2]");	}
		if(b.Nsize() != 0)                              { err("operator* test (l-value, r-value) [src Nsize2]");	}
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 4.2 || a[4] != 5.3 || a[5] != 6.4 || a[6] != 7.5 || 
        a[7] != 8.6 || a[8] != 9.7)  { err("operator* test (l-value, l-value) [src elements]"); }
		if(res.datasize() != 9)                            { err("operator* test (l-value, r-value) [datasize]");         }
		comp_matrix(ref,res,"operator* test (l-value, r-value)");
	}
	//Test operator* (r-value, r-value)
	{
		Matrix<double> a{3,{3.1, 5.2, 9.3,4.2,5.3,6.4,7.5,8.6,9.7}};
		Matrix<double> b{3,{1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9}};
		Matrix<double> ref{3,{97.9,117.26,136.62,77.22,94.71,112.2,120.78,149.16,177.54}};
		Matrix<double> res = std::move(a) * std::move(b);
		if(a.datasize() != 0)                              { err("operator* test (r-value, r-value) [src datasize1]");    }
		if(a.Nsize() != 0)                              { err("operator* test (r-value, r-value) [src Nsize1]");    }
		if(res.datasize() != 9)                            { err("operator* test (r-value, r-value) [datasize]");         }
		comp_matrix(ref,res,"operator* test (r-value, r-value)");
	}
}
