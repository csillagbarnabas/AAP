#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <initializer_list>
#include <cmath>
#include <ostream>

struct Idx1{};
struct Idx2{};

namespace detail
{
	template<typename V1, typename V2, typename F>
	void transform_matrix1(V1 const& v1, V2& v2, F f)
	{
		std::transform(v1.cbegin(), v1.cend(), v2.begin(), f);
	}

	template<typename V1, typename V2, typename V3, typename F>
	void transform_matrix2(V1 const& v1, V2 const& v2, V3& v3, F f)
	{
		std::transform(v1.cbegin(), v1.cend(), v2.cbegin(), v3.begin(), f);
	}
}

inline auto add = [](auto const& x, auto const& y){ return x + y; };
inline auto sub = [](auto const& x, auto const& y){ return x - y; };

template<typename T>
class Matrix{
    public: 
		int N;
    	std::vector<T> data;
    	T&  operator()(int i, int j)
    	{ return data[N*i+j]; }
    	T const& operator()(int i, int j) const
    	{ return data[N*i+j]; }
		T&  operator[](int i)
    	{ return data[i]; }
    	T const& operator[](int i) const
    	{ return data[i]; }
	Matrix() = default;
	Matrix( Matrix const& ) = default;
	Matrix( Matrix && ) = default;
	Matrix<T>& operator=(Matrix const&) = default;
	Matrix<T>& operator=(Matrix &&) = default;
	template<typename F>
	Matrix(Idx1, F f,int M){
		data.resize(M*M);
		N = M;
		for(int i=0; i<M*M; ++i){
			data[i] = f(i); 
		}
	}
	template<typename F>
	Matrix(Idx2, F f, int M){
		data.resize(M*M);
		N = M;
		for(int i=0; i<M; ++i){
			for( int j=0; j < M; ++j){
				data[i*M+j] = f(i,j);
			}
		}
	}
	Matrix( int n, std::vector<T> x ) : N(n), data(x){};
    Matrix<T>& operator+= (Matrix<T> const& cpy)
	{
		detail::transform_matrix2(data, cpy.data, data, add);
		return *this;
	}
	Matrix<T>& operator-= (Matrix<T> const& cpy)
	{
		detail::transform_matrix2(data, cpy.data, data, sub);
		return *this;
	}
	Matrix<T>& operator*= (T const& scl)
	{
		detail::transform_matrix1(data, data, [=](T const& x){ return x * scl;} );
		return *this;
	}
	Matrix<T>& operator/= (T const& scl)
	{
		detail::transform_matrix1(data, data, [=](T const& x){ return x / scl;} );
		return *this;
	}
	int datasize()const{
		return static_cast<int>(data.size());
		}
	auto begin()
	{
		return data.begin();
	}

	auto cbegin() const
	{
		return data.cbegin();
	}

	auto end()
	{
		return data.end();
	}

	auto cend() const
	{
		return data.cend();
	}
    };
template<typename T>
Matrix<T> operator+(Matrix<T> const& A, Matrix<T> const& B)
{
	return Matrix<T>(Idx1{}, [&](auto i){ return A[i] + B[i]; },A.N);
}
template<typename T>
Matrix<T> && operator+( Matrix<T> && m1, Matrix<T> const& m2 )
{
	detail::transform_matrix2(m1, m2, m1, add);
	return std::move(m1);
}
template<typename T>
Matrix<T> && operator+( Matrix<T> const& m1, Matrix<T> && m2 )
{
	detail::transform_matrix2(m1, m2, m2, add);
	return std::move(m2);
}
template<typename T>
Matrix<T> && operator+( Matrix<T> && m1, Matrix<T> && m2 )
{
	detail::transform_matrix2(m1, m2, m1, add);
	return std::move(m1);
}
//--
template<typename T>
Matrix<T> operator-(Matrix<T> const& A, Matrix<T> const& B)
{
	return Matrix<T>(Idx1{}, [&](auto i){ return A[i] - B[i]; },A.N);
}
template<typename T>
Matrix<T> && operator-( Matrix<T> && m1, Matrix<T> const& m2 )
{
	detail::transform_matrix2(m1, m2, m1, sub);
	return std::move(m1);
}
template<typename T>
Matrix<T> && operator-( Matrix<T> const& m1, Matrix<T> && m2 )
{
	detail::transform_matrix2(m1, m2, m2, sub);
	return std::move(m2);
}
template<typename T>
Matrix<T> && operator-( Matrix<T> && m1, Matrix<T> && m2 )
{
	detail::transform_matrix2(m1, m2, m1, sub);
	return std::move(m1);
}
template<typename T>
Matrix<T> operator*(Matrix<T> && m, T const& scl)
{
	detail::transform_matrix1(m, m, [=](T const& x){ return x * scl; });
	return std::move(m);
}
template<typename T>
Matrix<T> operator*(Matrix<T> const& A, T const& s)
{
	return Matrix<T>(Idx1{}, [&](auto i){ return A[i] * s; },A.N);
}
template<typename T>
Matrix<T> operator*(T const& s,Matrix<T> const& A)
{
	return Matrix<T>(Idx1{}, [&](auto i){ return s * A[i]; },A.N);
}
template<typename T>
Matrix<T> operator*(T const& scl,Matrix<T> && m)
{
	detail::transform_matrix1(m, m, [=](T const& x){ return scl * x; });
	return std::move(m);
}
template<typename T>
Matrix<T> operator/(Matrix<T> const& A, T const& s)
{
	return Matrix<T>(Idx1{}, [&](auto i){ return A[i] / s; },A.N);
}
template<typename T>
Matrix<T> operator/(Matrix<T> && m, T const& scl)
{
	detail::transform_matrix1(m, m, [=](T const& x){ return x / scl; });
	return std::move(m);
}
template<typename T>
Matrix<T> operator*(Matrix<T> const& A, Matrix<T> const& B)
{
	auto N = A.N;
	return Matrix<T>(Idx2{}, [&](int i, int j)
	{
	T sum = 0.0;
	for(int k = 0; k<N; ++k){ sum += A(i, k) * B(k, j); }
	return sum;
	}, N);
}
template<typename T>
Matrix<T> operator*(Matrix<T> && A, Matrix<T> const& B)
{
	for(int i=0; i<B.N; i++){
		std::vector<T> v(0);
		v.resize(A.datasize());
		for(int j=0; j<B.N; j++){
			for(int k=0; k<B.N; k++){
				v[j] += A(i,k) * B(k,j);
			}
		}
		for(int j=0; j<A.N; j++){
			A(i,j) = v[j];
		}
	}
	return std::move(A);
}
template<typename T>
Matrix<T> operator*(Matrix<T> const& A, Matrix<T> && B)
{
	for(int j=0; j<A.N; j++){
		std::vector<T> v(0);
		v.resize(A.datasize());
		for(int i=0; i<A.N; i++){
			for(int k=0; k<A.N; k++){
				v[i] += A(j,k) * B(k,i);
			}
		}
		for(int i=0; i<B.N; i++){
			B(j,i) = v[i];
		}
	}
	return std::move(B);
}
template<typename T>
Matrix<T> operator*(Matrix<T> && A, Matrix<T> && B)
{
	for(int i=0; i<B.N; i++){
		std::vector<T> v(0);
		v.resize(A.datasize());
		for(int j=0; j<A.N; j++){
			for(int k=0; k<A.N; k++){
				v[j] += A(i,k) * B(k,j);
			}
		}
		for(int j=0; j<A.N; j++){
			A(i,j) = v[j];
		}
	}
	return std::move(A);
}
template<typename T>
std::ostream& operator<< (std::ostream& o, Matrix<T> const& m)
{
	for(int j = 0; j < m.N; ++j){
		for(int i=0; i<m.N; ++i)
		{
			o << m.data[j*m.N+i] << "   ";
		}
		o << "\n";
	}
	return o;
}
