/////////////////////////////////////////////////////
// Filename: mpu6050.cpp
// Author: Subhojit Basu [ subhojit.basu@gmail.com ]
// License : MIT License
// Creation Date : 13 Feb 2023
/////////////////////////////////////////////////////

#include "mpu6050.h"



mpu6050::mpu6050(){
    /* initialize mraa for the platform (not needed most of the times) */
    mraa::I2c i2c_1(I2C_BUS);

    i2c = &(i2c_1);

    //i2c.init();
    
    /* set slave address */
    i2c->address(MPU6050_ADDR);

    buff[1] = MPU6050_RESET;
    buff[0] = MPU6050_REG_PWR_MGMT_1;
    /* reset the sensor */
    i2c->write(buff,2);


    sleep(5);

    
    uint8_t data = i2c->readReg(MPU6050_REG_PWR_MGMT_1);
    data |= MPU6050_PLL_GYRO_X;
    data &= ~(MPU6050_SLEEP);
    i2c->address(MPU6050_ADDR);
    buff[1] = data;
    buff[0] = MPU6050_REG_PWR_MGMT_1;

    i2c->write(buff,2);

    sleep(5);


}

mpu6050::~mpu6050(){

}

void mpu6050::read(){
    int16_t val[3];
    int raw[3];
    i2c->address(MPU6050_ADDR);
    val[0] = i2c->readWordReg(MPU6050_REG_RAW_ACCEL_X);
    //i2c->address(MPU6050_ADDR);
    //i2c->read(buff,2);
    raw[0] = (int) val[0];

    i2c->address(MPU6050_ADDR);
    val[1] = i2c->readWordReg(MPU6050_REG_RAW_ACCEL_Y);
    //i2c->address(MPU6050_ADDR);
    //i2c->read(buff,2);
    raw[1] = (int) val[1];

    i2c->address(MPU6050_ADDR);
    val[2] = i2c->readWordReg(MPU6050_REG_RAW_ACCEL_Z);
    //i2c->address(MPU6050_ADDR);
    //i2c->read(buff,2);
    raw[2] = (int) val[2];


    raw_accl.set(raw[0],raw[1],raw[2]);
    accl =  (raw_accl/(MPU6050_ACCEL_SCALE));

    i2c->address(MPU6050_ADDR);
    val[0] = i2c->readWordReg(MPU6050_REG_RAW_GYRO_X);
    //i2c->address(MPU6050_ADDR);
    //i2c->read(buff,2);
    raw[0] = (int) val[0];


    i2c->address(MPU6050_ADDR);
    val[1] = i2c->readWordReg(MPU6050_REG_RAW_GYRO_Y);
    //i2c->address(MPU6050_ADDR);
    //i2c->read(buff,2);
    raw[1] = (int) val[1];

    i2c->address(MPU6050_ADDR);
    val[2] = i2c->readWordReg(MPU6050_REG_RAW_GYRO_Z);
    //i2c->address(MPU6050_ADDR);
    //i2c->read(buff,2);
    raw[2] = (int) val[2];

    raw_gyro.set(raw[0],raw[1],raw[2]);
    gyro = (raw_gyro/(MPU6050_GYRO_SCALE));
    
}
vector<double,3> mpu6050::getA(void){
    return accl;
}
vector<double,3> mpu6050::getW(void){
    return gyro;
}