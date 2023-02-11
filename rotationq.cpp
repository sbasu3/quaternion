/////////////////////////////////////////////////////
// Filename: quaternion.h
// Author: Subhojit Basu 
// License : MIT License
// Creation Date : 8 Feb 2023
/////////////////////////////////////////////////////

#include "quaternion.h"



 quaternion getQDelta(double deltaT, vector<double, 3> omega)
{
    quaternion r;

    double omegaMag = omega.norm();

    r.mag = 1;
    r.phi = deltaT*omegaMag;
    r.n = omega/omegaMag;

    return r;
}

 quaternion getQCorrected(const quaternion& Qtilt, const quaternion& Qgyro, double alpha)
{
    quaternion qAlpha = Qtilt;

    qAlpha.phi = (1 - alpha) * qAlpha.phi;
    
    return qAlpha*Qgyro;
}

 quaternion getTilt(quaternion q){

    quaternion q0;

    vector<double,3> u = q.normalise();

    double den = sqrt(u.vec[0]*u.vec[0] + u.vec[2]*u.vec[2]);

    q0.mag = 1;
    q0.phi = acos(u.vec[1]);
    q0.n.set(-u.vec[2]/den, 0, u.vec[0]/den);

    return q0;
    
}

 quaternion getNextQ(const quaternion& Qt, const vector<double,3>& a, const vector<double,3>& omega,double deltaT){

    quaternion Qdelta = getQDelta(deltaT,omega);

    quaternion Qgyro = Qt*Qdelta;

    return Qgyro;

}

