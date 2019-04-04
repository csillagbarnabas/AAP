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
	Matrix(Idx1, F f, int N){
		data.resize(N);
		for(int i=0; i<N; ++i){
			data[i] = f(i); 
		}
	}
	template<typename F>
	Matrix(Idx2, F f, int N){
		data.resize(N);
		for(int i=0; i<N; ++i){
			for( int j=0; j < N; ++j){
				data[i*N+j] = f(i,j);
			}
		}
	}

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
Matrix<T> operator+( Matrix<T> const& m1, Matrix<T> const& m2 )
{
	Matrix<T> result; result.data.resize(m1.datasize());
	detail::transform_matrix2(m1, m2, result, add);
	return result;
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
Matrix<T> operator-( Matrix<T> const& m1, Matrix<T> const& m2 )
{
	Matrix<T> result; 
	result.data.resize(m1.datasize());
	result.N = m1.N;
	detail::transform_matrix2(m1, m2, result, sub);
	return result;
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
Matrix<T> operator*(Matrix<T> const& m, T const& scl)
{
	Matrix<T> result; result.data.resize(m.datasize());
	detail::transform_matrix1(m, result, [=](T const& x){ return x * scl; });
	return result;
}
template<typename T>
Matrix<T> operator*(Matrix<T> && m, T const& scl)
{
	detail::transform_matrix1(m, m, [=](T const& x){ return x * scl; });
	return std::move(m);
}
template<typename T>
Matrix<T> operator*(T const& scl,Matrix<T> const& m)
{
	Matrix<T> result; result.data.resize(m.datasize());
	detail::transform_matrix1(m, result, [=](T const& x){ return scl * x; });
	return result;
}
template<typename T>
Matrix<T> operator*(T const& scl,Matrix<T> && m)
{
	detail::transform_matrix1(m, m, [=](T const& x){ return scl * x; });
	return std::move(m);
}
template<typename T>
Matrix<T> operator/(Matrix<T> const& m, T const& scl)
{
	Matrix<T> result; result.data.resize(m.datasize());
	detail::transform_matrix1(m, result, [=](T const& x){ return x / scl; });
	return result;
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
	Matrix<T> V = A;
	for(int i=0; i<A.N; i++){
		for(int j=0; j<A.N; j++){
			V(i,j) = 0.0;
			for(int k=0; k<A.N; k++){
				V(i,j) += A(i,k) * B(k,j);
			}
		}
	}
	return V;
}
template<typename T>
Matrix<T> operator*(Matrix<T> && A, Matrix<T> const& B)
{
	Matrix<T> V = B;
	for(int i=0; i<B.N; i++){
		for(int j=0; j<B.N; j++){
			V(i,j) = 0.0;
			for(int k=0; k<B.N; k++){
				V(i,j) += A(i,k) * B(k,j);
			}
		}
	}
	return V;
}
template<typename T>
Matrix<T> operator*(Matrix<T> const& A, Matrix<T> && B)
{
	Matrix<T> V = A;
	for(int i=0; i<A.N; i++){
		for(int j=0; j<A.N; j++){
			V(i,j) = 0.0;
			for(int k=0; k<A.N; k++){
				V(i,j) += A(i,k) * B(k,j);
			}
		}
	}
	return V;
}
template<typename T>
Matrix<T> operator*(Matrix<T> && A, Matrix<T> && B)
{
	Matrix<T> V = A;
	for(int i=0; i<A.N; i++){
		for(int j=0; j<A.N; j++){
			V(i,j) = 0.0;
			for(int k=0; k<A.N; k++){
				V(i,j) += A(i,k) * B(k,j);
			}
		}
	}
	return std::move(V);
}
template<typename T>
std::ostream& operator<< (std::ostream& o, Matrix<T> const& m)
{
	if( m.N > 0 )
	{
		for(int j = 0; j < m.N; ++j){
			for(int i=0; i<m.N; ++i)
			{
				o << m.data[j*m.N+i] << "   ";
			}
			o << "\n";
		}
	}
	return o;
}