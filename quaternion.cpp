/////////////////////////////////////////////////////
// Filename: quaternion.cpp
// Author: Subhojit Basu 
// License : MIT License
// Creation Date : 3 July 2022
/////////////////////////////////////////////////////
#include "quaternion.h"

quaternion::quaternion(){

	form = NORMAL;

	w = 0.0;

	mag = 0.0;
	phi = 0.0;
}

quaternion::quaternion(const double& w, const vector<double,3>& v){

	this->setNormal(w,v);
}

quaternion::quaternion(const double& mag, const double& phi, const vector<double,3>& n){

	this->setPolar(mag,phi,n);
}

quaternion::quaternion(const quaternion& q){

	form = q.form;

	w = q.w;
	v = q.v;

	mag = q.mag;
	phi = q.phi;
	n = q.n;


}

quaternion::~quaternion(){

}

void quaternion::setNormal(const double& w, const vector<double,3>& v){


	form = NORMAL;

	this->w = w;
	this->v = v;

}

void quaternion::setPolar(const double& mag, const double& phi, const vector<double,3>& n){

	form = POLAR;

	this->mag = mag;
	this->phi = phi;
	this->n = n;

}

quaternion quaternion::getNormal(void){

	if(form == NORMAL)
		return *this;
	else{
			w = mag*cos(phi);
			v = n * mag * sin(phi);	
			form = NORMAL;

			return *this;
	}
}

quaternion quaternion::getPolar(void){

	if(form != POLAR){
		mag = sqrt(w*w + v.dotProduct(v));
		phi = acos(w/mag);
		n = v/(mag*sin(phi));

		form = POLAR; 

	}

	return *this;

}

quaternion quaternion::operator=(const quaternion& q ){

	form = q.form;

	w = q.w;
	v = q.v;

	mag = q.mag;
	phi = q.phi;
	n = q.n;


}

bool quaternion::operator==(const quaternion& q ){

	if(q.form == NORMAL){
		if(this->form == NORMAL){
			return ( (w == q.w) && ( v == q.v) );
		}else{
			quaternion q0 = this->getNormal();
			return ( q == q0);
	}else{
		if(this->form == POLAR){
			return ( ( mag == q.mag) && ( phi == q.phi) && ( n = q.n ))
		}else{
			quaternion q0 = this->getPolar();
			return ( q == q0);
		}
	}
}

bool quaternion::operator!=(const quaternion& q ){

	return !( *this == q );
}

quaternion quaternion::operator+(const quaternion& q){

	quaternion q0,q1;

	q1 = q.getNormal();
	q0 = this->getNormal();


	w = q0.w + q1.w;
	v = q0.v + q1.v;
	
	form = NORMAL;

}

quaternion quaternion::operator-(const quaternion& q){

	quaternion q0,q1;

	q1 = q.getNormal();
	q0 = this->getNormal();


	w = q0.w - q1.w;
	v = q0.v - q1.v;
	
	form = NORMAL;

}

quaternion quaternion::operator*(const quaternion& q){

	quaternion q0,q1;
	vector vec;


	q1 = q.getPolar();
	q0 = this->getPolar();


	mag = q0.mag * q1.mag;
	
	vec = q0.n * q0.phi + q1.n * q1.phi;
	phi = sqrt(vec.dotProduct(vec));
	n = vec/phi;
	

	
	form = POLAR;

}

quaternion operator*(const double& val){

	if(form == NORMAL){
		w = w * val;
		v = v * val;
	}else{
		mag = mag * val;
	}

	return *this;
}	

quaternion operator/(const double& val){

	if(form == NORMAL){
		w = w / val;
		v = v / val;
	}else{
		mag = mag / val;
	}

	return *this;
}	

double dotProduct(const quaternion& q ){

	quaternion q0,q1;

	q0 = this->getNormal();
	q1 = q.getNormal();

	return q0.w * q1.w + q0.v.dotProduct(q1.v);



}

double quaternion::norm(void){

	return sqrt(this->dotProduct(*this));
}

quaternion quaternion::conjugate(void){

	quaternion q;


	if(this->form == NORMAL){

		q.w = this->w;
		q.v = this->v * (-1.0);
		q.form = NORMAL; 
	}else{
		q.mag = 1/(this->mag);
		q.phi = this->phi ;
		q.n = this->n * (-1.0);
		
		form = POLAR;
	}

	return q;

}

quaternion quaternion::inverse(void){

	return this->conjugate()/this->norm();

}

quaternion quaternion::pow(const double& x){
	
	quaternion q0;


	q0 = this->getPolar();

	q0.mag = pow(q0.mag,x);

	q0.phi = q0.phi * x;

	return q0;

}






















