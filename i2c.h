#include "MKL46Z4.h"

class i2c
{
	I2C_Type* m_device;
	public:
	i2c(I2C_Type* device);
	
	void enable();  
	void disable(); 
	void start(); 
	void restart();
	void stop(); 
	void selectTX();
	void selectRX();
	void clearIICIF();
	void sendACK();
	void sendNACK();
	
	void init();
	void writeByte(uint8_t toSend);
	void readByte(uint8_t* readBuffer);
	bool isACK();
};
