/////////////////////////////////////////////////////
// Filename: mpu6050.cpp
// Author: Subhojit Basu [ subhojit.basu@gmail.com ]
// License : MIT License
// Creation Date : 13 Feb 2023
/////////////////////////////////////////////////////

#include "mpu6050.h"



mpu6050::mpu6050(){
    /* initialize mraa for the platform (not needed most of the times) */
    mraa::I2c i2c(I2C_BUS);

    /* set slave address */
   i2c.address(MPU6050_ADDR);


    /* reset the sensor */
    i2c.write_byte_data(i2c, MPU6050_RESET, MPU6050_REG_PWR_MGMT_1);


    sleep(1);

    data = ret;
    data |= MPU6050_PLL_GYRO_X;
    data &= ~(MPU6050_SLEEP);

    i2c.write_byte_data(i2c, data, MPU6050_REG_PWR_MGMT_1);

    sleep(1);


}

mpu6050::~mpu6050(){

}

void mpu6050::read(){
    //double val[3];
    int raw[3];

    raw[0] =  i2c.read_word(i2c, MPU6050_REG_RAW_ACCEL_X);
    raw[1] =  i2c.read_word(i2c, MPU6050_REG_RAW_ACCEL_Y);
    raw[2] =  i2c.read_word(i2c, MPU6050_REG_RAW_ACCEL_Z);

    raw_accl.set(raw[0],raw[1],raw[2]);
    accl =  (raw_accl/(MPU6050_ACCEL_SCALE));

    raw[0] =  i2c.read_word(i2c, MPU6050_REG_RAW_GYRO_X);
    raw[1] =  i2c.read_word(i2c, MPU6050_REG_RAW_GYRO_Y);
    raw[2] =  i2c.read_word(i2c, MPU6050_REG_RAW_GYRO_Z);

    raw_gyro.set(raw[0],raw[1],raw[2]);
    gyro = (raw_gyro/(MPU6050_GYRO_SCALE));
    
}
vector<double,3> mpu6050::getA(void){
    return accl;
}
vector<double,3> mpu6050::getW(void){
    return gyro;
}