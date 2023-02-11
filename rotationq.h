/////////////////////////////////////////////////////
// Filename: rotationq.h
// Author: Subhojit Basu 
// License : MIT License
// Creation Date : 8 Feb 2023
/////////////////////////////////////////////////////

#include "quaternion.h"

class rotationq: public quaternion
{
private:
    /* data */
public:
    rotationq();
    rotationq(double theta,vector<double,3> v);
    ~rotationq();
    quaternion rotateBy(rotationq Qr);
    quaternion getTilt();
    // omega are the gryo values
    // deltaT is the elapsed time since last
    rotationq getQDelta(double deltaT, vector<double,3> omega);
    //apply complementary filter on acc and gyro values
    // alpha between 0 and 1
    rotationq getQCorrected(rotationq QTilt,rotationq Qgyro,double alpha);
};

rotationq::rotationq()
{
    mag = 1;
    phi = 0;
    n.set(0,0,0);
    form = POLAR;
}
rotationq::rotationq(double theta, vector<double,3> v)
{
    mag = 1;
    phi = theta;
    n = v/sqrt(v.dotProduct(v));
    form = POLAR;
}

rotationq::~rotationq()
{
}

quaternion rotationq::rotateBy(rotationq Qr)
{
    quaternion q0 = *this;
    return Qr*q0*Qr.inverse();
}

rotationq rotationq::getQDelta(double deltaT, vector<double, 3> omega)
{
    rotationq r;

    double omegaMag = omega.norm();

    r.phi = deltaT*omegaMag;
    r.n = omega/omegaMag;

    return r;
}

rotationq rotationq::getQCorrected(rotationq Qtilt, rotationq Qgyro, double alpha)
{
    Qtilt.phi = (1 - alpha) * Qtilt.phi;
    return Qtilt*Qgyro;
}

quaternion rotationq:getTilt(){

    quaternion q0 = (*this).getNormal();
    quaternion q1;
    vector<double,3> v;
    double den = sqrt(q0.v[0]*q0.v[0] + q0.v[2]*q0.v[2])

    q1.mag = 1;
    q1.phi = acos(q0.v[1]);
    v.set(- V[2]/den, 0, v[0]/den);
    q1.n = v;

    return q1;
    
}