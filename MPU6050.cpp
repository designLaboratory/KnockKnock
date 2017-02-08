////////////////////////////////////////////////
// MPU6050 handling using i2c interface       //
// Authors: Adrian Barnas (ABarnasFLY)        //
//          Agnieszka Lupierz (LupierzA)      //
////////////////////////////////////////////////

#include "MPU6050.h"

MPU6050::MPU6050():
conectionDevice(I2C1)
{
	conectionDevice.init();
	GPIO::init_GPIO();
}

bool MPU6050::detected()
{
	return GPIO::detected();
}

int MPU6050::readHL(uint8_t RegisterAdress)
{
	uint8_t hdata;
  uint8_t ldata;
	conectionDevice.enable();
	conectionDevice.start();
	conectionDevice.writeByte(0x68 << 1);
	conectionDevice.writeByte(RegisterAdress);
  conectionDevice.restart();
	conectionDevice.writeByte((0x68 << 1) +1);
	conectionDevice.sendACK();
  conectionDevice.readByte(&hdata);
	conectionDevice.sendNACK();
	conectionDevice.readByte(&ldata);
	conectionDevice.stop();
	conectionDevice.disable();
	return (hdata << 8)+ ldata;	
	
}
void MPU6050::setRegister(uint8_t RegisterAdress, uint8_t value)
{
	conectionDevice.enable();
	conectionDevice.start();
	conectionDevice.writeByte(0x68 << 1);
	conectionDevice.writeByte(RegisterAdress);
	conectionDevice.writeByte(value);
	conectionDevice.stop();
	conectionDevice.disable();
}
void MPU6050::enableOnMotionInterupt(uint16_t thereshold, uint16_t duration)
{
	setRegister(0x1c, 1); //Configure High Pass Filter at 5Hz
	setRegister(0x37,0); //Interupt pin configuration - active High
	setRegister(0x1f,10 ); //Motion detection thereshold
	setRegister(0x20,1); //Motion minimal duration (1ms)
	setRegister(0x69,0x13); //Motion detection control (timer increment = 1)
	setRegister(0x38,64); //Enable Motion interupt
}

void MPU6050::Init()
{
	setRegister(0x6B,0x00);
}

uint16_t MPU6050::readRawAccelZ()
{
	return readHL(0x3F);
}
