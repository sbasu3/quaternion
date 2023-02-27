/////////////////////////////////////////////////////
// Filename: vector.cpp
// Author: Subhojit Basu 
// License : MIT License
// Creation Date : 1 July 2022
/////////////////////////////////////////////////////
#include"vector.h"
template <typename T > vector<T>::vector(){
	length = 0;
	vec = NULL;
}

template <typename T > vector<T>::vector(unsigned int n){

	length = n;
	vec = new T[n];
	setAll(0);
}

template<typename T> vector<T>::~vector(){
	delete[] vec;
}
/*
template <typename T> vector<T>::vector(const T &x ,const T &y,const T &z){

	assert(length == 3 );
	set(x,y,z);
}
*/
template<typename T> void vector<T>::reSize(unsigned int n){
	delete[] vec;
	length = n;
	vec = new T[n];
	setAll(0);
}
template <typename T> void vector<T>::setAll(T num){
	for(int i = 0 ; i < length; i++)
		vec[i] = num;
}

template <typename T> vector<T>::vector(const vector<T>& v ){

	uint32_t i = 0;

	length = v.length;
	vec = new T[length];

	for(; i < v.length; i++)
		vec[i] = v.vec[i];

}

template <typename T> void vector<T>::set(const T& x,const  T& y ,const T& z){

	length = 3;

	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
}// special for vector

template <typename T> T* vector<T>::get(void){

	return vec;
}
template<typename T> T &vector<T>::operator[](unsigned int i){
	assert( i < length);
	return vec[i];
}

template <typename T> bool vector<T>::operator==(const vector<T>& v){
	uint32_t i;
	bool flag = true;

	for( i  = 0; i < this->length; i++)
		if( vec[i] != v.vec[i]){
			flag = false;
			break; 
		}

	return flag;
}

template <typename T> bool vector<T>::operator!=(const vector<T>& v){

	return !( *this == v);
}

template <typename T> vector<T> vector<T>::operator+(const vector<T>& v){

	vector<T> tmp;
	uint32_t i;

	for(i = 0; i < this->length ; i++){
		tmp.vec[i] = this->vec[i] + v.vec[i];
	} 

	return tmp;
}

template <typename T> vector<T> vector<T>::operator-(const vector<T>& v){
	vector<T> tmp;
	uint32_t i;

	for(i = 0; i < this->length ; i++){
		tmp.vec[i] = this->vec[i] - v.vec[i];
	} 

	return tmp;

}


template <typename T> vector<T> vector<T>::operator*(const vector<T>& v){
// Cross product defined for vector 3
// i *j = k , j * k = i , k * i = j , i *j *k = -1
	assert( length ==  3 );
	vector<T> tmp;

	tmp.vec[0] = vec[1] * v.vec[2] - v.vec[1] * vec[2];
	tmp.vec[1] = vec[0] * v.vec[2] - v.vec[0] * vec[2];
	tmp.vec[2] = vec[0] * v.vec[1] - v.vec[0] * vec[1];


	return tmp;
} 

template <typename T> T vector<T>::dotProduct(const vector<T>& v ){

	T val = 0;
	uint32_t i;
	assert(v.length == this->length);

	for(i = 0; i < this->length ; i++){
		val += vec[i] * v.vec[i];
	} 

	return val;

}

template <typename T> vector<T> vector<T>::operator=(const vector<T>& v){

	uint32_t i;

	length = v.length;
	this->reSize(length);

	for(i = 0; i < this->length ; i++){
		vec[i] = v.vec[i];
	} 

	return *this;

}

template <typename T>  T vector<T>::norm(){

	vector<double> v = *this;

	return (T) sqrt(v.dotProduct(v));
}
	
template <typename T> vector<T> vector<T>::operator*(const T num){				//multiplication by scalar
	vector<T> a;
	uint32_t i;

	for(i=0 ; i < this->length; i++)
		a.vec[i] = num * vec[i];

	a.length = length;
	return a; 
}
template <typename T> vector<double> vector<T>::operator/(T num){
	vector<T> a;
	uint32_t i;
	assert( num != 0 );
	for(i=0 ; i < this->length; i++)
		a.vec[i] = vec[i]/num;

	a.length = length;
	return a; 
}

template<typename T> T vector<T>::shiftRight(T num)
{
	int ret = vec[length - 1];

	for(int i = length - 1; i > 0; i--)
		vec[i] = vec[i - 1];
	vec[0] = num;

	return ret;
}
template<typename T> T vector<T>::shiftLeft(T num)
{
	int ret = vec[0];

	for(int i = 0; i < length - 1; i++)
		vec[i] = vec[i + 1];
	vec[length - 1] = num;

	return ret;
}
template<typename T> void vector<T>::push( T num)									//Queue ops: push to beginning and pop from end
{
	this->shiftRight(num);
}

template<typename T> T vector<T>::pop(void)
{

}

template <typename T> void vector<T>::print(void){

	uint32_t i = 0;

	for (;i< this->length;++i){
		cout<<i<<":"<<vec[i]<<endl;
	}
}

