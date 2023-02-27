/////////////////////////////////////////////////////
// Filename: vector.h
// Author: Subhojit Basu 
// License : MIT License
// Creation Date : 1 July 2022
/////////////////////////////////////////////////////
#ifndef __VECTOR
#define __VECTOR

#include <stdint.h>
#include <cassert>
#include <cmath>
#include<iostream>

using namespace std;

template<typename T> class vector{


private:
	uint32_t length;
	T   *vec;
public:
	vector<T>();
	vector<T>(unsigned int n);
	//vector<T,len>(const T& x,const  T& y,const T& z);
	vector<T>(const vector<T>& v );
	~vector<T>(void);
	void reSize(unsigned int n);
	void set(const T& x,const  T& y ,const  T& z);					// special for vector3
	T* get(void);
	void setAll(T num);
	vector<T> operator=(const vector<T>& v);
	bool operator==(const vector<T>& v);
	bool operator!=(const vector<T>& v);
	T &operator[](unsigned int i);
	vector<T> operator+(const vector<T>& v);
	vector<T> operator-(const vector<T>& v);
	vector<T> operator*(const vector<T>& v);	// Cross product
	vector<T> operator*(const T num);				//multiplication by scalar
	vector<double> operator/(T num);
	T shiftRight(T num);
	T shiftLeft(T num);
	void push( T num);									//stack ops: push to beginning and pop from end
	T pop(void);

	T dotProduct(const vector<T>& v );
	T norm(void);

	void print(void);
}; 

#endif