/*
 Copyright (C) 2014  Cagdas Caglak cagdascaglak@gmail.com http://expcodes.blogspot.com.tr/

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "AllDevices.h"
#include "quaternion.h"
#include <time.h>

using namespace cacaosd_i2cport;
using namespace cacaosd_mpu6050;

int ctrl;

int main() {

    ctrl = 1;
    signal(SIGINT, signal_handler);

    I2cPort *i2c = new I2cPort(0x68, 2);
    i2c->openConnection();

    MPU6050 *mpu6050 = new MPU6050(i2c);
    mpu6050->initialize();

    float k = 16384;
    int16_t *accels = (int16_t *) calloc(3, sizeof(int16_t));
    int16_t *gyros = (int16_t *) calloc(3, sizeof(int16_t));
    vector<double,3> v,u;

    quaternion<double,3> q[4];

    clock_t start,end;
    clock_t delay = (clock_t) 20;        //50Hz

    v.set(0,0,0);
    q[0].setNormal(1,v);

    while (ctrl) {
        //std::cout << "MPU6050" << std::endl;

        start = clock();
        cout<<start;

        mpu6050->getAccelerations(accels);
        v.set((double) accels[0] / k , (double) accels[1] / k, (double) accels[2] / k );

        mpu6050->getAngularVelocities(gyros);
        u.set((double) gyros[0] / k , (double) gyros[1] / k, (double) gyros[2] / k );






            //process
            q[1] = getNextQ(q[0],v,u,delay);
            q[1].print();
            q[0] = q[1];
            end = clock();
            cout<<end;
            while((end - start) < delay)
                end = clock();
            cout<<end;


        std::cout << "----------------------" << std::endl;
        usleep(200000);
    }

    free(accels);
    free(gyros);
    i2c->closeConnection();
    delete i2c, mpu6050;

    return 0;
}
