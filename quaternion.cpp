/////////////////////////////////////////////////////
// Filename: quaternion.cpp
// Author: Subhojit Basu 
// License : MIT License
// Creation Date : 3 July 2022
/////////////////////////////////////////////////////
#include "quaternion.h"

quaternion::quaternion(){

	form = NORMAL;

	//NORMAL
	w = 0.0;

	//POLAR
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

	if(form == NORMAL){
		w = q.w;
		v = q.v;
	}else{
		mag = q.mag;
		phi = q.phi;
		n = q.n;
	}

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
			quaternion q0;
			q0.w = mag*std::cos(phi);
			q0.v = n * mag * sin(phi);	
			q0.form = NORMAL;

			return q0;
	}
}

quaternion quaternion::getPolar(void){

	if(form != POLAR){
		quaternion q;
		//mag = sqrt(w*w + v.dotProduct(v));
		q.mag = this->norm();
		q.phi = acos(w/q.mag);

		if(q.phi){
			q.n = v/(q.mag*sin(q.phi));
		}else{
			q.n.set(0,0,0);
		}
		q.form = POLAR;

		return q; 

	}else
		return *this;

}

quaternion quaternion::operator=(const quaternion& q ){

	form = q.form;

	if(form == NORMAL){
		w = q.w;
		v = q.v;
	}else{
		mag = q.mag;
		phi = q.phi - ceil(q.phi/_2PI) * _2PI;
		n = q.n;
	}

	return *this;
}

bool quaternion::operator==(const quaternion& q ){

	if(q.form == NORMAL){
		if(this->form == NORMAL){
			return ( (w == q.w) && ( v == q.v) );
		}else{
			quaternion q0 = this->getNormal();
			return ( q0 == q);
		}
	}else{
		if(this->form == POLAR){
			return ( ( mag == q.mag) && ( phi == q.phi) && ( n == q.n ));
		}else{
			quaternion q0 = this->getPolar();
			return ( q0 == q);
		}
	}
}

/// @brief 
/// @param q 
/// @return 
bool quaternion::operator!=(const quaternion& q ){

	return !( *this == q );
}

quaternion quaternion::operator+(const quaternion& q){

	quaternion q0,q1;

	q1 = q;
	q1 = q1.getNormal();
	q0 = this->getNormal();


	q0.w = q0.w + q1.w;
	q0.v = q0.v + q1.v;
	
	q0.form = NORMAL;

	return q0;
}

quaternion quaternion::operator-(const quaternion& q){

	quaternion q0,q1;
	q1 = q;

	q1 = q1.getNormal();
	q0 = this->getNormal();


	q0.w = q0.w - q1.w;
	q0.v = q0.v - q1.v;
	
	q0.form = NORMAL;

	return q0;
}

quaternion quaternion::operator*(const quaternion& q){

	quaternion q0,q1;
	//vector vec;
	q1 = q;
	if(form == POLAR){


		q1 = q1.getPolar();

		q0.mag = mag * q1.mag;
	
		q0.n = n * phi + q1.n * q1.phi;
		q0.phi = q0.n.norm();
		q0.n = q0.n/q0.phi;

		q0.form = POLAR;
	}else{

		q1 = q1.getNormal();

		q0.w = w*q1.w - v.dotProduct(q1.v);
		q0.v = q1.v*w + v*q1.w + v*q1.v;

		q0.form = NORMAL;
	}
	
	return q0;

}

quaternion quaternion::operator*(const double& val){

	quaternion q;

	if(form == NORMAL){
		q.w = w * val;
		q.v = v * val;
		q.form = NORMAL;
	}else{
		q.mag = mag * val;
		q.phi = phi;
		q.n = n;
		q.form = POLAR;
	}

	return q;
}	

quaternion quaternion::operator/(const double & val){

	quaternion q;

	if(form == NORMAL){
		q.w = w / val;
		q.v = v / val;
		q.form = NORMAL;
	}else{

		q.mag = mag / val;
		q.phi = phi;
		q.n = n;
		q.form = POLAR;
	}

	return q;
}	


double quaternion::norm(void){

	if(form == NORMAL){
		return sqrt(w*w +v.norm()*v.norm());
	}else
		return mag;
	
}

quaternion quaternion::conjugate(void){

	quaternion q;


	if(this->form == NORMAL){

		q.w = this->w;
		q.v = this->v * (-1.0);
		q.form = NORMAL; 
	}else{
		q.mag = this->mag;
		q.phi = -this->phi ;
		q.n = this->n;
		
		q.form = POLAR;
	}

	return q;

}

quaternion quaternion::inverse(void){

	return (this->conjugate() / (this->norm()*this->norm()));

}

quaternion quaternion::pow(const double& x){
	
	quaternion q0;


	q0 = this->getPolar();

	q0.mag = std::pow(q0.mag,x);

	q0.phi = q0.phi * x;

	return q0;

}
vector<double,3> quaternion::normalise(void){

	vector<double,3> x;

	if (form == NORMAL){
		x = v/v.norm();
	}else{
		//maybe division is not required
		x = n/n.norm();
	}


	return x;

}

 quaternion quaternion::rotateBy(quaternion Qr)
{
    quaternion q0 = *this;
    return Qr*q0*Qr.conjugate();
}

void quaternion::print(){

	//double *u;

	cout<<"form:"<<form<<endl;

	if(form==NORMAL){
		//u = v.get();
		cout<<"s:"<<w<<endl;
		v.print();
	}else{
		//u = n.get();
		cout<<"mag:"<<mag<<"phi:"<<phi<<endl;
		n.print();
	}
}


















