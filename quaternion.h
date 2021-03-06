/////////////////////////////////////////////////////
// Filename: quaternion.h
// Author: Subhojit Basu 
// License : MIT License
// Creation Date : 2 July 2022
/////////////////////////////////////////////////////

#include "vector.cpp"

enum QuatType { NORMAL = 0 , POLAR = 1};

class quaternion{

private:
	
	QuatType form;
	//simple form
	double w;
	vector<double,3> v;
	//polar form
	double mag;
	double phi;
	vector<double,3> n;

public:
	//constructors and destructors
	quaternion();
	quaternion(const double& w, const vector<double,3>& v);
	quaternion(const double& mag, const double& phi, const vector<double,3>& n);
	quaternion(const quaternion& q);
	~quaternion();

	//operators
	void setNormal(const double& w, const vector<double,3>& v);
	void setPolar(const double& mag, const double& phi, const vector<double,3>& n);
	quaternion getNormal(void);
	quaternion getPolar(void);
	quaternion operator=(const quaternion& q );
	bool operator==(const quaternion& q );
	bool operator!=(const quaternion& q );
	quaternion operator+(const quaternion& q);
	quaternion operator-(const quaternion& q);
	quaternion operator*(const quaternion& q);	
	quaternion operator*(const double& val);	
	quaternion operator/(const double& val);	
	double dotProduct(const quaternion& q );
	
	//Math functions
	double norm(void);
	quaternion conjugate(void);
	quaternion inverse(void);
	quaternion pow(const double& x);
	//friend quaternion exp(const quaternion& q);
	//friend quaternion log(const quaternion& q);
		

};
