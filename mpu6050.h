/////////////////////////////////////////////////////
// Filename: mpu6050.h
// Author: Subhojit Basu [ subhojit.basu@gmail.com ]
// License : MIT License
// Creation Date : 13 Feb 2023
/////////////////////////////////////////////////////


/* mraa header */
#include "vector.h"


/* standard headers */
#include <iostream>
#include <math.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

/* mraa headers */
#include "mraa/common.hpp"
#include "mraa/i2c.hpp"


#define I2C_BUS 0

/* register definitions */
#define MPU6050_ADDR 0x68
#define MPU6050_REG_PWR_MGMT_1 0x6b
#define MPU6050_REG_RAW_ACCEL_X 0x3b
#define MPU6050_REG_RAW_ACCEL_Y 0x3d
#define MPU6050_REG_RAW_ACCEL_Z 0x3f
#define MPU6050_REG_RAW_GYRO_X 0x43
#define MPU6050_REG_RAW_GYRO_Y 0x45
#define MPU6050_REG_RAW_GYRO_Z 0x47

/* bit definitions */
#define MPU6050_RESET 0x80
#define MPU6050_SLEEP (1 << 6)
#define MPU6050_PLL_GYRO_X (1 << 1)

/* accelerometer scale factor for (+/-)2g */
#define MPU6050_ACCEL_SCALE 16384.0

/* gyroscope scale factor for (+/-)250/s */
#define MPU6050_GYRO_SCALE 131.0

class mpu6050{
    private:
        //raw values from sensor
        vector<int,3> raw_accl;
        vector<int,3> raw_gyro;
        //scaled values 
        vector<double,3> accl;
        vector<double,3> gyro;
        mraa_result_t status;
        mraa_i2c_context i2c;
        uint8_t data;
        int ret;
    public:
        mpu6050();
        ~mpu6050();
        void read();
        vector<double,3> getA(void);
        vector<double,3> getW(void);
};