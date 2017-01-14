#include "MPU6050.h"

MPU6050::MPU6050():
conectionDevice(I2C1)
{
	conectionDevice.init();
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

void MPU6050::Init()
{
	setRegister(0x6B,0x00);
}

uint16_t MPU6050::readRawAccelZ()
{
	return readHL(0x3F);
}
