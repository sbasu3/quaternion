/////////////////////////////////////////////////////
// Filename: quaternion.h
// Author: Subhojit Basu 
// License : MIT License
// Creation Date : 2 July 2022
/////////////////////////////////////////////////////
#include<iostream>
#include "vector.cpp"

#define _PI 3.14159
#define _2PI 2*_PI
#define DEG2RAD(x) ((x)*_PI)/180


enum QuatType { NORMAL = 0 , POLAR = 1};

using namespace std;

class quaternion{

protected:
	
	QuatType form;
	//simple form
	double w;
	vector<double> v;
	//polar form
	double mag;
	double phi;
	vector<double> n;

public:
	//constructors and destructors
	quaternion();
	quaternion(const double& w, const vector<double>& v);
	quaternion(const double& mag, const double& phi, const vector<double>& n);
	quaternion(const quaternion& q);
	~quaternion();

	//operators
	void setNormal(const double& w, const vector<double>& v);
	void setPolar(const double& mag, const double& phi, const vector<double>& n);
	quaternion getNormal(void);
	quaternion getPolar(void);
	vector<double> getVec(void);
	quaternion operator=(const quaternion& q );
	bool operator==(const quaternion& q );
	bool operator!=(const quaternion& q );
	quaternion operator+(const quaternion& q);
	quaternion operator-(const quaternion& q);
	//Quaternion multiplication, non-commutative
	quaternion operator*(const quaternion& q);	
	quaternion operator*(const double& val);	
	quaternion operator/(const double& val);
	// doent exist	
	//double dotProduct(const quaternion& q );
	
	//Math functions
	double norm(void);
	quaternion conjugate(void);
	quaternion inverse(void);
	quaternion pow(const double& x);

	//only normalises vector component and returns it
	quaternion normalise(void);
	//will add when I require it
	//friend quaternion exp(const quaternion& q);
	//friend quaternion log(const quaternion& q);
	quaternion rotateBy(quaternion Qr);

	void print(void);
	//friend quaternion rotateBy(quaternion Qr);
    friend quaternion getTilt();
    // omega are the gryo values
    // deltaT is the elapsed time since last
    friend quaternion getQDelta(double deltaT, vector<double> omega);
    friend quaternion getTilt(const quaternion& q);
    //apply complementary filter on acc and gyro values
    // alpha between 0 and 1
    friend quaternion getQCorrected(const quaternion& QTilt,const quaternion& Qgyro,double alpha);
    friend quaternion getNextQ(const quaternion& Qt, const vector<double>& a, const vector<double>& omega,double deltaT);
	friend quaternion scalePhi(quaternion q);	

};

double  scale(double x);
