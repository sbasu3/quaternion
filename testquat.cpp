/////////////////////////////////////////////////////
// Filename: testquat.cpp
// Author: Subhojit Basu [ subhojit.basu@gmail.com ]
// License : MIT License
// Creation Date : 13 Feb 2023
/////////////////////////////////////////////////////

#include "quaternion.h"
#include "mpu6050.h"
#include <time.h>

int main(void){

    quaternion q[10];
    vector<double,3> v;
    //test constructor
    quaternion q0(1,v);
    v.set(0,1,0);
    quaternion q1(0,v);

    //test Multiplication operator and assignment
    q[0] = q0*q1;

    //test print fn
    q[0].print();

    v.set(1,1,1);

    quaternion q3(1,v);
    //test conjugate and norm
    q[1] = q3*q3.conjugate();
 
    q[1].print();
    cout<<q[1].norm()<<endl;
    cout<<q3.norm()<<endl;

    //test normalise
    v.set(1,1,1);
    q[0].setNormal(1,v);

    v = q[0].normalise();

    v.print();

    //test getPolar and getNormal

    q[1].setNormal(0,v);

    q[1].print();

    q[2] = q[1].getPolar();

    q[2].print();

    q[3] = q[2].getNormal();

    q[3].print();

    //test pow and inverse

    q[4] = q[3].inverse();
    q[5] = q[4]*q[3];

    q[5].print(); 

    q[6] = q[1].pow(3);

    q[6].print();

    q[7] = q[2].pow(3);

    q[7].print();

    //test rotateby

    v.set(1,1,1);

    q[0].setNormal(1,v);

    v.set(0,0,0.3);

    q[1].setNormal(1,v);

    q[1] = q[1]/q[1].norm();

    q[2] = q[1].rotateBy(q[0]);

    q[2].print();

    q[2] = q[2].getPolar();

    q[2].print();

    //test getTilt
    v.set(1,0,1);
    q[2].setNormal(0,v);
    q[3] = getTilt(q[2]);

    q[3].print();

    q[2].rotateBy(q[3]);

    q[2].print();
    //imu test
    mpu6050 imu;
    clock_t start,end;
    clock_t delay = 20;        //50Hz

    v.set(0,0,0);
    q0.setNormal(1,v);
    
    q[0] = q0;

    while(1){
        start = clock();
        imu.read();
        //process
        q[1] = getNextQ(q[0],imu.getA(),imu.getW(),delay);
        q[1].print();
        q[0] = q[1];
        end = clock();
        while(end-start< delay)
            end = clock();
    }
}

