/////////////////////////////////////////////////////
// Filename: vector.cpp
// Author: Subhojit Basu 
// License : MIT License
// Creation Date : 1 July 2022
/////////////////////////////////////////////////////
#include"vector.h"

template <typename T , unsigned len> vector<T,len>::vector(){

	length = 3;
	set(0,0,0);

}

template <typename T , unsigned len> vector<T,len>::vector(const T &x ,const T &y,const T &z){

	assert(len == 3 );
	set(x,y,z);
}

template <typename T , unsigned len> vector<T,len>::vector(const vector<T,len>& v ){

	uint32_t i = 0;

	length = v.length;

	for(; i < v.length; i++)
		vec[i] = v.vec[i];

}

template <typename T , unsigned len> vector<T,len>::~vector(void){

}

template <typename T , unsigned len> void vector<T,len>::set(const T& x,const  T& y ,const T& z){

	length = 3;

	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
}// special for vector

template <typename T , unsigned len> T* vector<T,len>::get(void){

	return vec;
}

template <typename T , unsigned len> bool vector<T,len>::operator==(const vector<T,len>& v){
	uint32_t i;
	bool flag = true;

	for( i  = 0; i < this->length; i++)
		if( vec[i] != v.vec[i]){
			flag = false;
			break; 
		}

	return flag;
}

template <typename T , unsigned len> bool vector<T,len>::operator!=(const vector<T,len>& v){

	return !( *this == v);
}

template <typename T , unsigned len> vector<T,len> vector<T,len>::operator+(const vector<T,len>& v){

	vector<T,len> tmp;
	uint32_t i;

	for(i = 0; i < this->length ; i++){
		tmp.vec[i] = this->vec[i] + v.vec[i];
	} 

	return tmp;
}

template <typename T , unsigned len> vector<T,len> vector<T,len>::operator-(const vector<T,len>& v){
	vector<T,len> tmp;
	uint32_t i;

	for(i = 0; i < this->length ; i++){
		tmp.vec[i] = this->vec[i] - v.vec[i];
	} 

	return tmp;

}


template <typename T , unsigned len> vector<T,len> vector<T,len>::operator*(const vector<T,len>& v){
// Cross product defined for vector 3
// i *j = k , j * k = i , k * i = j , i *j *K = -1
	assert( len ==  3 );
	vector<T,len> tmp;

	tmp.vec[0] = vec[1] * v.vec[2] - v.vec[1] * vec[2];
	tmp.vec[1] = vec[0] * v.vec[2] - v.vec[0] * vec[2];
	tmp.vec[2] = vec[0] * v.vec[1] - v.vec[0] * vec[1];


	return tmp;
} 

template <typename T , unsigned len> T vector<T,len>::dotProduct(const vector<T,len>& v ){

	T val = 0;
	uint32_t i;

	for(i = 0; i < this->length ; i++){
		val += vec[i] * v.vec[i];
	} 

	return val;

}

template <typename T , unsigned len> vector<T,len> vector<T,len>::operator=(const vector<T,len>& v){

	uint32_t i;

	length = v.length;

	for(i = 0; i < this->length ; i++){
		vec[i] = v.vec[i];
	} 

	return *this;

}

template <typename T , unsigned len>  double vector<T,len>::norm(){

	return sqrt(v.dotProduct(v));
}
	

