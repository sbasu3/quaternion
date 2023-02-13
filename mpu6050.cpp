/////////////////////////////////////////////////////
// Filename: mpu6050.cpp
// Author: Subhojit Basu [ subhojit.basu@gmail.com ]
// License : MIT License
// Creation Date : 13 Feb 2023
/////////////////////////////////////////////////////

#include "mpu6050.h"

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>

mpu6050::mpu6050(){
    /* initialize mraa for the platform (not needed most of the times) */
    mraa_init();

    //! [Interesting]
    /* initialize I2C bus */
    i2c = mraa_i2c_init(I2C_BUS);
    if (i2c == NULL) {
        fprintf(stderr, "Failed to initialize I2C\n");
        mraa_deinit();
        //return EXIT_FAILURE;
    }

    /* set slave address */
    status = mraa_i2c_address(i2c, MPU6050_ADDR);
    if (status != MRAA_SUCCESS) {
        //goto err_exit;
    }

    /* reset the sensor */
    status = mraa_i2c_write_byte_data(i2c, MPU6050_RESET, MPU6050_REG_PWR_MGMT_1);
    if (status != MRAA_SUCCESS) {
        //goto err_exit;
    }

    sleep(1);

    /* configure power management register */
    ret = mraa_i2c_read_byte_data(i2c, MPU6050_REG_PWR_MGMT_1);
    if (ret == -1) {
        //return EXIT_FAILURE;
    }

    data = ret;
    data |= MPU6050_PLL_GYRO_X;
    data &= ~(MPU6050_SLEEP);

    status = mraa_i2c_write_byte_data(i2c, data, MPU6050_REG_PWR_MGMT_1);
    if (status != MRAA_SUCCESS) {
        //goto err_exit;
    }

    sleep(1);


}

mpu6050::~mpu6050(){

    /* stop i2c */
    mraa_i2c_stop(i2c);

    //! [Interesting]
    /* deinitialize mraa for the platform (not needed most of the times) */
    mraa_deinit();


}
void mpu6050::read(){
    double val[3];

    val[0] =  i2c_read_word(i2c, MPU6050_REG_RAW_ACCEL_X);
    val[1] =  i2c_read_word(i2c, MPU6050_REG_RAW_ACCEL_Y);
    val[2] =  i2c_read_word(i2c, MPU6050_REG_RAW_ACCEL_Z);

    raw_accl.set(val[0],val[1],val[2]);
    accl = raw_accl/(MPU6050_ACCEL_SCALE);

    val[0] =  i2c_read_word(i2c, MPU6050_REG_RAW_GYRO_X);
    val[1] =  i2c_read_word(i2c, MPU6050_REG_RAW_GYRO_Y);
    val[2] =  i2c_read_word(i2c, MPU6050_REG_RAW_GYRO_Z);

    raw_gyro.set(val[0],val[1],val[2]);
    gyro = raw_gyro/(MPU6050_GYRO_SCALE);
    
}
vector<double,3> mpu6050::getA(void){
    return accl;
}
vector<double,3> mpu6050::getW(void){
    return gyro;
}