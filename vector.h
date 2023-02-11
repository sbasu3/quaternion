/////////////////////////////////////////////////////
// Filename: vector.h
// Author: Subhojit Basu 
// License : MIT License
// Creation Date : 1 July 2022
/////////////////////////////////////////////////////
#include <stdint.h>
#include <cassert>
#include <cmath>

template<typename T,unsigned len> class vector{
// len = 3 is default, kept for scaling later on

private:
	uint32_t length;
	T   vec[len];
public:
	vector<T,len>();
	vector<T,len>(const T& x,const  T& y,const T& z);
	vector<T,len>(const vector<T,len>& v );
	~vector<T,len>(void);
	void set(const T& x,const  T& y ,const  T& z);					// special for vector3
	T* get(void);
	vector<T,len> operator=(const vector<T,len>& v);
	bool operator==(const vector<T,len>& v);
	bool operator!=(const vector<T,len>& v);
	vector<T,len> operator+(const vector<T,len>& v);
	vector<T,len> operator-(const vector<T,len>& v);
	vector<T,len> operator*(const vector<T,len>& v);	// Cross product
	vector<T,len> operator*(const T num);				//multiplication by scalar
	vector<T,len> operator/(T num);
	T dotProduct(const vector<T,len>& v );
	T norm(void);
}; 
