#include <iostream>
#include "Matrix_parallel.h"

template<typename T, typename F, typename G>
void comp_matrix(Matrix<T> const& A, Matrix<F> const& B, G str){
	if(A.Nsize() != B.Nsize()){
		std::cout << "Matrix_parallel.h error in: " << str << "[N size]" << "\n";
		std::exit(-1);
	}
	if(A.datasize() != B.datasize()){
		std::cout << "Matrix_parallel.h error in: " << str << "[datasize]" << "\n";
		std::exit(-1);
	}
	for(int i = 0; i < A.Nsize()*A.Nsize(); ++i){
		if (A[i] - B[i] > 1e-13 ){
			std::cout << "Matrix_parallel.h error in: " << str << "[elements]" << "\n";
			std::exit(-1);
		}
	}
}
int main(int, char**) {
	auto err = [](auto str){ std::cout << "Matrix_parallel.h error in: " << str << "\n"; std::exit(-1); };
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
