/////////////////////////////////////////////////////
// Filename: quaternion.h
// Author: Subhojit Basu 
// License : MIT License
// Creation Date : 8 Feb 2023
/////////////////////////////////////////////////////

#include "quaternion.h"

using namespace std;

 quaternion getQDelta(double deltaT, vector<double, 3> omega)
{
    quaternion r;

    double omegaMag = omega.norm();

    r.mag = 1;
    r.phi = deltaT*omegaMag;

    if(omegaMag != 0)
        r.n = omega/omegaMag;
    else 
        r.n.set(0,0,0);
    r.form = POLAR;

    return r;
}

 quaternion getQCorrected(const quaternion& Qtilt, const quaternion& Qgyro, double alpha)
{
    quaternion qAlpha = Qtilt;

    qAlpha.phi = (1 - alpha) * qAlpha.phi;
    
    return qAlpha*Qgyro;
}

 quaternion getTilt(const quaternion& q){

    quaternion q0 = q;

    vector<double,3> u = q0.normalise();

    double *v = u.get();

    double den = sqrt(v[0]*v[0] + v[2]*v[2]);

    q0.mag = 1;
    q0.phi = acos(v[1]);
    q0.n.set(-v[2]/den, 0, v[0]/den);

    q0.form = POLAR;

    return q0;
    
}

 quaternion getNextQ(const quaternion& Qt, const vector<double,3>& a, const vector<double,3>& omega,double deltaT){

    quaternion qt = Qt;
    quaternion Qdelta = getQDelta(deltaT,omega);

    qt.print();
    Qdelta.print();

    quaternion Qgyro = qt*Qdelta;
    Qgyro.print();

    quaternion Qbody,Qtilt;

    Qbody.setNormal(0,a);

    Qtilt = getTilt(Qbody);
    Qtilt.print();

    quaternion Qcorr = getQCorrected(Qtilt,Qgyro,0.8);

    Qcorr.print();

    quaternion q0 = Qcorr.rotateBy(Qgyro);

    quaternion q1 = q0.rotateBy(Qtilt);

    q1.print();

    return q1;

}

